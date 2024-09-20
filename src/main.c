/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: License Ref-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/conn.h>
#include <dk_buttons_and_leds.h>
#include <nrfx_saadc.h>

#include "Beacon.h"


static struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
	(BT_LE_ADV_OPT_CONNECTABLE |
	 BT_LE_ADV_OPT_USE_IDENTITY), 	/* Connectable advertising and use identity address */
	BT_GAP_ADV_FAST_INT_MIN_1,		/* Min Advertising Interval 1000ms (1600*0.625ms) */
	BT_GAP_ADV_FAST_INT_MAX_1,
	BT_ID_DEFAULT					/* Max Advertising Interval 1000.625ms (1600*0.625ms) */
	); 							/* Set to NULL for undirected advertising */


struct bt_conn *my_conn = NULL;

static struct bt_gatt_exchange_params exchange_params;

static void exchange_func(struct bt_conn *conn, uint8_t att_err,struct bt_gatt_exchange_params *params);

#define DEVICE_NAME "Tracker Beacon"
#define DEVICE_NAME_LEN (sizeof("Tracker Beacon") - 1)

#define RUN_STATUS_LED DK_LED1
#define CON_STATUS_LED DK_LED2
#define USER_RING 	   DK_LED3
#define FIND_BUTTON    DK_BTN1_MSK

#define STACKSIZE 1024
#define PRIORITY 7

#define RUN_LED_BLINK_INTERVAL 1000
#define RUN_RING_BLINK_INTERVAL 100
#define NOTIFY_INTERVAL 60000
static bool app_button_state;
static struct bt_conn_cb conn_callbacks;

bool Ring_state = 0 ;
int err;
uint32_t battery_voltage;
static nrfx_saadc_channel_t channel = NRFX_SAADC_DEFAULT_CHANNEL_SE(NRF_SAADC_INPUT_AIN0, 0);

static bool bluetooth_connected = false;

static int16_t sample;

#define BATTERY_SAMPLE_INTERVAL_MS 2000

static void battery_sample_timer_handler(struct k_timer *timer);

K_TIMER_DEFINE(battery_sample_timer, battery_sample_timer_handler, NULL);

void battery_sample_timer_handler(struct k_timer *timer)
{

        /*Trigger the sampling */
        nrfx_err_t err = nrfx_saadc_mode_trigger();
        if (err != NRFX_SUCCESS) {
                //printk("nrfx_saadc_mode_trigger error: %08x", err);
                return;
        }

        /*Calculate and print voltage */
        battery_voltage = ((600*8) * sample) / ((1<<12));

        //printk("SAADC sample: %d\n", sample);
        //printk("Battery Voltage: %d mV\n", battery_voltage);

}

static void configure_saadc(void)
{
        /*Connect ADC interrupt to nrfx interrupt handler */
        IRQ_CONNECT(DT_IRQN(DT_NODELABEL(adc)),
		    DT_IRQ(DT_NODELABEL(adc), priority),
		    nrfx_isr, nrfx_saadc_irq_handler, 0);
        
        /*Initialize the nrfx_SAADC driver */
        nrfx_err_t err = nrfx_saadc_init(DT_IRQ(DT_NODELABEL(adc), priority));
        if (err != NRFX_SUCCESS) 
        {
               //printk("nrfx_saadc_mode_trigger error: %08x", err);
                return;
        }

        /*Configure the SAADC channel */
        channel.channel_config.gain = NRF_SAADC_GAIN1_6;
        err = nrfx_saadc_channels_config(&channel, 1);
        if (err != NRFX_SUCCESS) 
        {
		//printk("nrfx_saadc_channels_config error: %08x", err);
	        return;
	}

        /*Configure nrfx_SAADC driver in simple and blocking mode */
        err = nrfx_saadc_simple_mode_set(BIT(0),
                                         NRF_SAADC_RESOLUTION_12BIT,
                                         NRF_SAADC_OVERSAMPLE_DISABLED,
                                         NULL);
        if (err != NRFX_SUCCESS) {
                //printk("nrfx_saadc_simple_mode_set error: %08x", err);
                return;
        }
        
        /*Set buffer where sample will be stored */
        err = nrfx_saadc_buffer_set(&sample, 1);
        if (err != NRFX_SUCCESS) {
                //printk("nrfx_saadc_buffer_set error: %08x", err);
                return;
        }

        /*Start periodic timer for battery sampling */
	k_timer_start(&battery_sample_timer, K_NO_WAIT, K_MSEC(BATTERY_SAMPLE_INTERVAL_MS));

}

