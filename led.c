#include <wiringPi.h>
#include "led.h"

uchar led_pos[4]={0x01, 0x02, 0x04, 0x08};
uchar led_tab[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void led_gpio_init()
{
	pinMode(SCLK, OUTPUT);
	pinMode(RCLK, OUTPUT);
	pinMode(LEDDATA, OUTPUT);
}

void led_out(uchar data)
{
	int i;
	for(i=0; i<8; i++) {
		if( data&0x80 )
			digitalWrite(LEDDATA, HIGH);
		else
			digitalWrite(LEDDATA, LOW);
		digitalWrite(SCLK, LOW);
		digitalWrite(SCLK, HIGH);
		digitalWrite(SCLK, LOW);
		data <<= 1;
	}
}

void led_display(int ult_speed)
{
	int i;
	for(i=0; i<3; i++) {
		led_out(led_tab[ult_speed%10]);
		led_out(led_pos[i]);
		ult_speed /= 10;
		digitalWrite(RCLK, LOW);
		digitalWrite(RCLK, HIGH);
		digitalWrite(RCLK, LOW);
	}
	led_out(led_tab[ult_speed%10] & 0x7f);
	led_out(led_pos[i]);
	ult_speed /= 10;
	digitalWrite(RCLK, LOW);
	digitalWrite(RCLK, HIGH);
	digitalWrite(RCLK, LOW);
}
