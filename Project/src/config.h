/* See LICENSE file for copyright and license details. */
/* Configuration options */

/* Motor parameters */
/* port, to which the motor is connected (1-4) */
static const uint8_t motor_port = 1;

/* PWM frequency used to drive the motor,
 * options from AFMotor.h:
 *     MOTOR12_1KHZ
 *     MOTOR12_2KHZ    Only ports 1 & 2
 *     MOTOR12_8KHZ    Only ports 1 & 2
 *     MOTOR12_64KHZ   Only ports 1 & 2
 */
#define MOTOR_FREQUENCY MOTOR12_1KHZ

/* motor speed */
static const uint8_t motor_speed = 95;


/* Servo parameters */
/* servo control-pin (servo port1: 9; servo port2: 10) */
static const uint8_t servo_port = 10;

/* set straight steering angle (normal 90 degree) */
static const int servo_straight_angle =  90;

/* max steering angle (from middle to left/right) */
static const int servo_max_steering_angle = 30;


/* Sensor parameters */
/* sensor analog ports */
static const uint8_t sensor_ports[] = {A0, A1, A2};

/* Pin to power the sensor-leds */
static const uint8_t sensor_led_pin = 6;

/* minimal difference between light and dark for detecting line change */
static const uint8_t contrast_threshold = 5;

/* button for calibrating */
static const uint8_t calibrate_button = 3;

/* iteration count for calibration */
static const uint8_t calibrate_passes = 10;

/* iteration count for sensor readings */
static const uint8_t read_passes = 35;



/* Miscellaneous options */
/* control-led port */
static const uint8_t led_pin = 13;

