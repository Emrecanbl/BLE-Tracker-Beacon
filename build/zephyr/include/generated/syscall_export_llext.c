
/* Export syscalls for extensions */
static void * const no_handler = NULL;

/* Weak references, if something is not found by the linker, it will be NULL
 * and simply fail during extension load
 */
extern __weak ALIAS_OF(no_handler) void * const z_impl_zephyr_read_stdin;
extern __weak ALIAS_OF(no_handler) void * const z_impl_zephyr_write_stdout;
extern __weak ALIAS_OF(no_handler) void * const z_impl_zephyr_fputc;
extern __weak ALIAS_OF(no_handler) void * const z_impl_zephyr_fwrite;
extern __weak ALIAS_OF(no_handler) void * const z_impl___posix_clock_get_base;
extern __weak ALIAS_OF(no_handler) void * const z_impl_z_sys_mutex_kernel_lock;
extern __weak ALIAS_OF(no_handler) void * const z_impl_z_sys_mutex_kernel_unlock;
extern __weak ALIAS_OF(no_handler) void * const z_impl_z_log_msg_simple_create_0;
extern __weak ALIAS_OF(no_handler) void * const z_impl_z_log_msg_simple_create_1;
extern __weak ALIAS_OF(no_handler) void * const z_impl_z_log_msg_simple_create_2;
extern __weak ALIAS_OF(no_handler) void * const z_impl_z_log_msg_static_create;
extern __weak ALIAS_OF(no_handler) void * const z_impl_log_panic;
extern __weak ALIAS_OF(no_handler) void * const z_impl_log_process;
extern __weak ALIAS_OF(no_handler) void * const z_impl_log_buffered_cnt;
extern __weak ALIAS_OF(no_handler) void * const z_impl_log_filter_set;
extern __weak ALIAS_OF(no_handler) void * const z_impl_log_frontend_filter_set;
extern __weak ALIAS_OF(no_handler) void * const z_impl_sys_rand_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_sys_csrand_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_entropy_get_entropy;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_pin_interrupt_configure;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_pin_configure;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_port_get_direction;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_pin_get_config;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_port_get_raw;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_port_set_masked_raw;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_port_set_bits_raw;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_port_clear_bits_raw;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_port_toggle_bits;
extern __weak ALIAS_OF(no_handler) void * const z_impl_gpio_get_pending_int;
extern __weak ALIAS_OF(no_handler) void * const z_impl_hwinfo_get_device_id;
extern __weak ALIAS_OF(no_handler) void * const z_impl_hwinfo_get_device_eui64;
extern __weak ALIAS_OF(no_handler) void * const z_impl_hwinfo_get_reset_cause;
extern __weak ALIAS_OF(no_handler) void * const z_impl_hwinfo_clear_reset_cause;
extern __weak ALIAS_OF(no_handler) void * const z_impl_hwinfo_get_supported_reset_cause;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_err_check;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_poll_in;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_poll_in_u16;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_poll_out;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_poll_out_u16;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_configure;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_config_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_irq_tx_enable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_irq_tx_disable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_irq_rx_enable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_irq_rx_disable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_irq_err_enable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_irq_err_disable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_irq_is_pending;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_irq_update;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_tx;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_tx_u16;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_tx_abort;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_rx_enable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_rx_enable_u16;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_rx_disable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_line_ctrl_set;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_line_ctrl_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_uart_drv_cmd;
extern __weak ALIAS_OF(no_handler) void * const z_impl_device_get_binding;
extern __weak ALIAS_OF(no_handler) void * const z_impl_device_is_ready;
extern __weak ALIAS_OF(no_handler) void * const z_impl_device_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_stack_alloc;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_stack_free;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_create;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_stack_space_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_join;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_sleep;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_usleep;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_busy_wait;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_yield;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_wakeup;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_sched_current_thread_query;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_abort;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_start;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_timeout_expires_ticks;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_timeout_remaining_ticks;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_priority_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_priority_set;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_deadline_set;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_suspend;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_resume;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_is_preempt_thread;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_custom_data_set;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_custom_data_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_name_set;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_thread_name_copy;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_timer_start;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_timer_stop;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_timer_status_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_timer_status_sync;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_timer_expires_ticks;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_timer_remaining_ticks;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_timer_user_data_set;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_timer_user_data_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_uptime_ticks;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_queue_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_queue_cancel_wait;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_queue_alloc_append;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_queue_alloc_prepend;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_queue_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_queue_is_empty;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_queue_peek_head;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_queue_peek_tail;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_futex_wait;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_futex_wake;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_event_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_event_post;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_event_set;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_event_set_masked;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_event_clear;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_event_wait;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_event_wait_all;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_stack_alloc_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_stack_push;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_stack_pop;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_mutex_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_mutex_lock;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_mutex_unlock;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_condvar_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_condvar_signal;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_condvar_broadcast;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_condvar_wait;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_sem_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_sem_take;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_sem_give;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_sem_reset;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_sem_count_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_msgq_alloc_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_msgq_put;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_msgq_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_msgq_peek;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_msgq_peek_at;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_msgq_purge;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_msgq_num_free_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_msgq_get_attrs;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_msgq_num_used_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_pipe_alloc_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_pipe_put;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_pipe_get;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_pipe_read_avail;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_pipe_write_avail;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_pipe_flush;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_pipe_buffer_flush;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_poll;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_poll_signal_init;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_poll_signal_reset;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_poll_signal_check;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_poll_signal_raise;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_str_out;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_float_disable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_float_enable;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_object_access_grant;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_object_release;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_object_alloc;
extern __weak ALIAS_OF(no_handler) void * const z_impl_k_object_alloc_size;
extern __weak ALIAS_OF(no_handler) void * const z_impl_sys_clock_hw_cycles_per_sec_runtime_get;

