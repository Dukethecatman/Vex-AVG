#pragma config(Sensor, in1,    lineFollowL,    sensorLineFollower)
#pragma config(Sensor, in2,    lineFollow,     sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowR,    sensorLineFollower)
#pragma config(Sensor, dgtl1,  stopButton,     sensorTouch)
#pragma config(Sensor, dgtl2,  calButton,      sensorTouch)
#pragma config(Sensor, dgtl3,  spacing,        sensorSONAR_inch)
#pragma config(Sensor, dgtl10, ,               sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, ,               sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, ,               sensorLEDtoVCC)
#pragma config(Motor,  port1,            ,             tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,            ,             tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Project Title:1.2.9 Auto bot thing
Team Members: ME
Date:
Section:


Task Description:
AUTO BOTS DO STUFF

Pseudocode:nani?

SO i dont forget:
line follwer goes to 4095
*/
int Sstop = 0;
int try = 0;//count the fails
int STOP = true;//start off :(
int person = true;//start in HANDS ON
int line = 2000; // defualt number
int care = 0;


void safety(){// Makeing the world safer
	if(SensorValue[stopButton] == 1){
		if(STOP == false){
			STOP = true;
			turnLEDOn(12);
			wait(.25);
		}
		else{
			STOP = false;
			turnLEDOff(12);
			wait(.25);
		}
	}

	if(vexRT[Btn6U] == 1){
		if(person == false){
			person = true;
			turnLEDOn(11);
		}
		else{
			person = false;
			turnLEDOff(11);
		}
	}

	if(vexRT[Btn6D] == 1){
		if(STOP == 0){
			STOP = true;
			turnLEDOn(12);
		}
		else{
			STOP = false;
			turnLEDOff(12);
		}
	}

	if(care ==1){
		if(STOP == false){
			if(SensorValue(spacing) <= 3){
				STOP = true;
				turnLEDOn(12);
				Sstop = 1;
			}
		}

		else{
			if(Sstop == 1){
				if(SensorValue[spacing] != -1){
					if(SensorValue(spacing) > 3){
						Sstop = 0;
						STOP = 0;
						turnLEDOff(12);
					}
				}
			}
		}
	}
}



void waitAMin(){
	if(SensorValue(lineFollow) >= line){
		if(SensorValue(lineFollowL) >= line){
			if(SensorValue(lineFollowR) >= line){
				stopMotor(port2);
				stopMotor(port3);
				stopMotor(port4);
				stopMotor(port5);
				safety();
				wait(1);//SOOOOO LONG I COULD BE DOING STUFF
				safety();
				wait(1);
				safety();
				wait(1);
				safety();
				wait(1);
				safety();
				wait(1);
				safety();
				wait(1);
				startMotor(port2, -65);//dont get stuck
				startMotor(port3, 65);
				startMotor(port4, -65);
				startMotor(port5, 65);
				wait(.10);
			}
		}
	}
}
void FindLine(){//where am I?
	try = 0;
	while(try <= 5){
		waitAMin();
		safety();
		if(person == true){
			break;
		}
		if(	SensorValue[lineFollow] < line){
			startMotor(port2, 100);
			startMotor(port3, 100);
			startMotor(port4, 100);
			startMotor(port5, 100);
		}
		else{
			break;
		}
		wait(.05);
		try = try + 1;
	}
	try = 0;
	while(try <= 10){
		waitAMin();
		safety();
		if(person == true){
			break;
		}
		if(	SensorValue[lineFollow] < line){
			startMotor(port2, -100);
			startMotor(port3, -100);
			startMotor(port4, -100);
			startMotor(port5, -100);
		}
		else{
			break;
		}
		wait(.05);
		try = try + 1;
	}
	try = 0;
}

void cal(){
	if(SensorValue(calButton)== 1){
		line = lineFollow;//git it right
	}
}

void AUTOBOTS(){//Auto function
	if(SensorValue(lineFollow) >= line){//zoom zoom
		safety();
		try = 0;
		startMotor(port2,-65);
		startMotor(port3,65);
		startMotor(port4,-65);
		startMotor(port5,65);
		waitAMin();
		safety();
	}
	else{
		safety();
		FindLine();
	}
}

task main(){                                    //Program begins, insert code within curly braces
	while(1 == 1){//never ending love
		safety();
		cal();
		if(STOP == false){//RUNNING IN tHE 90s
			if(person == true){//hands ON!
				startMotor(port2,-vexRT[Ch2]);
				startMotor(port3,vexRT[Ch3]);
				startMotor(port4,-vexRT[Ch2]);
				startMotor(port5,vexRT[Ch3]);
			}
			else{// Autobots
				AUTOBOTS();
			}
		}
		else{//DEAD STOP
			stopMotor(port2);
			stopMotor(port3);
			stopMotor(port4);
			stopMotor(port5);
			safety();
		}
	}
}
