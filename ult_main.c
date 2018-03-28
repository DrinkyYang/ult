#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <wiringPi.h>
#include <sys/time.h>
#include <math.h>

#include "led.h"

#define TRIG 4
#define ECHO 5
#define ALARM 1

pthread_mutex_t lock_ult;
float ult_speed,ult_dis;
float alarm_speed = 1;

void *ult(void *arg)
{
	struct timeval t1,t2;
	long time_start, time_stop, time_old, time_new;
	float dis_old, dis_new, dis_temp;
	bool startflag=0;
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	while(1) {
		digitalWrite(TRIG, LOW);
		digitalWrite(TRIG, HIGH);
		delayMicroseconds(15);
		digitalWrite(TRIG, LOW);
		while(1) {
			if (digitalRead(ECHO) == 1)
				break;
		}
		gettimeofday(&t1, NULL);
		while(1) {
			if(digitalRead(ECHO) == 0)
				break;
		}
		gettimeofday(&t2, NULL);
		time_start = t1.tv_sec * 1000000 + t1.tv_usec;
		time_stop = t2.tv_sec * 1000000 + t2.tv_usec;
		dis_temp = (float)(time_stop - time_start) /1000000 * 340 / 2;
		
		if(dis_temp < 10.0) {
                        if(startglag) {
                                dis_old = dis_new;
                                time_old = time_new;
                        }
                        else
                                startflag = 1;
                        dis_new = dis_temp;
                        time_new = (time_stop - time_start)/2 + time_start;
                        
                        pthread_mutex_lock(&lock_ult);
                        ult_dis = dis_new;
                        ult_speed = (fabs)(dis_new - dis_old) / ((float)(time_new - time_old) / 1000000);
                        printf("dis:%f m, speed:%f m/s\n", ult_dis, ult_speed);
                        pthread_mutex_unlock(&lock_ult);
                }
		delay(500);
	}
}

void *led_disp(void *arg)
{
	int speed_disp;
	led_gpio_init();
	while(1) {
		pthread_mutex_lock(&lock_ult);
		speed_disp = (int)(ult_speed*1000);
		pthread_mutex_unlock(&lock_ult);
		led_display(speed_disp);		
	}
}

int main()
{
	float speed;
	bool phflag=0;
	wiringPiSetup();
	pinMode(ALARM, OUTPUT);
	pthread_t ult_data,ult_disp;
	pthread_create(&ult_data,NULL,ult,NULL);
	pthread_create(&ult_disp,NULL,led_disp,NULL);
	int i=0;
	while(1)
	{
		pthread_mutex_lock(&lock_ult);
		speed=ult_speed;
		pthread_mutex_unlock(&lock_ult);
		if(speed > alarm_speed) {
                        digitalWrite(ALARM, LOW);
                        if(!phflag) {
                                system("raspistill -t 200 -o photo/$(date +%Y%m%d%H%M%S).jpg -w 640 -h 480");
                                phflag = 1;
                        }
                }
                else {
                        digitalWrite(ALARM, HIGH);
                        phflag = 0;
                }
		delay(500);
	}
	return 0;
}