/*PHY coded as "BT_GAP_LE_PHY_CODED" for extra long range */
void on_le_param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency,
			 uint16_t timeout){
	double connection_interval = interval * 1.25; // in ms
	uint16_t supervision_timeout = timeout * 10; // in ms
	//printk("Connection parameters updated: interval %.2f ms, latency %d intervals, timeout %d ms",connection_interval, latency, supervision_timeout);
}
static void update_phy(struct bt_conn *conn)
{
    int err;
    const struct bt_conn_le_phy_param preferred_phy = {
        .options = BT_CONN_LE_PHY_OPT_NONE,
        .pref_rx_phy = BT_GAP_LE_PHY_1M,
        .pref_tx_phy = BT_GAP_LE_PHY_1M,
    };
    err = bt_conn_le_phy_update(conn, &preferred_phy);
    if (err) {
        //printk("bt_conn_le_phy_update() returned %d", err);
    }
}
void on_le_phy_updated(struct bt_conn *conn, struct bt_conn_le_phy_info *param)
{
    // PHY Updated
    if (param->tx_phy == BT_CONN_LE_TX_POWER_PHY_1M) {
        //printk("PHY updated. New PHY: 1M");
    }
    else if (param->tx_phy == BT_CONN_LE_TX_POWER_PHY_2M) {
        //printk("PHY updated. New PHY: 2M");
    }
    else if (param->tx_phy == BT_CONN_LE_TX_POWER_PHY_CODED_S8) {
        //printk("PHY updated. New PHY: Long Range");
    }
}
static void on_security_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err)
{
	char addr[BT_ADDR_LE_STR_LEN];
	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	if (!err) {
		//printk("Security changed: %s level %u\n", addr, level);
	} else {
		//printk("Security failed: %s level %u err %d\n", addr, level, err);
	}
}
static void update_data_length(struct bt_conn *conn)
{
    int err;
    struct bt_conn_le_data_len_param my_data_len = {
        .tx_max_len = BT_GAP_DATA_LEN_MAX,
        .tx_max_time = BT_GAP_DATA_TIME_MAX,
    };
    err = bt_conn_le_data_len_update(conn, &my_data_len);
    if (err) {
        //printk("data_len_update failed (err %d)", err);
    }
}
static void update_mtu(struct bt_conn *conn)
{
    int err;
    exchange_params.func = exchange_func;

    err = bt_gatt_exchange_mtu(conn, &exchange_params);
    if (err) {
        //printk("bt_gatt_exchange_mtu failed (err %d)", err);
    }
}

void on_le_data_len_updated(struct bt_conn *conn, struct bt_conn_le_data_len_info *info)
{
    uint16_t tx_len     = info->tx_max_len; 
    uint16_t tx_time    = info->tx_max_time;
    uint16_t rx_len     = info->rx_max_len;
    uint16_t rx_time    = info->rx_max_time;
    //printk("Data length updated. Length %d/%d bytes, time %d/%d us", tx_len, rx_len, tx_time, rx_time);
}
static void exchange_func(struct bt_conn *conn, uint8_t att_err,
			  struct bt_gatt_exchange_params *params)
{
    if (!att_err) {
        uint16_t payload_mtu = bt_gatt_get_mtu(conn) - 3;   // 3 bytes used for Attribute headers.
        //printk("New MTU: %d bytes", payload_mtu);
    }
}
static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),

};

static const struct bt_data sd[] = {
	BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_LBS_VAL),
};

static void app_led_cb(bool led_state)
{
	Ring_state  = led_state;
}

static bool app_button_cb(void)
{
	return app_button_state;
}
static struct my_lbs_cb app_callbacks = {
	.led_cb = app_led_cb,
	.button_cb = app_button_cb,
};

/* Define the thread functions  */
void send_data_thread(void)
{
	while (1) {
		if (bluetooth_connected) {
			/* Send notification, the function sends notifications only if a client is subscribed */
			// printk("\n send_data_thread Running");
			uint32_t battery_voltage_Percentece = (uint32_t)((battery_voltage/4200)*100);
			if (battery_voltage_Percentece >=100){battery_voltage_Percentece=99;}
			//printk("Battery Percentece: %d \n", battery_voltage_Percentece);
			my_lbs_send_sensor_notify(battery_voltage);
			k_sleep(K_MSEC(NOTIFY_INTERVAL));
		}
		else{
			k_sleep(K_MSEC(30000));
			k_yield	();
		}
	}
}
void Ring_thread(void)
{
	while (1) {
		if (bluetooth_connected) {	
			// printk("\n Ring_thread Running");
			if (Ring_state == 1){
				dk_set_led(USER_RING, 1);
				k_sleep(K_MSEC(RUN_RING_BLINK_INTERVAL));
				dk_set_led(USER_RING, 0);
				k_sleep(K_MSEC(RUN_RING_BLINK_INTERVAL));
				}
			else {
				dk_set_led(USER_RING,1);
				k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
				k_yield	();
			}
		}
		else {
			k_sleep(K_MSEC(30000));
			k_yield	();
		}
	}
}
/*Send indication on a button press */
static void button_changed(uint32_t button_state, uint32_t has_changed)
{
	if (has_changed & FIND_BUTTON) {
		uint32_t user_button_state = button_state & FIND_BUTTON;
		my_lbs_send_button_state_indicate(user_button_state);
		app_button_state = user_button_state ? true : false;
	}
}
static void on_connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		//printk("Connection failed (err %u)\n", err);
		return;
	}
	//printk("Connected\n");
	bluetooth_connected = true;
	/*Led indicat connected */
	my_conn = bt_conn_ref(conn);
	struct bt_conn_info info;
		err = bt_conn_get_info(conn, &info);
	if (err) {
		//printk("bt_conn_get_info() returned %d", err);
		return;
	}
	double connection_interval = info.le.interval * 1.25; // in ms
	uint16_t supervision_timeout = info.le.timeout * 10; // in ms
	//printk("Connection parameters: interval %.2f ms, latency %d intervals, timeout %d ms",connection_interval, info.le.latency, supervision_timeout);
	/*Update the PHY */
	update_phy(my_conn);
	/*Update the data length and MTU */
	update_data_length(my_conn);
	update_mtu(my_conn);
	dk_set_led_on(CON_STATUS_LED);				
	k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL*2));
	dk_set_led_off(CON_STATUS_LED);
}

