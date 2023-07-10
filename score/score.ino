#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>
#include <stdlib.h>
#include <string.h>
#include <Stream.h>
#include <math.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

#define START_BUTTON 32
#define LINE_LED 30
#define BUZZER 34

int s_btn, s_flag = 1;
int past = 0, time = 0, now = millis(), start = 0, flag[2] = {1, 1}, ok_end = 0;
int c_robot = 0, c_human = 0;
unsigned long past_led = 0, time_led = 0, now_led = micros();
int FND[12][12] = {{1, 0, 0, 0, 0, 0, 0}, 
                   {1, 1, 1, 1, 0, 0, 1},
                   {0, 1, 0, 0, 1, 0, 0},
                   {0, 1, 1, 0, 0, 0, 0},
                   {0, 0, 1, 1, 0, 0, 1},
                   {0, 0, 1, 0, 0, 1, 0},
                   {0, 0, 0, 0, 0, 1, 0},
                   {1, 0, 1, 1, 0, 0, 0}
                  };

int s_song = 1, e_song = 1;

int start_melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

int end_melody[] = {
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
  NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

int s_notes=sizeof(start_melody)/sizeof(start_melody[0])/2; 
int s_wholenote = (60000 * 4) / 144;
int s_divider = 0, s_noteDuration = 0;

int notes = sizeof(end_melody) / sizeof(end_melody[0]) / 2;
int divider = 0, noteDuration = 0;

int size = sizeof(underworld_melody) / sizeof(int);

/*
시작
스타트 버튼 입력 = 1
SCORE 사람, 로봇 0으로 초기화 
FND 0-0 출력
라인 LED 3번 깜빡이기 -> 점등 유지
3분 카운트
테트리스 노래 출력
*/

/*
끝
스타트 버튼 = 0
SCORE FND 5초 간 출력
라인 LED 3번 깜빡이기 -> 소등
팩맨 노래 출력
*/

void setup(){
    Serial.begin(19200);
    pinMode(START_BUTTON, INPUT_PULLUP);
    pinMode(LINE_LED, 1);
    pinMode(BUZZER, 1);

    pinMode(1, 0);
    pinMode(2, 0);
    for(int i=3; i<=13; i++)
        pinMode(i, 1);
    for(int i=22; i<=28; i++)
        pinMode(i, 1);

    digitalWrite(13, 0);

    for(int i=10; i<=12; i++)
      digitalWrite(i, 1);
}

void loop(){
    //시작 스위치를 누르면!!
    if(digitalRead(START_BUTTON) == 0){
        start = 1;
        ok_end = 1;
        c_human = 0;
        c_robot = 0;
    }

    if(start){
        if(now-past >= 180000){ //3분이 지나면
            start = 0; //start = 0이고
            goto end; //끝 지점으로 감
        }
        if(c_robot == 7 || c_human == 7){ //7점을 내면
            start = 0; //start = 0이고
            goto end; //끝 지점으로 감
        }
        //라인 LED 3번 깜빡이기
        for(int i=0; i<3; i++){
            digitalWrite(LINE_LED, 1);
            delay(200);
            digitalWrite(LINE_LED, 0);
            delay(200);
        }
        digitalWrite(LINE_LED, 1);

        //테트리스 bgm
        if(s_song){
          int s_size = sizeof(start_melody) / sizeof(int);
          for (int thisNote = 0; thisNote < s_size; thisNote++) {
              int noteDuration = 1000 / tempo[thisNote];

              buzz(BUZZER, start_melody[thisNote], noteDuration);
              int pauseBetweenNotes = noteDuration * 1.30;
              delay(pauseBetweenNotes);
              buzz(BUZZER, 0, noteDuration);
            }
            s_song = 0;
          }
        }

        //포토 리플렉터 신호 감지 -> 1씩 카운트
        if(digitalRead(2)==1){
            if(flag[1] == 1){
                delay(1000);
                flag[1] = 0; 
                c_human++;
                for (int thisNote = 0; thisNote < size; thisNote++) {
                    int noteDuration = 1000 / underworld_tempo[thisNote];
                    buzz(BUZZER, underworld_melody[thisNote], noteDuration);
                    int pauseBetweenNotes = noteDuration * 1.30;
                    delay(pauseBetweenNotes);
                    buzz(BUZZER, 0, noteDuration);
                }
                delay(1500);
            }
            if(c_human > 7) c_human = 0;
        }else flag[1] = 1;

        if(digitalRead(1)==1){
            if(flag[2] == 1){
                delay(1000);
                flag[2] = 0; 
                c_robot++;
                for (int thisNote = 0; thisNote < size; thisNote++) {
                    int noteDuration = 1000 / underworld_tempo[thisNote];
                    buzz(BUZZER, underworld_melody[thisNote], noteDuration);
                    int pauseBetweenNotes = noteDuration * 1.30;
                    delay(pauseBetweenNotes);
                    buzz(BUZZER, 0, noteDuration);
                }
                delay(1500);
            }
            if(c_robot > 7) c_robot = 0;
        }else flag[2] = 1;

        for(int i=0; i<=6; i++){
            digitalWrite(i+3, FND[c_robot][i]);
        }

        for(int i=0; i<=6; i++){
            digitalWrite(i+22, FND[c_human][i]);
        }

        //끝 지점
        end:
        if(start == 0 && ok_end == 1 && e_song == 1){
          if(c_human>=7 || c_robot>=7 || now-past >= 180000){
            //팩맨 노래 출력
            for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
                divider = end_melody[thisNote + 1];
                if (divider > 0) {
                noteDuration = (2285) / divider;
                } else if (divider < 0) {
                noteDuration = (2285) / abs(divider);
                }
                tone(BUZZER, end_melody[thisNote], noteDuration * 0.9);
                delay(noteDuration);
                noTone(BUZZER);
            }
            e_song = 0;
            //FND 출력
            for(int i=0; i<=6; i++){
                digitalWrite(i+3, FND[c_robot][i]);
            }
            for(int i=0; i<=6; i++){
                digitalWrite(i+22, FND[c_human][i]);
            }
            for(int i=0; i<=6; i++){
                if(now_led-past_led >= 5000000){
                    digitalWrite(i+3, 1);
                    digitalWrite(i+22, 1);
                    digitalWrite(13, 1);
                }
            }
            //라인 LED 3번 깜빡이기
            for(int i=0; i<3; i++){
                digitalWrite(LINE_LED, 1);
                delay(200);
                digitalWrite(LINE_LED, 0);
                delay(200);
            }
            digitalWrite(LINE_LED, 0);
          } 
        }
}

void buzz(int targetPin, long frequency, long length) {
    long delayValue = 1000000 / frequency / 2;
    long numCycles = frequency * length / 1000;
    for (long i = 0; i < numCycles; i++) {
        digitalWrite(targetPin, 1);
        delayMicroseconds(delayValue); 
        digitalWrite(targetPin, 0); 
        delayMicroseconds(delayValue); 
    }
}
