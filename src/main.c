#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    pal,            sensorPotentiometer)
#pragma config(Sensor, in2,    par,            sensorPotentiometer)
#pragma config(Sensor, in3,    ps,             sensorPotentiometer)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           shu,           tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           fl,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           fr,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           bl,            tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port5,           br,            tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port6,           al,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           ar,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           sp,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           in,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          shd,           tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

#define PA_LOW_POLE 900
#define PA_HIGH_POLE 1370
#define PA_SAFE 2000
#define PS_PARALLEL 700
#define PS_SAFE 2100

#define PA_VALUE ((SensorValue(pal) + SensorValue(par)) / 2)

// #define RED

short pa_target;
byte arm;
short ps_target;
byte sprocket;
short pa_prev;

void pre_auton() {
	resetMotorEncoder(bl);
	resetMotorEncoder(br);
}

#define drive(x) motor[fl] = motor[fr] = motor[bl] = motor[br] = x
#define left(x) motor[fl] = motor[bl] = x
#define right(x) motor[fr] = motor[br] = x
#define drive_enc ((nMotorEncoder(bl) + nMotorEncoder(br)) / 2)

void reset_both() {
	resetMotorEncoder(bl);
	resetMotorEncoder(br);
}

task auto_arm_up();
task auto_arm_down();
task auto_sp_down();
task auto_sp_up();

task autonomous() {
	motor[in] = 127;
	motor[shu] = motor[shd] = 127;
	sleep(1200);
	motor[shu] = motor[shd] = 0;
	startTask(auto_arm_up);
	startTask(auto_sp_down);
	reset_both();
	reset_both();
	drive(127);
#ifdef RED
	while (drive_enc < 1300);
#else
	while (drive_enc < 1300);
#endif
	drive(0);
	reset_both();
#ifdef RED
	left(-127);
	while (nMotorEncoder(bl) > -50);
	left(0);
#else
	right(-127);
	while (nMotorEncoder(br) > -50);
	right(0);
#endif

	startTask(auto_arm_down);
	startTask(auto_sp_up);
	reset_both();
	drive(-127);
#ifdef RED
	while (drive_enc > -1530);
#else
	while (drive_enc > -1700);
#endif
	drive(0);
	reset_both();
#ifdef RED
	left(-127);
	while (nMotorEncoder(bl) > -1050);
	left(0);
#else
	right(-127);
	while (nMotorEncoder(br) > -1000);
	right(0);
#endif
	reset_both();
	drive(-127);
	while (drive_enc > -1800);
	drive(0);

	/*
	right(-127);
	while (nMotorEncoder(br) > -1200);
	right(0);
	left(-127);
	while (nMotorEncoder(bl) > -1200);
	left(0);
	reset_both();
	drive(-127);
	while (drive_enc > -2000);
	drive(0);
	*/
}

task auto_arm_up() {
	motor[al] = motor[ar] = 127;
	while (PA_VALUE < 100);
	motor[al] = motor[ar] = 0;
}

task auto_arm_down() {
	motor[al] = motor[ar] = -127;
	while (PA_VALUE > 0);
	motor[al] = motor[ar] = 0;
}

task auto_sp_down() {
	motor[sp] = -127;
	while (SensorValue(ps) > 200);
	motor[sp] = 0;
}

task auto_sp_up() {
	motor[sp] = 127;
	while (SensorValue(ps) < 1800);
	motor[sp] = 0;
}

float battery;

task usercontrol() {
	while (1) {
		battery = nImmediateBatteryLevel * 0.001;
		if (sgn(PA_VALUE - pa_target) == sgn(arm)) {
			pa_target = 0;
			arm = 0;
		}
		if (sgn(SensorValue(ps) - ps_target) == sgn(sprocket)) {
			ps_target = 0;
			sprocket = 0;
		}
		if ((abs(vexRT[Ch3Xmtr2]) > 20 || abs(vexRT[Ch2Xmtr2]) > 20)
			&& abs(vexRT[Ch3]) < 20 && abs(vexRT[Ch2]) < 20) {
			motor[fl] = motor[bl] = vexRT[Ch3Xmtr2];
			motor[fr] = motor[br] = vexRT[Ch2Xmtr2];
		} else {
			motor[fl] = motor[bl] = vexRT[Ch3];
			motor[fr] = motor[br] = vexRT[Ch2];
		}
		motor[in] = vexRT[Btn6UXmtr2] ? 127 : vexRT[Btn6DXmtr2] ? -127 : vexRT[Btn8UXmtr2] ? 40 : 0;
		motor[shu] = motor[shd] = vexRT[Btn5UXmtr2] * 127;
		if (vexRT[Btn6U]) {
			if (PA_VALUE < PA_SAFE) {
				motor[al] = motor[ar] = 127;
				pa_target = 0;
				arm = 0;
			}
		} else if (vexRT[Btn6D]) {
			motor[al] = motor[ar] = -127;
			pa_target = 0;
			arm = 0;
		} else if (pa_target) {
			motor[al] = motor[ar] = arm;
		} else {
			motor[al] = motor[ar] = 0;
		}
		if (vexRT[Btn5U]) {
			motor[sp] = 127;
			ps_target = 0;
			sprocket = 0;
		} else if (vexRT[Btn5D]) {
			motor[sp] = -127;
			ps_target = 0;
			sprocket = 0;
		} else if (ps_target) {
			motor[sp] = sprocket;
		} else {
			motor[sp] = 0;
		}
		if (vexRT[Btn8D] && !pa_target) {
			pa_target = PA_LOW_POLE;
			arm = PA_VALUE < pa_target ? 127 : -127;
		}
		if (vexRT[Btn8R] && !pa_target) {
			pa_target = PA_HIGH_POLE;
			arm = PA_VALUE < pa_target ? 127 : -127;
		}
		if (vexRT[Btn7D] && !ps_target
			|| pa_prev > 1000 && PA_VALUE <= 1000 && SensorValue(ps) > PS_SAFE) {
			ps_target = PS_PARALLEL;
			sprocket = SensorValue(ps) < ps_target ? 127 : -127;
		}
		pa_prev = PA_VALUE;
	}
}
