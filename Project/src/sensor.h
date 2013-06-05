/* See LICENSE file for copyright and license details. */
/* Basic funtions for controlling the sensor bar */

#include <Arduino.h>        /* Standard Arduino header file */

/* get array element count at compile time */
#define LENGTH(X) (sizeof(X) / sizeof(X[0]))

/* type definitions  */
typedef struct {
	const uint8_t led_pin;
	const uint8_t *analog_pins; /* pointer to array */
	unsigned int *start_values; /* pointer to array */
} Sensor;


/* initialize sensor array */
Sensor
init_sensors(const uint8_t led_pin, const uint8_t *inputs) {
	static unsigned int start_values[LENGTH(sensor_ports)];
	Sensor s = { led_pin, inputs, &start_values[0] };

	pinMode(led_pin, OUTPUT);
	digitalWrite(led_pin, HIGH);

	return s;
}

/* read sensor array */
unsigned int *
read_sensors(Sensor *s, const uint8_t passes) {
	static unsigned int readings[LENGTH(sensor_ports)];

	for(uint8_t i = 0; i < passes; i++) {
		for(uint8_t j = 0; j < LENGTH(readings); j++)
			readings[j] = readings[j] + analogRead(s->analog_pins[j]);
	}

	for(uint8_t i = 0; i < LENGTH(readings); i++)
		readings[i] = readings[i] / passes;

	return readings;
}

/* calibrate sensors */
void
calibrate_sensors(Sensor *s, const uint8_t calibrate_passes, const uint8_t read_passes) {
	unsigned int *readings;

	for(uint8_t i = 0; i < LENGTH(sensor_ports); i++)
		s->start_values[i] = 0;

	for(uint8_t i = 0; i < calibrate_passes; i++) {
		readings = read_sensors(s, read_passes);
		for(uint8_t j = 0; j < LENGTH(sensor_ports); j++)
			s->start_values[j] = s->start_values[j] + readings[j];
	}

	for(uint8_t i = 0; i < LENGTH(sensor_ports); i++)
		s->start_values[i] = s->start_values[i] / calibrate_passes;
}

/* get the position of the line under the sensors */
bool *
get_line_position(Sensor *s, const uint8_t contrast_threshold, const uint8_t read_passes) {
	static bool position[LENGTH(sensor_ports)];
	unsigned int *readings = read_sensors(s, read_passes);

	for(uint8_t i = 0; i < LENGTH(sensor_ports); i++) {
		if(abs(((int) s->start_values[i] - (int) readings[i])) >= contrast_threshold)
			position[i] = true;
		else
			position[i] = false;
	}

	return position;
}
