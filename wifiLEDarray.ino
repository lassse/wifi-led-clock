#include <Process.h>
#include <Servo.h> 


Servo motor;
int motorTicker = 0;
int motorTime = 80;


boolean useWifi = false;

/*
Black  - 1st from ground
 Grey   - 2nd from ground
 Blue   - 3rd from ground
 Red    - 4th from ground
 White  - 5th from ground
 Purple - 6th from ground
 */

int wifiCheck = 20;
int wifiCurrent = 0;

int current = 0;
int fadeSteps = 20;
int fadeValue = round(255/fadeSteps);

// Pins
//int led1 = 11; // Black
//int led2 = 10; // Grey
//int led3 = 9; // Blue
//int led4 = 6; // Red
//int led5 = 5; // White
//int led6 = 3; // Purple

int led1 = 3; // Black
int led2 = 5; // Grey
int led3 = 6; // Blue
int led4 = 9; // Red
int led5 = 10; // White
//int led6 = 11; // Purple

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;

int leds[] = {
    led1, led2, led3, led4, led5};
int vals[] = {
    val1, val2, val3, val4, val5};
int signal = 0;

Process p;


void setup() {
    Bridge.begin();

    Serial.begin(9600);
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(led3,OUTPUT);
    pinMode(led4,OUTPUT);
    pinMode(led5,OUTPUT);
//    pinMode(led6,OUTPUT);  

    motor.attach(11);
}

void loop() {
    
    
    for (int i=0; i<5; i++){

        if (i < signal){
            if ( vals[i] < fadeSteps ){
                vals[i] += 1;
            }else{
                vals[i] = fadeSteps;   
            }
        }else{
            if ( vals[i] > 0 ){
                vals[i] -= 1;
            }else{
                vals[i] = 0;
            }
        }        
        analogWrite(leds[i], vals[i] * fadeValue);
    }      

    if (useWifi) {
        if (wifiCurrent < wifiCheck) {
            wifiCurrent++;
        }else{
            p.runShellCommand("/usr/bin/pretty-wifi-info.lua | grep Signal"); 
            while(p.running());  
            while (p.available()){ 
                int result = p.parseInt();
                if (result != 0) {
                    signal = map(result, 50, 70, 0, 4);
    
                    Serial.println("  ");  
                    Serial.println("------------------------");  
                    Serial.print("Signal strength: ");  
                    Serial.println(signal);    
                }
            }
    
            wifiCurrent = 0; 
        }
    }else{
        signal = 3;
    }
    
    if (motorTicker > motorTime) {
        motor.write(110);
        motorTicker = 0;        
    }else{
        motor.write(94);
        motorTicker++;   
    }    

    delay(30);

}


