#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/spi_master.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#include "soc/soc.h"
#include "soc/dport_reg.h"
#include "soc/uart_struct.h"

#define ECHO_TEST_TXD  (GPIO_NUM_5)
#define ECHO_TEST_RXD  (GPIO_NUM_4)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)

// #define PIN_NUM_MOSI    18
// #define PIN_NUM_CLK     19
// #define PIN_NUM_CS      23

// static spi_device_handle_t spi;

#define SPI_BURST_MAX_LEN (16 * 1024)  // Maximum pixel data transferred at a time

#define BUF_SIZE (1024)

static void uart_init(void)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);
}

void freq_det_init(void)
{
    UART1.auto_baud.en = 0;
    UART1.auto_baud.en = 1;

    while(UART1.rxd_cnt.edge_cnt < 100); 
    uint32_t hight_cnt = UART1.highpulse.min_cnt;
    uint32_t ful_cnt = UART1.pospulse.min_cnt;
    UART1.auto_baud.en = 0;
    uint32_t freq = 80000000 / ful_cnt;
    float duty = 1.0*hight_cnt / ful_cnt;

    // printf("ful_cnt: %d  high_cnt: %d\n", ful_cnt, hight_cnt);
    printf("freq: %dHz,   duty %.4f\n", freq, duty);
}

void app_main(void)
{
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_LOW_SPEED_MODE,           // timer mode
        .timer_num = LEDC_TIMER_1,            // timer index
        .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
    };
    // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);
    ledc_channel_config_t ledc_channel = {
            .channel    = LEDC_CHANNEL_0,
            .duty       = 4095,  // duty = ledc_channel.duty / (2 ^ ledc_timer.)
            .gpio_num   = 18,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER_1,
    };
    ledc_channel_config(&ledc_channel);
    uart_init();
    // uint32_t pwm_high_cnt = 0;
    // uint32_t pwm_low_cnt  = 0;
    while(1) {
        // UART1.auto_baud.en = 1;
        // UART1.auto_baud.glitch_filt = 0;
        // vTaskDelay(50/portTICK_PERIOD_MS);
        // while(UART1.rxd_cnt.edge_cnt < 100);
        

        // pwm_high_cnt = UART1.highpulse.min_cnt;
        // pwm_low_cnt  = UART1.lowpulse.min_cnt;
        
        // uint32_t full_circle = UART_CLK_FREQ / (pwm_high_cnt + pwm_low_cnt);
        
        // float duty = (float)pwm_high_cnt / (pwm_high_cnt + pwm_low_cnt) * 100;

        // printf("high: %d      low: %d    circle:%dHz   duty: %f%%\n", pwm_high_cnt, pwm_low_cnt, full_circle, duty);
        // UART1.highpulse.min_cnt = 0;
        // UART1.lowpulse.min_cnt = 0;
        // UART1.auto_baud.en = 0;
        // vTaskDelay(50 / portTICK_PERIOD_MS);
        freq_det_init();
        vTaskDelay(50 / portTICK_PERIOD_MS);
    
    }
}
