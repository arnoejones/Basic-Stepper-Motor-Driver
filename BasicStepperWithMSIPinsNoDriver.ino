/*
A4988 & 8825 hookups different from EasyDriver board:
5v -> RST (pin 5)
5v -> SLP (pin 6)
*/
#define step_pin 2  // Pin 3 connected to Steps pin on EasyDriver
#define dir_pin 3   // Pin 2 connected to Direction pin
#define MS0
#define MS1 10  // Pin 5 connected to MS1 pin
#define MS2 9   // Pin 4 connected to MS2 pin
#define MS3 8

#define CW LOW
#define CCW HIGH

#define byte fullStep 0b000
#define byte halfStep 0b001
#define byte quarterStep 0b010
#define byte eighthStep 0b011
#define byte sixteenthStep 0b100
#define byte thirtytwoStep 0b101

int step_time_delay = 1000;
int count = 0;
void runMotor(bool direction, int steps, int step_time_delay, bool ms1, bool ms2, bool ms3) {
  digitalWrite(dir_pin, direction);
  digitalWrite(MS1, ms1);
  digitalWrite(MS2, ms2);
  digitalWrite(MS3, ms3);

  while (count <= steps) {
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(step_time_delay);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(step_time_delay);
    count++;
  }
  count = 0;
  return;
}

void setup() {
  Serial.begin(115200);
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
}

/*
Using DRV8825 stepper driver 
Data sheet: https://www.ti.com/lit/ds/symlink/drv8825.pdf
MS1	  MS2	  MS3	    Microstep Resolution
Low	  Low	  Low	    Full step
Low   Low	  High	  Half step
Low	  High	Low	    Quarter step
Low   High	High	  Eighth step
High  Low   Low     Sixteenth step
High  Low	  High    32nd step  (not available on A4988 (Big Easyddriver))
*/
void loop() {
  /**** 200 steps for 360º *******/
  runMotor(CW, 200, step_time_delay, LOW, LOW, LOW);
  Serial.println("200 CW");
  delay(100);
  runMotor(CCW, 200, step_time_delay, LOW, LOW, LOW);
  Serial.println("200 CCW");
  delay(100);

  /****** 400 steps for 360º ********/
  runMotor(CW, 200 * 2, step_time_delay, HIGH, LOW, LOW);
  Serial.println("400 CW");
  delay(100);
  runMotor(CCW, 200 * 2, step_time_delay, HIGH, LOW, LOW);
  Serial.println("400 CCW");
  delay(100);

  /****** 400 steps for 360º ********/
  runMotor(CW, 200 * 4, step_time_delay, LOW, HIGH, LOW);
  Serial.println("800 CW");
  delay(100);
  runMotor(CCW, 200 * 4, step_time_delay, LOW, HIGH, LOW);
  Serial.println("800 CCW");
  delay(100);

  /******** 800 steps for 360º ********/
  runMotor(CW, 200 * 8, step_time_delay, HIGH, HIGH, LOW);
  Serial.println("1600 CW");
  delay(100);
  runMotor(CCW, 200 * 8, step_time_delay, HIGH, HIGH, LOW);
  Serial.println("1600 CCW");
  delay(100);

  /******* 1600 steps for 360º ********/
  /*** DRV8825 need a multiplier of 32 to 3200 step***/
  runMotor(CW, 200 * 16, step_time_delay, LOW, LOW, HIGH);
  Serial.println("3200 CW");
  delay(100);
  runMotor(CCW, 200 * 16, step_time_delay, LOW, LOW, HIGH);
  Serial.println("3200 CCW");
  delay(500);

  /******* 3200 steps for 360º ********/
  runMotor(CW, 200 * 32, step_time_delay, HIGH, LOW, HIGH);
  Serial.println("3200 CW");
  delay(100);
  runMotor(CCW, 200 * 32, step_time_delay, HIGH, LOW, HIGH);
  Serial.println("3200 CCW");
  delay(500);
}
