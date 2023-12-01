#define A1 2
#define A2 3
#define A4 5
#define A5 6
#define A6 7
#define B__1 8
#define B__2 9
#define B__3 10
#define B__4 11
#define B__5 12
#define B__6 13
#define H 1
#define L 0
// 35cm -> 20cm
// 250 : 4 = x : 5
//16개, 2mm -> 한 바퀴에 32mm => 200 : 32 = 250 : 4cm => 0 5 10 15 20
float C1 = 0, C2 = 312, C3 = 625, C4 = 937, C5 = 1248;
int nx=0, s = 254;

const int dirPin = 20;  
const int stepPin = 21;  
int stepsPerRevolution = 200;  
const int stepDelay = 1000; //모터 속도 제어 

//한 바퀴 돌면 3cm 이동, 1step 200

void go()
{
  for(int x = 0; x < stepsPerRevolution; x++)  
    {  
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(stepDelay);
				digitalWrite(stepPin, LOW);
				delayMicroseconds(stepDelay);
    }  
}
  
void setup()  
{  
    pinMode(stepPin, OUTPUT);  
    pinMode(dirPin, OUTPUT);  
    for(int i=4; i<=13; i++)
      pinMode(i, INPUT);
    
    Serial.begin(9600);

    digitalWrite(dirPin, HIGH);
    nx = C3;
    stepsPerRevolution = C3;
    go();
}  

void how(){
  if (nx >= C3) {
    digitalWrite(dirPin, HIGH);
    stepsPerRevolution = nx - C3;
    go();
    delay(500);
    digitalWrite(dirPin, LOW);
    stepsPerRevolution = nx - C3;
    go();
  }
  else {
    digitalWrite(dirPin, LOW);
    stepsPerRevolution = C3 - nx;
    go();
    delay(500);
    digitalWrite(dirPin, HIGH);
    stepsPerRevolution = C3 - nx;
    go();
  }
}

void loop()  
{  
  int a_1 = digitalRead(A1);
  int a_2 = digitalRead(A2);
  int a_3 = digitalRead(A3);
  int a_4 = digitalRead(A4);
  int a_5 = digitalRead(A5);
  int a_6 = digitalRead(A6);
  int b_1 = digitalRead(B__1);
  int b_2 = digitalRead(B__2);
  int b_3 = digitalRead(B__3);
  int b_4 = digitalRead(B__4);
  int b_5 = digitalRead(B__5);
  int b_6 = digitalRead(B__6);

  Serial.print(a_1);
  Serial.print(a_2);
  Serial.print(a_3);
  Serial.print(a_4);
  Serial.print(a_5);
  Serial.print(a_6);
  Serial.print(" ");
  Serial.print(b_1);
  Serial.print(b_2);
  Serial.print(b_3);
  Serial.print(b_4);
  Serial.print(b_5);
  Serial.println(b_6);
  delay(1);

  if(a_1 == H){
    if(b_1 == H) {
      //C1
      nx = C1;
      how();
    }
    else if(b_2 == H) {
      nx = C5;
      how();
    }
    else if(b_3 == H) {
      nx = C2;
      how();
    }
    else if(b_4 == H) {
      nx = C1;
      how();
    }
    else if(b_5 == H) {
      nx = C4;
      how();
    }
    else if(b_6 == H) {
      nx = C3;
      how();
    }
  }
 else if(a_2 == H){
    if(b_1 == H) {
      nx = C1;
      how();
    }
    else if(b_2 == H) {
      nx = C2;
      how();
    }
    else if(b_3 == H) {
      nx = C5;
      how();
    }
    else if(b_4 == H) {
      nx = C4;
      how();
    }
    else if(b_5 == H) {
      nx = C3;
      how();
    }
    else if(b_6 == H) {
      nx = C3;
      how();
    }
  }
  else if(a_3 == H){
    if(b_1 == H) {
      nx = C4;
      how();
    }
    else if(b_2 == H) {
      nx = C5;
      how();
    }
    else if(b_3 == H) {
      nx = C3;
      how();
    }
    else if(b_4 == H) {
      nx = C1;
      how();
    }
    else if(b_5 == H) {
      nx = C2;
      how();
    }
    else if(b_6 == H) {
      nx = C3;
      how();
    }
  }
  else if(a_4 == H){
    if(b_1 == H) {
      nx = C1;
      how();
    }
    else if(b_2 == H) {
      nx = C5;
      how();
    }
    else if(b_3 == H) {
      nx = C1;
      how();
    }
    else if(b_4 == H) {
      nx = C4;
      how();
    }
    else if(b_5 == H) {
      nx = C3;
      how();
    }
    else if(b_6 == H) {
      nx = C3;
      how();
    }
  }
  else if(a_5 == H){
    if(b_1 == H) {
      nx = C1;
      how();
    }
    else if(b_2 == H) {
      nx = C5;
      how();
    }
    else if(b_3 == H) {
      nx = C4;
      how();
    }
    else if(b_4 == H) {
      nx = C1;
      how();
    }
    else if(b_5 == H) {
      nx = C5;
      how();
    }
    else if(b_6 == H) {
      nx = C3;
      how();
    }
  }
}
