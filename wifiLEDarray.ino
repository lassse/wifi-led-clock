
int current = 0;
int led1 = 2; // Black
int led2 = 3; // Grey
int led3 = 4; // Blue
int led4 = 5; // Red
int led5 = 6; // White
int led6 = 7; // Purple
int leds[] = {led1, led2, led3, led4, led5, led6};

/*
Black  - 1st from ground
Grey   - 2nd from ground
Blue   - 3rd from ground
Red    - 4th from ground
White  - 5th from ground
Purple - 6th from ground
*/

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);  
}

void loop() {
  
  if (current < 6) {
   current++;  
  }else{
    current = 0;
  }

  for (int i =0; i<6; i++){
    digitalWrite(leds[i], LOW);  
  }
  
  Serial.println(current);
  
  digitalWrite(leds[current], HIGH);

  delay(200);
  
}
