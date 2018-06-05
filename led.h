#ifndef LED_H
#define LED_H

#define SCLK 3
#define RCLK 2
#define LEDDATA 0
#define DOTMASK 3

typedef unsigned char uchar;

void led_gpio_init();
void led_out(uchar data);
void led_display(int ult_speed);

#endif
