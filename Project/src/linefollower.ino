/* See LICENSE file for copyright and license details. */
#include <Arduino.h>
#include "config.h"
#include "control.h"
#include "sensor.h"

/* type definitions */
typedef enum { LEFT, RIGHT, STRAIGHT } Direction;

/* variable definitions */
static const size_t sensor_count = LENGTH(sensor_ports);
static bool calibrate = true;
static uint8_t cycle = 0;

/* initialize motor,servo and sensors */
AF_DCMotor *motor = new AF_DCMotor(motor_port, MOTOR_FREQUENCY);
Servo *servo = new Servo;
Sensor sensor = init_sensors(sensor_led_pin, sensor_ports);

void
setup(void) {
	pinMode(led_pin, OUTPUT);
	pinMode(calibrate_button, INPUT_PULLUP);    /* enable pullup-resistor */

	servo->attach(servo_port);
	servo->write(90);
}

/* main loop */
void
loop(void) {
	bool *position;
	Direction correction = STRAIGHT;

	if(digitalRead(calibrate_button) == HIGH) {
		calibrate = true;
		stop(motor);

		return;
	}

	if(calibrate) {
		blink(led_pin);
		cycle = 0;
		calibrate_sensors(&sensor, calibrate_passes, read_passes);
		forward(motor, motor_speed);
		calibrate = false;
	}

	position = get_line_position(&sensor, contrast_threshold, read_passes);
	correction = correct_vehicle(servo, position, correction);

	//delay(50);
	/*if(Serial.available() > 0) {
		switch(Serial.read()) {
			case 108:
			servo->write(115);
			break;
			case 114:
			servo->write(50);
			break;
		}
	}*/
}

/* control servo based on position */
Direction
correct_vehicle(Servo *s, bool *position, Direction dir) {

	if(position[0] && (dir != RIGHT)) {
		right(s, servo_straight_angle, servo_max_steering_angle);
		return RIGHT;
	}

	if(position[(LENGTH(sensor_ports) - 1)] && (dir != LEFT)) {
		left(s, servo_straight_angle, servo_max_steering_angle);
		return LEFT;
	}

	straight(s, servo_straight_angle);

	return STRAIGHT;
}

/* blink to indicate calibration */
void
blink(uint8_t pin) {
	for(uint8_t i = 0; i < 8; i++) {
		digitalWrite(pin, HIGH);
		delay(80);
		digitalWrite(pin, LOW);
		delay(80);
	}
}

