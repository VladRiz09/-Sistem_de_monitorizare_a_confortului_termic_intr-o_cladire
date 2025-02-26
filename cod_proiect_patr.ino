#include <Arduino_FreeRTOS.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
const int buttonPin = 2;
int buttonState = 0;
int temperatura = 23;
int temperatura_manuala = 23;
int manual_auto = 1;
int presiune = 0;

void Task_T(void *pvParameters);
void Task_S(void *pvParameters);
void Task_SW(void *pvParameters);
void Task_P(void *pvParameters);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Serial.println(F("Start!"));
  pinMode(buttonPin, INPUT);
  pinMode(13, OUTPUT);////////////////se aprinde becul cand se aprinde heater
  xTaskCreate(Task_T,"Task_T",configMINIMAL_STACK_SIZE,NULL, 0, NULL);
  xTaskCreate(Task_S, "Task_S", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(Task_SW, "Task_SW", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  xTaskCreate(Task_P, "Task_P", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
  vTaskStartScheduler(); 
}

void Task_T(void *pvParameters){
  Serial.println("Task T activat");
  while(1){
    temperatura = analogRead(A0)/21;
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void Task_S(void *pvParameters){
  Serial.println("Task S activat");
  while(1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(0,1);
    lcd.print(temperatura);
    if(manual_auto == 0){
      if(temperatura < 22){
        digitalWrite(13, HIGH);//aprinde becul
      }else{
        digitalWrite(13, LOW);//se stinge becul
      }
      lcd.setCursor(15,1);
      lcd.print("A");
    }
    if(manual_auto == 1){
      int temperatura_fake = analogRead(A2) / 30;
      if(temperatura < temperatura_fake){
        
        digitalWrite(13, HIGH);//aprinde becul
      }else{
        digitalWrite(13, LOW);//se stinge becul
      }
      lcd.setCursor(15,1);
      lcd.print("M");
      lcd.setCursor(7,0);
      lcd.print("TempIN:");
      lcd.setCursor(7,1);
      lcd.print(temperatura_fake);
    }
    vTaskDelay(700 / portTICK_PERIOD_MS);
  }
}

void Task_SW(void *pvParameters){
  Serial.println("Task SW activat");
  while(1){
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      if(manual_auto == 0){
        manual_auto = 1;
      }else{
        manual_auto = 0;
      }
    }
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void Task_P(void *pvParameters){
  Serial.println("Task P activat");
  while(1){
    presiune = analogRead(A1)/2;
    if(presiune < 300){
      if(temperatura > 32){ //hard stop in caz de overheat
        Serial.println("Opresc pompele");
        Serial.print("Presiunea este de :");
        Serial.println(presiune);
        Serial.print("Temperatura este de :");
        Serial.println(temperatura);
      }else{
        Serial.println("Pompe pornite");
        Serial.print("Presiunea este de :");
        Serial.println(presiune);
        Serial.print("Temperatura este de :");
        Serial.println(temperatura);
      }
    }else{
      Serial.println("Opresc pompele");
      Serial.print("Presiunea este de :");
      Serial.println(presiune);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


void loop(){}