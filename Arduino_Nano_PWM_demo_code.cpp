/*
adapted fade code, start serial monitor at 9600 baud to enter a fixed PWM % or "F" for fade-mode
PWM signal appears at GPIO D9 of your arduino Nano or Uno
Mr. T's design Graveyard: https://www.youtube.com/@smartpowerelectronics8779
*/

int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
bool fadeMode = true;  // start in fade mode by default

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Please enter the PWM duty cycle in % (0-100), or F for fade:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    if (input.equalsIgnoreCase("F")) {
      fadeMode = true;
      Serial.println("Fade mode activated");
    } else {
      int percent = input.toInt();
      if (percent >= 0 && percent <= 100) {
        fadeMode = false;
        brightness = map(percent, 0, 100, 0, 255);
        analogWrite(led, brightness);
        Serial.print("Set brightness to ");
        Serial.print(percent);
        Serial.println("%");
      } else {
        Serial.println("Invalid input. Please enter 0-100 or F");
      }
    }
  }

  if (fadeMode) {
    analogWrite(led, brightness);
    brightness += fadeAmount;
    
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
	   if (brightness <= 25) brightness = 25; //prevent standby
    }
    delay(20);
  }
}