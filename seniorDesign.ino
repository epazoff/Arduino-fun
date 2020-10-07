//REMEMBER TO CHANGE FILE NAMES BETWEEN TESTS

//pins:
//flowmeter in connected to PWR (5V), GND, and D4
//flowmeter out connected to PWR (5V), GND, and D5
//SD/SPI:
//MOSI=D11
//MISO=D12
//SCK=D13
//CS=D10
//motor (ch A) connected to:
//Direction=D7
//PWM=D3
//Brake=D9
//Current Sensing=A0
//Voltage Sensing=A2

#include <SD.h>
#include <SPI.h>
File myFile;

int pinCS = 10; //D10, chip select
int flowsensor_i = 4; //D4, yellow wire
int flowsensor_e = 5; //D5, yellow wire
int PWM_a = 3; //D3, pwm (speed) on motor shield
int dir_a = 7; //D7, direction on motor shield (changed on hardware)
int cur_a = A0; //A0, current sensing from motor shield
int volt_a = A2; //A2, voltage divider circuit

int time_delay = 100; //time between each sample in milliseconds

int pwm_value_i;
int pwm_value_e;

int current;

int voltage;

int spd; //motor speed (0-255)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(flowsensor_i, INPUT);
  pinMode(flowsensor_e, INPUT);
  pinMode(pinCS, OUTPUT);
  pinMode(PWM_a, OUTPUT);
  pinMode(dir_a, OUTPUT);

  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
  } else {
    Serial.println("SD card initialization failed");
    return;
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  spd=255;
  analogWrite(PWM_a, spd); //set motor speed
  digitalWrite(dir_a,HIGH); //set motor direction

  pwm_value_i = pulseIn(flowsensor_i, HIGH); //opt: pulseIn(pin,HIGH/LOW,timeout), automatic timeout is 1 microsecond
  pwm_value_e = pulseIn(flowsensor_e, HIGH);

  current = analogRead(cur_a);
  voltage = analogRead(volt_a);

  //have serial print all stuff first
  Serial.print("Time: ");
  Serial.print(millis()); //unsigned long
  Serial.print(", PWM in: ");
  Serial.print(pwm_value_i); //unsigned long
  Serial.print(", PWM out: ");
  Serial.print(pwm_value_e); //unsigned long
  Serial.print(", Voltage: ");
  Serial.print(voltage);
  Serial.print(", Current: ");
  Serial.println(current);

  myFile = SD.open("test.txt", FILE_WRITE); //must be 8.3 filetype, can save as .csv?
  if (myFile) {
    Serial.println("Writing to file...");
    myFile.print(millis()); //time?
    myFile.print(", "); //delimiter
    myFile.print(pwm_value_i); //time in microseconds between pulses
    myFile.print(", "); //delimiter
    myFile.print(pwm_value_e); //time in microseconds between pulses
    myFile.print(", "); //delimiter
    myFile.print(voltage); //voltage of motor
    myFile.print(", "); //delimiter
    myFile.println(current); //current
    myFile.close();
  } else {
    Serial.println("Error opening file");
  }
  delay(time_delay);

}