static void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
	//printk("Disconnected** (reason %u)\n", reason);
	bluetooth_connected = false;
	/*Led indicat Disconnected */
	dk_set_led_on(RUN_STATUS_LED);				
	k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL*2));
	dk_set_led_off(RUN_STATUS_LED);
}
// Disconnection handler
void disconnected(struct bt_conn *conn, uint8_t reason)
{
    //printk("\nDisconnected (reason %d). Restarting", reason);
	NVIC_SystemReset();
}
void setup_conn_callbacks()
{
    conn_callbacks.connected = NULL;  // Handle connected event if needed
    conn_callbacks.disconnected = disconnected; // Handle disconnection event
    bt_conn_cb_register(&conn_callbacks); // Register the callbacks
}
struct bt_conn_cb connection_callbacks = {
	.connected = on_connected,
	.disconnected = on_disconnected,
	.le_param_updated = on_le_param_updated,
	.le_phy_updated = on_le_phy_updated,
	.le_data_len_updated = on_le_data_len_updated,
	/* Added the security_changed member to the callback structure */
	.security_changed = on_security_changed,
};
static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
	char addr[BT_ADDR_LE_STR_LEN]; 
	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	//printk("\n*********Passkey for %s: %06u\n**********\n", addr, passkey);
}

static void auth_cancel(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];
	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	//printk("Pairing cancelled: %s\n", addr);
}

static struct bt_conn_auth_cb conn_auth_callbacks = { 
	.passkey_display = auth_passkey_display,	
	.pairing_confirm = NULL,
	.cancel = auth_cancel,
};
static int init_button(void)
{
	int err;

	err = dk_buttons_init(button_changed);
	if (err) {
		//printk("Cannot init buttons (err: %d)\n", err);
	}

	return err;
}

int main(void)
{
	//printk(" Tracker Beacon \n");
	configure_saadc();
	err = dk_leds_init();
	unsigned int passkey = 123456;
	bt_passkey_set(passkey);
	dk_set_led(USER_RING,1);
	if (err) {
		//printk("LEDs init failed (err %d)\n", err);
		return -1;
	}

	err = init_button();
	if (err) {
		//printk("Button init failed (err %d)\n", err);
		return -1;
	}

	err = bt_enable(NULL);
	if (err) {
		//printk("Bluetooth init failed (err %d)\n", err);
		return -1;
	}
	bt_conn_cb_register(&connection_callbacks);

	err = my_lbs_init(&app_callbacks);
	if (err) {
		//printk("Failed to init LBS (err:%d)\n", err);
		return -1;
	}
	//printk("Bluetooth initialized\n");
	err = bt_conn_auth_cb_register(&conn_auth_callbacks);
	if (err) {
		//printk("Failed to register authorization callbacks.\n");
		return -1;
	}
	setup_conn_callbacks();
	err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		//printk("Advertising failed to start (err %d)\n", err);
		/*Led and Ring indicat Advertising started not succesfully */
		dk_set_led_on(RUN_STATUS_LED);	
		dk_set_led_on(USER_RING);	
		return -1;
	}
	else {
		/*Led and Ring indicat Advertising started succesfully */
		for (int i = 0;i<=10;i++){
			dk_set_led(RUN_STATUS_LED, i%2);	
			k_sleep(K_MSEC(RUN_RING_BLINK_INTERVAL));
		}
		//printk("Advertising successfully started\n");
		}
	dk_set_led(USER_RING,1);
}
K_THREAD_DEFINE(send_data_thread_id, STACKSIZE, send_data_thread, NULL, NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(Ring_thread_id, STACKSIZE, Ring_thread, NULL, NULL, NULL, PRIORITY, 0, 0);