/* Exported symbols */
EXPORT_SYMBOL(z_impl_zephyr_read_stdin);
EXPORT_SYMBOL(z_impl_zephyr_write_stdout);
EXPORT_SYMBOL(z_impl_zephyr_fputc);
EXPORT_SYMBOL(z_impl_zephyr_fwrite);
EXPORT_SYMBOL(z_impl___posix_clock_get_base);
EXPORT_SYMBOL(z_impl_z_sys_mutex_kernel_lock);
EXPORT_SYMBOL(z_impl_z_sys_mutex_kernel_unlock);
EXPORT_SYMBOL(z_impl_z_log_msg_simple_create_0);
EXPORT_SYMBOL(z_impl_z_log_msg_simple_create_1);
EXPORT_SYMBOL(z_impl_z_log_msg_simple_create_2);
EXPORT_SYMBOL(z_impl_z_log_msg_static_create);
EXPORT_SYMBOL(z_impl_log_panic);
EXPORT_SYMBOL(z_impl_log_process);
EXPORT_SYMBOL(z_impl_log_buffered_cnt);
EXPORT_SYMBOL(z_impl_log_filter_set);
EXPORT_SYMBOL(z_impl_log_frontend_filter_set);
EXPORT_SYMBOL(z_impl_sys_rand_get);
EXPORT_SYMBOL(z_impl_sys_csrand_get);
EXPORT_SYMBOL(z_impl_entropy_get_entropy);
EXPORT_SYMBOL(z_impl_gpio_pin_interrupt_configure);
EXPORT_SYMBOL(z_impl_gpio_pin_configure);
EXPORT_SYMBOL(z_impl_gpio_port_get_direction);
EXPORT_SYMBOL(z_impl_gpio_pin_get_config);
EXPORT_SYMBOL(z_impl_gpio_port_get_raw);
EXPORT_SYMBOL(z_impl_gpio_port_set_masked_raw);
EXPORT_SYMBOL(z_impl_gpio_port_set_bits_raw);
EXPORT_SYMBOL(z_impl_gpio_port_clear_bits_raw);
EXPORT_SYMBOL(z_impl_gpio_port_toggle_bits);
EXPORT_SYMBOL(z_impl_gpio_get_pending_int);
EXPORT_SYMBOL(z_impl_hwinfo_get_device_id);
EXPORT_SYMBOL(z_impl_hwinfo_get_device_eui64);
EXPORT_SYMBOL(z_impl_hwinfo_get_reset_cause);
EXPORT_SYMBOL(z_impl_hwinfo_clear_reset_cause);
EXPORT_SYMBOL(z_impl_hwinfo_get_supported_reset_cause);
EXPORT_SYMBOL(z_impl_uart_err_check);
EXPORT_SYMBOL(z_impl_uart_poll_in);
EXPORT_SYMBOL(z_impl_uart_poll_in_u16);
EXPORT_SYMBOL(z_impl_uart_poll_out);
EXPORT_SYMBOL(z_impl_uart_poll_out_u16);
EXPORT_SYMBOL(z_impl_uart_configure);
EXPORT_SYMBOL(z_impl_uart_config_get);
EXPORT_SYMBOL(z_impl_uart_irq_tx_enable);
EXPORT_SYMBOL(z_impl_uart_irq_tx_disable);
EXPORT_SYMBOL(z_impl_uart_irq_rx_enable);
EXPORT_SYMBOL(z_impl_uart_irq_rx_disable);
EXPORT_SYMBOL(z_impl_uart_irq_err_enable);
EXPORT_SYMBOL(z_impl_uart_irq_err_disable);
EXPORT_SYMBOL(z_impl_uart_irq_is_pending);
EXPORT_SYMBOL(z_impl_uart_irq_update);
EXPORT_SYMBOL(z_impl_uart_tx);
EXPORT_SYMBOL(z_impl_uart_tx_u16);
EXPORT_SYMBOL(z_impl_uart_tx_abort);
EXPORT_SYMBOL(z_impl_uart_rx_enable);
EXPORT_SYMBOL(z_impl_uart_rx_enable_u16);
EXPORT_SYMBOL(z_impl_uart_rx_disable);
EXPORT_SYMBOL(z_impl_uart_line_ctrl_set);
EXPORT_SYMBOL(z_impl_uart_line_ctrl_get);
EXPORT_SYMBOL(z_impl_uart_drv_cmd);
EXPORT_SYMBOL(z_impl_device_get_binding);
EXPORT_SYMBOL(z_impl_device_is_ready);
EXPORT_SYMBOL(z_impl_device_init);
EXPORT_SYMBOL(z_impl_k_thread_stack_alloc);
EXPORT_SYMBOL(z_impl_k_thread_stack_free);
EXPORT_SYMBOL(z_impl_k_thread_create);
EXPORT_SYMBOL(z_impl_k_thread_stack_space_get);
EXPORT_SYMBOL(z_impl_k_thread_join);
EXPORT_SYMBOL(z_impl_k_sleep);
EXPORT_SYMBOL(z_impl_k_usleep);
EXPORT_SYMBOL(z_impl_k_busy_wait);
EXPORT_SYMBOL(z_impl_k_yield);
EXPORT_SYMBOL(z_impl_k_wakeup);
EXPORT_SYMBOL(z_impl_k_sched_current_thread_query);
EXPORT_SYMBOL(z_impl_k_thread_abort);
EXPORT_SYMBOL(z_impl_k_thread_start);
EXPORT_SYMBOL(z_impl_k_thread_timeout_expires_ticks);
EXPORT_SYMBOL(z_impl_k_thread_timeout_remaining_ticks);
EXPORT_SYMBOL(z_impl_k_thread_priority_get);
EXPORT_SYMBOL(z_impl_k_thread_priority_set);
EXPORT_SYMBOL(z_impl_k_thread_deadline_set);
EXPORT_SYMBOL(z_impl_k_thread_suspend);
EXPORT_SYMBOL(z_impl_k_thread_resume);
EXPORT_SYMBOL(z_impl_k_is_preempt_thread);
EXPORT_SYMBOL(z_impl_k_thread_custom_data_set);
EXPORT_SYMBOL(z_impl_k_thread_custom_data_get);
EXPORT_SYMBOL(z_impl_k_thread_name_set);
EXPORT_SYMBOL(z_impl_k_thread_name_copy);
EXPORT_SYMBOL(z_impl_k_timer_start);
EXPORT_SYMBOL(z_impl_k_timer_stop);
EXPORT_SYMBOL(z_impl_k_timer_status_get);
EXPORT_SYMBOL(z_impl_k_timer_status_sync);
EXPORT_SYMBOL(z_impl_k_timer_expires_ticks);
EXPORT_SYMBOL(z_impl_k_timer_remaining_ticks);
EXPORT_SYMBOL(z_impl_k_timer_user_data_set);
EXPORT_SYMBOL(z_impl_k_timer_user_data_get);
EXPORT_SYMBOL(z_impl_k_uptime_ticks);
EXPORT_SYMBOL(z_impl_k_queue_init);
EXPORT_SYMBOL(z_impl_k_queue_cancel_wait);
EXPORT_SYMBOL(z_impl_k_queue_alloc_append);
EXPORT_SYMBOL(z_impl_k_queue_alloc_prepend);
EXPORT_SYMBOL(z_impl_k_queue_get);
EXPORT_SYMBOL(z_impl_k_queue_is_empty);
EXPORT_SYMBOL(z_impl_k_queue_peek_head);
EXPORT_SYMBOL(z_impl_k_queue_peek_tail);
EXPORT_SYMBOL(z_impl_k_futex_wait);
EXPORT_SYMBOL(z_impl_k_futex_wake);
EXPORT_SYMBOL(z_impl_k_event_init);
EXPORT_SYMBOL(z_impl_k_event_post);
EXPORT_SYMBOL(z_impl_k_event_set);
EXPORT_SYMBOL(z_impl_k_event_set_masked);
EXPORT_SYMBOL(z_impl_k_event_clear);
EXPORT_SYMBOL(z_impl_k_event_wait);
EXPORT_SYMBOL(z_impl_k_event_wait_all);
EXPORT_SYMBOL(z_impl_k_stack_alloc_init);
EXPORT_SYMBOL(z_impl_k_stack_push);
EXPORT_SYMBOL(z_impl_k_stack_pop);
EXPORT_SYMBOL(z_impl_k_mutex_init);
EXPORT_SYMBOL(z_impl_k_mutex_lock);
EXPORT_SYMBOL(z_impl_k_mutex_unlock);
EXPORT_SYMBOL(z_impl_k_condvar_init);
EXPORT_SYMBOL(z_impl_k_condvar_signal);
EXPORT_SYMBOL(z_impl_k_condvar_broadcast);
EXPORT_SYMBOL(z_impl_k_condvar_wait);
EXPORT_SYMBOL(z_impl_k_sem_init);
EXPORT_SYMBOL(z_impl_k_sem_take);
EXPORT_SYMBOL(z_impl_k_sem_give);
EXPORT_SYMBOL(z_impl_k_sem_reset);
EXPORT_SYMBOL(z_impl_k_sem_count_get);
EXPORT_SYMBOL(z_impl_k_msgq_alloc_init);
EXPORT_SYMBOL(z_impl_k_msgq_put);
EXPORT_SYMBOL(z_impl_k_msgq_get);
EXPORT_SYMBOL(z_impl_k_msgq_peek);
EXPORT_SYMBOL(z_impl_k_msgq_peek_at);
EXPORT_SYMBOL(z_impl_k_msgq_purge);
EXPORT_SYMBOL(z_impl_k_msgq_num_free_get);
EXPORT_SYMBOL(z_impl_k_msgq_get_attrs);
EXPORT_SYMBOL(z_impl_k_msgq_num_used_get);
EXPORT_SYMBOL(z_impl_k_pipe_alloc_init);
EXPORT_SYMBOL(z_impl_k_pipe_put);
EXPORT_SYMBOL(z_impl_k_pipe_get);
EXPORT_SYMBOL(z_impl_k_pipe_read_avail);
EXPORT_SYMBOL(z_impl_k_pipe_write_avail);
EXPORT_SYMBOL(z_impl_k_pipe_flush);
EXPORT_SYMBOL(z_impl_k_pipe_buffer_flush);
EXPORT_SYMBOL(z_impl_k_poll);
EXPORT_SYMBOL(z_impl_k_poll_signal_init);
EXPORT_SYMBOL(z_impl_k_poll_signal_reset);
EXPORT_SYMBOL(z_impl_k_poll_signal_check);
EXPORT_SYMBOL(z_impl_k_poll_signal_raise);
EXPORT_SYMBOL(z_impl_k_str_out);
EXPORT_SYMBOL(z_impl_k_float_disable);
EXPORT_SYMBOL(z_impl_k_float_enable);
EXPORT_SYMBOL(z_impl_k_object_access_grant);
EXPORT_SYMBOL(z_impl_k_object_release);
EXPORT_SYMBOL(z_impl_k_object_alloc);
EXPORT_SYMBOL(z_impl_k_object_alloc_size);
EXPORT_SYMBOL(z_impl_sys_clock_hw_cycles_per_sec_runtime_get);
