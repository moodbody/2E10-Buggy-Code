

const int LEFT_MOTOR_PWM = D6;
const int RIGHT_MOTOR_PWM = D5;

// D8 and D9 Control Left Motor
const int LEFT_MOTOR_DIRECTION[2] = {D9,D8};

// D10 and D11 Control Right Motor
const int RIGHT_MOTOR_DIRECTION[2] = {D10,D11};

//D2 is Echo
const int US_ECHO = 2;
const int US_TRIG = 3;
//D3 is Trig


const int LEYE = D12;
const int REYE = D13;
bool irState[2];

void setup() {
  Serial.begin(9600);

  pinMode( LEYE, INPUT );
  pinMode( REYE, INPUT );
  irState[0] = digitalRead(LEYE);
  irState[1] = digitalRead(REYE);

  // Set PWM Motor Speed
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  

  pinMode(LEFT_MOTOR_DIRECTION[0], OUTPUT);
  pinMode(LEFT_MOTOR_DIRECTION[1], OUTPUT);
  pinMode(RIGHT_MOTOR_DIRECTION[0], OUTPUT);
  pinMode(RIGHT_MOTOR_DIRECTION[1], OUTPUT);

  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);


}

void leftMotorForward(int speed) {
  digitalWrite(LEFT_MOTOR_DIRECTION[0],HIGH);
  digitalWrite(LEFT_MOTOR_DIRECTION[1],LOW);
  analogWrite(LEFT_MOTOR_PWM,speed);
}

void leftMotorBackward(int speed) {
  digitalWrite(LEFT_MOTOR_DIRECTION[0],LOW);
  digitalWrite(LEFT_MOTOR_DIRECTION[1],HIGH);
  analogWrite(LEFT_MOTOR_PWM,speed);
}

void rightMotorForward(int speed) {
  digitalWrite(RIGHT_MOTOR_DIRECTION[0],HIGH);
  digitalWrite(RIGHT_MOTOR_DIRECTION[1],LOW);
  analogWrite(RIGHT_MOTOR_PWM,speed);
}

void rightMotorBackward(int speed) {
  digitalWrite(RIGHT_MOTOR_DIRECTION[0],LOW);
  digitalWrite(RIGHT_MOTOR_DIRECTION[1],HIGH);
  analogWrite(RIGHT_MOTOR_PWM,speed);
}

void leftMotorStop() {
  digitalWrite(LEFT_MOTOR_DIRECTION[0],LOW);
  digitalWrite(LEFT_MOTOR_DIRECTION[1],LOW); 
}

void rightMotorStop() {
  digitalWrite(RIGHT_MOTOR_DIRECTION[0],LOW);
  digitalWrite(RIGHT_MOTOR_DIRECTION[1],LOW); 
}

void stopMotors() {
  leftMotorStop();
  rightMotorStop();
}

void loop() {

   //UltraSonic
  int distance;
  long duration;

  digitalWrite( US_TRIG, LOW );
  delayMicroseconds(2);
  digitalWrite( US_TRIG, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( US_TRIG, LOW );

  duration = pulseIn( US_ECHO, HIGH );

  distance = duration/58;

  irState[0] = digitalRead(LEYE);
  irState[1] = digitalRead(REYE);
  //Change the value below to change stopping distance
if(distance < 20){
  //leftMotorBackward(150);
  //rightMotorBackward(120);
//}else if (distance > 10 && distance < 20){
  stopMotors();
}
else {
  //Speed of buggy needs optimising

/*
%%%%IDEA%%%%
  Using if/else to create a seciton that changes the 
  speed/turning radius of the buggy depending on the 
  amount of the the IR sensors are over the white
  */

  if(irState[0] == HIGH && irState[1] == HIGH) {
    // On the white path
    leftMotorForward(215);
    rightMotorForward(145);
  } else if(irState[0] == LOW && irState[1] == LOW) {
    // Not on any path
    stopMotors();
  } else if(irState[0] == LOW && irState[1] == HIGH) {
    // Turn Left
    rightMotorForward(135);
    leftMotorStop();
  } else {
    // Turn Right 
    leftMotorForward(200);
    rightMotorStop();
  }
}
  
  Serial.print("Distance detected: ");
  Serial.print( distance );
  Serial.println(" cm");


  delay(50);
}