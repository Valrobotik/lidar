#include "lidar.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <bcm2835.h>

#include <stdio.h>

#define MAX_VALUE 4000
#define MAX_LEN 15
#define OFFSET_LEN 7

#define MAX_HEIGHT 5
#define OFFSET_HEIGHT 3.5

void	linear_display(void)
{
	int i = 0;

	double factorx = g_size / MAX_LEN;
	//double factory = f_max(g_range, g_size) / MAX_HEIGHT;
	double factory = MAX_VALUE / MAX_HEIGHT;
	glBegin(GL_LINE_STRIP);
		while (i < g_size)
		{
			glVertex2d((double)(i/factorx) - OFFSET_LEN,
					(double)(g_range[i]/factory) - OFFSET_HEIGHT);
			i++;
		}
	glEnd();
}

void	polar_display(double start, double end)
{
	int 	i = 0;
	double	ray;
	(void)start;
	(void)end;

	start = 0;
	end = 4.1888;
	//double factory = f_max(g_range, g_size) / MAX_HEIGHT;
	//double factory = MAX_VALUE / (MAX_HEIGHT);
	glBegin(GL_LINE_STRIP);
		while (i < g_size)
		{
			ray = (double)(g_range[i] * MAX_HEIGHT) / MAX_VALUE / 1.1;
			glVertex2d(ray * cos(start + (i * (end - start)) / g_size), ray * sin((start + i * (end - start)) / g_size));
			//glVertex2d(ray * cos((i * M_PI * 2) / g_size), ray * sin((i * M_PI * 2) / g_size));
			i++;
		}
	glEnd();

}

void	light_led(int pin, int status)
{
	if (status < 10)
		bcm2835_gpio_clr(pin);
	else
		bcm2835_gpio_set(pin);
}

void	led_stop()
{
	int	i;
	int	led;
	int	distlast;

	distlast = 0;
	led = 0;
	i = 0;
	while (i < g_size)
	{
		if (g_range[i] > 100 && g_range[i] < 300)
		{
			distlast = g_range[i];
			led++;
		}
		i++;
	}
	light_led(PINOUT, led);
	printf("led value = %d range:%d\n", led, distlast);
}
