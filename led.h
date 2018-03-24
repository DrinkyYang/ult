#ifndef LED_H
#define LED_H

#define SCLK 21
#define RCLK 22
#define LEDDATA 23

typedef unsigned char uchar;

//uchar led_pos[4]={0x01, 0x02, 0x04, 0x08};
//uchar led_tab[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void led_gpio_init();
void led_out(uchar data);
void led_display(int ult_speed);

#endif
