#include<LiquidCrystal.h>  // Include LiquidCrystal library

float temperature;    // Variable for storing the input value of temperature sensor
float voltage;       // Variable for storing the given voltage of teperature sensor
float temp_in_celsius; // Variable for storing the value in celsius
float temp_in_fahernheit; // Variable for storing the value in fahernheit

const int trigPin = 9;   // Trigger pin of ultrasonic sensor 
const int echoPin = 10;  // Echo pin of ultrasonic sensor 
long duration;           // Variable for storing the input value of ultrasonic sensor
int distance_in_cm;      // Variable for storing the distance in centimeters
int distance_in_inches; // Variable for storing the distance in Inches

int pir_sensor = 8;     // Pin connected to output pin of PIR sensor
int Motor = 1;          // Pin connected to motor
int Buzzer = 11;        // Pin connected to Buzzer
int Led = 12;           // Pin connected to LED
int tmp_36 = A0;       // Pin connected to output pin of temperature sensor
int i = 0;             // Variable for 'if' condiotion
int s = 0;             // Variable for 'while loop'


int wait = 500;       // delay time

int pir_sensor_value;  // Variable for storing the input value of PIR sensor value

LiquidCrystal LCD1(13,A1,A2,A3,A4,A5);  // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7) for first LCD
LiquidCrystal LCD2(2,3,4,5,6,7);        // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7) for second LCD
  
void setup()
{
  
  
 LCD1.begin(16,2);  // Initialize first LiquidCrystal display
 LCD2.begin(16,2);   // Initialize second LiquidCrystal display
  
 pinMode(tmp_36, INPUT);         // Set Temperature sensor pin as an INPUT pin
 pinMode(trigPin, OUTPUT);      // Set Trigger pin of ultrasonic sensor as an OUTPUT pin
 pinMode(echoPin, INPUT);      // Set Echo pin of ultrasonic sensor as an INPUT pin
 pinMode(pir_sensor, INPUT);  // Set PIR sensor pin as an INPUT pin
 pinMode(Buzzer, OUTPUT);   // Set Buzzer pin as an OUTPUT pin
 pinMode(Motor, OUTPUT);     // Set Electric Motor pin as an OUTPUT pin
 pinMode(Led, OUTPUT);       // Set LED pin as an OUTPUT pin
 
 LCD1.setCursor(0,0);
  LCD1.print("Assalamualaikum");
  LCD1.setCursor(4,1);
  LCD1.print("Everyone");

  LCD2.setCursor(3,0);
  LCD2.print("Welcome to");
  delay(1000);
  LCD2.clear();
  LCD1.clear();
  LCD1.setCursor(4,0);
  LCD1.print("AYESHA'S");
  LCD2.setCursor(0,0);
  LCD2.print("COVID-19 Human");
   LCD2.setCursor(0,1);
  LCD2.print("Detector System");
  delay(2500);
 LCD2.clear();
  LCD1.clear();

}

void loop()
{
  pir_sensor_value = digitalRead(pir_sensor);      // // See if PIR sensor senses or not
  
  if (pir_sensor_value == HIGH || i == 1)
  {
       while(s<1)
    {
   LCD1.print("There is Human!");
   LCD2.print("There is Human!");      // Print the text .Alert' on second LCD
  delay(wait);
    LCD1.clear();
    LCD2.clear(); 
    s=1; 
    }

  digitalWrite(trigPin, LOW);  // Clears the trigPin condition
  delayMicroseconds(2);        
  digitalWrite(trigPin, HIGH);  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);     // Reads the echoPin, returns the sound wave travel time in microseconds
  distance_in_cm = duration*0.0343;
  distance_in_cm = distance_in_cm/2;    // Calculating the distance in centimeters     
  distance_in_inches = distance_in_cm * 0.3937;  // Calculating the distance in inches
  

  temperature = analogRead(tmp_36);   //getting the voltage reading from the temperature sensor
  voltage = temperature * 0.0048828125;  // converting that reading to voltage
  temp_in_celsius = (voltage - 0.5) * 100;   //converting from 10 mv per degree with 500 mV offset
                                              //to degrees ((voltage - 500mV) times 100)
  temp_in_fahernheit = (temp_in_celsius * 9.0 / 5.0) + 32.0;   // now convert to Fahrenheit
  

  if (distance_in_cm < 30)             // when the ultrasonic distance is less than 30 
  {
  LCD1.print("Temp.C :");        
  LCD1.print(temp_in_celsius);         // Print the temperature value in Celsius
  LCD1.setCursor(0,1);
  LCD1.print("Temp.F :");
  LCD1.print(temp_in_fahernheit);     // Print the temperature value in Celsius
    
  LCD2.print("Distance: ");
  LCD2 .print(distance_in_cm);      // Print the distance of ultrasonic sensor in Centimeters
  LCD2.print("cm");  
  LCD2.setCursor(0,1);  
  LCD2.print("Distance: ");
  LCD2 .print(distance_in_inches);   // Print the distance of ultrasonic sensor in Inches
  LCD2.print("in");
  delay(wait);
  LCD2.clear();   
  LCD1.clear();
  
  if (  temp_in_celsius > 37.5)   // When temperature is greater than 37.5 degree celsius
  {
    digitalWrite(Buzzer, HIGH);  // Buzzer will be turned on
    digitalWrite(Led, HIGH);      // LED will be turned on
    digitalWrite(Motor, LOW);     // Motor will stay off
  }
    
 else
  {
    digitalWrite(Buzzer, LOW);  // Buzzer will stay off
    digitalWrite(Led, LOW);     // LED will stay off
    digitalWrite(Motor, HIGH);  // Motor willbe turned on
  }
  }
  else
  {
 
    
  LCD1.print("");
  LCD1.setCursor(0,1);
  LCD1.print("");

  LCD2.print("Distance: ");
  LCD2 .print(distance_in_cm);  // Print the distance of ultrasonic sensor in Centimeters
  LCD2.print("cm");  
  LCD2.setCursor(0,1);  
  LCD2.print("Distance: ");
  LCD2 .print(distance_in_inches);  // Print the distance of ultrasonic sensor in Inches
  LCD2.print("in");
  delay(wait);
  LCD1.clear();
  LCD2.clear();   
  } 
  i=1;    
 }  

  else
  {
    i=0;
  }
  }