/* See LICENSE file for copyright and license details. */
/* Basic vehicle control functions, including motor and servo control */

#include <Arduino.h>        /* Standard Arduino header file */
#include <Servo.h>          /* Standard Servo library */
#include "AFMotor.h"

/* motor specific funtions */
void
forward(AF_DCMotor *m, uint8_t speed) {
	m->run(FORWARD);
	m->setSpeed(speed);
}

void
backward(AF_DCMotor *m, uint8_t speed) {
	m->run(BACKWARD);
	m->setSpeed(speed);
}

void
stop(AF_DCMotor *m) {
	m->run(RELEASE);
}

/* servo specific functions */
/*Servo *
servo_init(const uint8_t pin) {
	Servo *s = new Servo;
	s->attach(pin);
	s->write(90);
	return s;
}*/

void
left(Servo *s, const uint8_t base_angle, const uint8_t left_angle) {
	//s->write(base_angle + left_angle);
	s->write(110); //125
}

void
right(Servo *s, const uint8_t base_angle, uint8_t const right_angle) {
	//s->write(base_angle - right_angle);
	s->write(50); //45
}

void
straight(Servo *s, const uint8_t base_angle) {
	s->write(base_angle);
}
