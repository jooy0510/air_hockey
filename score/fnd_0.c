#include <stdio.h>

int c_robot = 0, c_human = 0;
int FND[12][12] = {{1, 0, 0, 0, 0, 0, 0}, 
                   {1, 1, 1, 1, 0, 0, 1},
                   {0, 1, 0, 0, 1, 0, 0},
                   {0, 1, 1, 0, 0, 0, 0},
                   {0, 0, 1, 1, 0, 0, 1},
                   {0, 0, 1, 0, 0, 1, 0},
                   {0, 0, 0, 0, 0, 1, 0},
                   {1, 0, 1, 1, 0, 0, 0}
                  };
 
void setup(){
    for(int i=3; i<=13; i++)
      pinMode(i, OUTPUT);
    for(int i=22; i<=28; i++)
      pinMode(i, OUTPUT);

    for(int i=0; i<=6; i++){
      digitalWrite(i+3, FND[c_robot][i]);
    }

		digitalWrite(13, 0);

    for(int i=0; i<=6; i++){
      digitalWrite(i+22, FND[c_human][i]);
    }

    for(int i=10; i<=12; i++)
      digitalWrite(i, 1);
}
 
void loop(){
}
