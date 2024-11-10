#include <IRremote.h>

const int IR_PIN = 12;                                           // define IR receiver pin 
int Brightnesslvl = 150;                                         // default brightness level = 150
int values[8] = {0,1,2,3,4,5,6,7};                              // LED array
int i = 0;
int cycle = 0;

#define LED1 5                                                   //pin 5 : 1st LEd   PWM
#define LED2 6                                                   //pin 6 : 2nd LEd   PWM
#define LED3 9                                                   //pin 9 : 3rd LEd   PWM
#define LED4 10                                                  //pin 10 : 4th LEd  PWM
#define REDLED 4                                                 //pin 4 : red LEd   non-PWM
#define GREENLED 7                                               //pin 7 : green LEd non-PWM
#define BLUELED 8                                                //pin 8 : blue LED  non-PWM

IRrecv irrecv(IR_PIN);                                          // Define IR receiver object

void setup() {
  Serial.begin(9600);                                           // Serial monitor
  irrecv.enableIRIn();

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);

}

void loop() {
  if (irrecv.decode()) {                                        // Check if the IR receiver has received a signal
  irrecv.resume();                                              // Reset the IR receiver for the next signal
  LEDstate();

    if(values[i] == 0){                                             //all LED off
      state0();
    }

    else if(values[i] == 1){                                        //1st LED on
      state1();
    }

    else if(values[i] == 2){                                        //upto 2nd LED on   
      state2();
    }

    else if(values[i] == 3){                                        //upto 3rd LED on
      state3();
    }

    else if(values[i] == 4){                                        //upto 4th LED on
      state4();
    }

    else if(values[i] == 5){                                        //4 white LED and red LED on
      state5();
    }

    else if(values[i] == 6){                                        //4 white LED and green LED on
      state6();
    }
    
    else if(values[i] == 7){                                        //4 white LED and blue LED on
      state7();
    }
  }
}

void LEDstate(){
  if(irrecv.decodedIRData.decodedRawData == 0xE718FF00){        // check if receiver receive UP key value , 0xE718FF00 = UP
    if(i == 7){                           // check if LED in state 7
      i = 4;                              
      values[i];
      i ++;                               // cycle state5, state6, state7
      cycle ++;                           // count RGB cycles
      Serial.print("RGB cycles: ");
      Serial.println(cycle);
    }
    else{
      values[i];                          // if it is not in state 7, increase array without loop
      i ++;
    }
  }
  else if(irrecv.decodedIRData.decodedRawData == 0xAD52FF00){   // check if receiver receive DOWN key value , 0xAD52FF00 = DOWN
    if(i >= 0){                           // i always has to be 0 or higher  
      if(cycle != 0){                     // check if RGB cycle not equals to zero 
      if(i == 5){                         // cycle != 0 and i == 5
        i = 8;                            
        i --;
        values[i];
        cycle --;  
        Serial.print("RGB cycles: ");
        Serial.println(cycle);                       
      }
      else{                               // cycle != 0 and i != 5
        values[i];                        
        i --;
      }
    }else{                                // RGB cycles are 0
      values[i];                          
      i --;
    }
    }
    else{
      i = 0;
    }
  }
  else if(irrecv.decodedIRData.decodedRawData == 0xA55AFF00){   // check if receiver receive RIGHT key value , 0xA55AFF00 = RIGHT
    if(Brightnesslvl < 250){   
      Brightnesslvl = Brightnesslvl + 50; 
      Serial.print("Brightness: ");
      Serial.println(Brightnesslvl);
    }
    else if(Brightnesslvl >= 250){         // once brightness lvl is 250 or get higher, brightness lvl set to 250
      Brightnesslvl = 250;
    }
  }
  else if(irrecv.decodedIRData.decodedRawData == 0xF708FF00){   // check if receiver receive LEFT key value , 0xF708FF00 = LEFT
    if(Brightnesslvl > 50){
      Brightnesslvl = Brightnesslvl - 50;
      Serial.print("Brightness: ");
      Serial.println(Brightnesslvl);
    }
    else if(Brightnesslvl <= 50){          // once brightness lvl is 50 or get lower, brightness lvl set to 50
      Brightnesslvl = 50;
    }
  }
}

void state0(){
  analogWrite(LED1, 0);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, LOW);
  Serial.println("HIGH LEDs: -");
}
void state1(){
  analogWrite(LED1, Brightnesslvl);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, LOW);
  Serial.println("HIGH LEDs: W");
}
void state2(){
  analogWrite(LED1, Brightnesslvl);
  analogWrite(LED2, Brightnesslvl);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, LOW);
  Serial.println("HIGH LEDs: W  W");
}
void state3(){
  analogWrite(LED1, Brightnesslvl);
  analogWrite(LED2, Brightnesslvl);
  analogWrite(LED3, Brightnesslvl);
  digitalWrite(LED4, LOW);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, LOW);
  Serial.println("HIGH LEDs: W  W  W");
}
void state4() {
  analogWrite(LED1, Brightnesslvl); 
  analogWrite(LED2, Brightnesslvl); 
  analogWrite(LED3, Brightnesslvl); 
  analogWrite(LED4, Brightnesslvl); 
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW); 
  digitalWrite(BLUELED, LOW); 
  Serial.println("HIGH LEDs: W  W  W  W");
}
void state5(){
  analogWrite(LED1, Brightnesslvl); 
  analogWrite(LED2, Brightnesslvl); 
  analogWrite(LED3, Brightnesslvl); 
  analogWrite(LED4, Brightnesslvl);
  digitalWrite(REDLED, HIGH);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, LOW);
  Serial.println("HIGH LEDs: W  W  W  W  R");
}
void state6(){
  analogWrite(LED1, Brightnesslvl);
  analogWrite(LED2, Brightnesslvl); 
  analogWrite(LED3, Brightnesslvl); 
  analogWrite(LED4, Brightnesslvl);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, HIGH);
  digitalWrite(BLUELED, LOW);
  Serial.println("HIGH LEDs: W  W  W  W  G");
}
void state7(){
  analogWrite(LED1, Brightnesslvl);
  analogWrite(LED2, Brightnesslvl); 
  analogWrite(LED3, Brightnesslvl); 
  analogWrite(LED4, Brightnesslvl);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, HIGH);
  Serial.println("HIGH LEDs: W  W  W  W  B");
}
