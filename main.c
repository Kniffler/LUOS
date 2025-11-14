#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "i2ckbd.h"
#include "lcdspi.h"
#include "keyboard_define.h"

const uint LEDPIN = 25;

void all_init()
{
	set_sys_clock_khz(133000, true);
	stdio_init_all();

	uart_init(uart0, 115200);

	uart_set_format(uart0, 8, 1, UART_PARITY_NONE);  // 8-N-1
	uart_set_fifo_enabled(uart0, false);

	init_i2c_kbd();
	lcd_init();

	gpio_init(LEDPIN);
	gpio_set_dir(LEDPIN, GPIO_OUT);

	gpio_put(LEDPIN, 1);
	sleep_ms(1000);
	lcd_clear();
}

int main()
{
	all_init();
	char msg[] = "Your mom\n";
	lcd_print_string(msg);
}



/*
* These functions are requried for FreeRTOS to work in static memory mode.
*/

#if configSUPPORT_STATIC_ALLOCATION
static StaticTask_t idle_task_tcb;
static StackType_t idle_task_stack[mainIDLE_TASK_STACK_DEPTH];
void vApplicationGetIdleTaskMemory(
    StaticTask_t **ppxIdleTaskTCBBuffer,
    StackType_t **ppxIdleTaskStackBuffer,
    uint32_t *pulIdleTaskStackSize
) {
    *ppxIdleTaskTCBBuffer = &idle_task_tcb;
    *ppxIdleTaskStackBuffer = idle_task_stack;
    *pulIdleTaskStackSize = mainIDLE_TASK_STACK_DEPTH;
}

static StaticTask_t timer_task_tcb;
static StackType_t timer_task_stack[configMINIMAL_STACK_SIZE];
void vApplicationGetTimerTaskMemory(
    StaticTask_t **ppxTimerTaskTCBBuffer,
    StackType_t **ppxTimerTaskStackBuffer,
    uint32_t *pulTimerTaskStackSize
) {
    *ppxTimerTaskTCBBuffer = &timer_task_tcb;
    *ppxTimerTaskStackBuffer = timer_task_stack;
    *pulTimerTaskStackSize = configMINIMAL_STACK_SIZE;
}
#endif
