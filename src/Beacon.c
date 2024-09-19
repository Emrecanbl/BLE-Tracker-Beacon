/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include "Beacon.h"

static bool notify_mysensor_enabled;
static bool indicate_enabled;
static bool button_state;
static struct my_lbs_cb lbs_cb;

static struct bt_gatt_indicate_params ind_params;

static void mylbsbc_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	indicate_enabled = (value == BT_GATT_CCC_INDICATE);
}

static void mylbsbc_ccc_mysensor_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	notify_mysensor_enabled = (value == BT_GATT_CCC_NOTIFY);
}

// This function is called when a remote device has acknowledged the indication at its host layer

static void indicate_cb(struct bt_conn *conn, struct bt_gatt_indicate_params *params, uint8_t err)
{
	//printk("Indication %s\n", err != 0U ? "fail" : "success");
	k_sleep(K_MSEC(1));
}

static ssize_t write_led(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,
			 uint16_t len, uint16_t offset, uint8_t flags)
{
	// LOG_DBG("Attribute write, handle: %u, conn: %p", attr->handle, (void *)conn);
	k_sleep(K_MSEC(1));

	if (len != 1U) {
		// LOG_DBG("Write led: Incorrect data length");
		k_sleep(K_MSEC(1));
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
	}

	if (offset != 0) {
		// LOG_DBG("Write led: Incorrect data offset");
		k_sleep(K_MSEC(1));
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	if (lbs_cb.led_cb) {
		// Read the received value
		uint8_t val = *((uint8_t *)buf);

		if (val == 0x00 || val == 0x01) {
			// Call the application callback function to update the LED state
			lbs_cb.led_cb(val ? true : false);
		} else {
			// LOG_DBG("Write led: Incorrect value");
			k_sleep(K_MSEC(1));
			return BT_GATT_ERR(BT_ATT_ERR_VALUE_NOT_ALLOWED);
		}
	}

	return len;
}

static ssize_t read_button(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
	// get a pointer to button_state which is passed in the BT_GATT_CHARACTERISTIC() and stored in attr->user_data
	const char *value = attr->user_data;

	if (lbs_cb.button_cb) {
		// Call the application callback function to update the get the current value of the button
		button_state = lbs_cb.button_cb();
		return bt_gatt_attr_read(conn, attr, buf, len, offset, value, sizeof(*value));
	}

	return 0;
}

/* LED Button Service Declaration */
BT_GATT_SERVICE_DEFINE(
	my_lbs_svc, BT_GATT_PRIMARY_SERVICE(BT_UUID_LBS),
	BT_GATT_CHARACTERISTIC(BT_UUID_LBS_BUTTON, BT_GATT_CHRC_READ | BT_GATT_CHRC_INDICATE,
			       BT_GATT_PERM_READ_AUTHEN, read_button, NULL, &button_state),
	BT_GATT_CCC(mylbsbc_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

	BT_GATT_CHARACTERISTIC(BT_UUID_LBS_LED, BT_GATT_CHRC_WRITE, BT_GATT_PERM_WRITE_AUTHEN, NULL,
			       write_led, NULL),
	BT_GATT_CHARACTERISTIC(BT_UUID_LBS_MYSENSOR, BT_GATT_CHRC_NOTIFY, BT_GATT_PERM_READ_AUTHEN, NULL,
			       NULL, NULL),

	BT_GATT_CCC(mylbsbc_ccc_mysensor_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

);
/* A function to register application callbacks for the LED and Button characteristics  */
int my_lbs_init(struct my_lbs_cb *callbacks)
{
	if (callbacks) {
		lbs_cb.led_cb = callbacks->led_cb;
		lbs_cb.button_cb = callbacks->button_cb;
	}

	return 0;
}

int my_lbs_send_button_state_indicate(bool button_state)
{
	if (!indicate_enabled) {
		return -EACCES;
	}
	ind_params.attr = &my_lbs_svc.attrs[2];
	ind_params.func = indicate_cb; // A remote device has ACKed at its host layer (ATT ACK)
	ind_params.destroy = NULL;
	ind_params.data = &button_state;
	ind_params.len = sizeof(button_state);
	return bt_gatt_indicate(NULL, &ind_params);
}

int my_lbs_send_sensor_notify(uint32_t sensor_value)
{
	if (!notify_mysensor_enabled) {
		return -EACCES;
	}

	return bt_gatt_notify(NULL, &my_lbs_svc.attrs[7], &sensor_value, sizeof(sensor_value));
}
