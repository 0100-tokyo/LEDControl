#include <MsTimer2.h>

const int LED_PIN = 5;
const int UP_STEP = 1;
const int DOWN_STEP = 3;

int brightness = 0;

boolean bAscending = false;

const double C = 255.0;

int getDuty(double ratio) {
  if(ratio == 0) return 0;
  return round(exp(log(255.0) - (1 - ratio) * log(C))); 
}

int potential = 0;

void controlBrightness() {
 if(bAscending == true && brightness <255 && potential == 25) {
   brightness += UP_STEP;
   if(brightness > 255) brightness = 255;
 }
 else if(bAscending == true && brightness <255) {
   potential += 1;
 }
 else if(bAscending == false && brightness > 0) {
   brightness -= DOWN_STEP;
   if(brightness < 0) brightness = 0;
   potential = 0;
 }

 int b = getDuty(brightness/255.0);
 Serial.println(b);
 analogWrite(LED_PIN, b);
}

void readDistance()
{
  int value = analogRead(0);
  int distance = (6787/(value-3))-4;
  if(distance <= 50 && distance > 0){
    // Serial.print(distance);
    // Serial.println("cm");
    bAscending = true;
  }
  else{
    // Serial.println("not found");
    bAscending = false;
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode( LED_PIN, OUTPUT );
 MsTimer2::set(10, controlBrightness);
 MsTimer2::start();
}

void loop() {
 readDistance();
 delay(10);
}
