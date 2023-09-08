#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Servo.h>

#define PIR_PIN A3
#define LDR_PIN A2
#define WHITE_LED1 A0
#define WHITE_LED2 A1
#define RED_LED A5
#define GREEN_LED A4
#define button_garage1 11
#define button_garage2 12
#define buzzer 10
#define servo1 2
#define servo2 3
#define servo3 4
#define servo4 5
#define servo5 6

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo
Servo myservo5;  // create servo object to control a servo

int value;

void task1(void *pvParameters)
{
    
    while (1) {

          if (digitalRead(PIR_PIN) == 1) {
            
              myservo1.write(0);            
              myservo2.write(0);              
              myservo3.write(0);              

              digitalWrite(GREEN_LED, LOW);
              digitalWrite(RED_LED, HIGH);

              tone(buzzer, 1500); // Send 1.5KHz sound signal...
              delay(500);        // ...for 1 sec
              noTone(buzzer);     // Stop sound...
              delay(500);        // ...for 1sec
            }
          

          if (digitalRead(PIR_PIN) == 0) {
              myservo1.write(90);            
              myservo2.write(90);             
              myservo3.write(90);           
              
              
              digitalWrite(GREEN_LED, HIGH);
              digitalWrite(RED_LED, LOW);

              noTone(buzzer);     // Stop sound...
            }
          }
    }


void task2(void *pvParameters)
{

    while (1) {

          if (digitalRead(LDR_PIN) == 1) {

              digitalWrite(WHITE_LED1, HIGH);
              digitalWrite(WHITE_LED2, HIGH);
            }
          

          if (digitalRead(LDR_PIN) == 0) {
            
              digitalWrite(WHITE_LED1, LOW);
              digitalWrite(WHITE_LED2, LOW);
            }
    }
}

void task3(void *pvParameters)
{

    while (1) {

          if (digitalRead(button_garage1) == 1) {
            
              myservo4.write(0);            
              myservo5.write(0);          
            }
          
          if (digitalRead(button_garage2) == 1) {

              myservo4.write(360);              
              myservo5.write(300);            
              
            }
    }
}



void setup()
{
    myservo1.attach(servo1);  // attaches the servo on pin 2 to the servo object
    myservo2.attach(servo2);  // attaches the servo on pin 3 to the servo object
    myservo3.attach(servo3);  // attaches the servo on pin 4 to the servo object
    myservo4.attach(servo4);  // attaches the servo on pin 5 to the servo object
    myservo5.attach(servo5);  // attaches the servo on pin 6 to the servo object

    pinMode(PIR_PIN, INPUT);
    pinMode(LDR_PIN, INPUT);
    pinMode(button_garage1, INPUT);
    pinMode(button_garage2, INPUT);

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(WHITE_LED1, OUTPUT);
    pinMode(WHITE_LED2, OUTPUT);
    pinMode(buzzer, OUTPUT);
    

    xTaskCreate(task1, "Task1", 128, NULL, 1, NULL);
    xTaskCreate(task2, "Task2", 128, NULL, 1, NULL);
    xTaskCreate(task3, "Task3", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    Serial.begin(9600);
}

void loop()
{

}
