/*
  sketch by niq_ro for control 2 DC motors using 4 relay board
  http://nicuflorica.blogspot.ro/
  http://www.tehnic.go.ro
  http://arduinotehniq.blogspot.com/

ver.0 - just test control mode, 10 March 2018, Craiova - Romania
ver.1 - put DS18B20 for measure temperature
ver.2 - put LCD1602 on i2c

 */

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A3  // // Data wire is plugged into A3 on the Arduino
OneWire oneWire(ONE_WIRE_BUS); // // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // // Pass our oneWire reference to Dallas Temperature. 

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// http://arduino.cc/en/Reference/LiquidCrystalCreateChar  // definim un simbol pentru grad celsius
byte grad[8] = {
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000,
  B00000,
};

// inputs for relays:
#define pin1 2  // D2 for relay 1
#define pin2 3  // D3 for relay 2
#define pin3 4  // D4 for relay 3
#define pin4 5  // D5 for relay 4

#define releuatras LOW
#define releuliber HIGH

int pauza = 5000;  // pause between commands
float te;
float tecald = 30.;  // 

// the setup routine runs once when you press reset:
void setup() {  
  Serial.begin(9600);  // start serial port
  Serial.println("Sistem made by Nicu FLORICA (niq_ro)");
  sensors.begin();  // Start up the library

lcd.begin();	// initialize the LCD
lcd.backlight();	// Turn on the blacklight and print a message.
lcd.createChar(0, grad);  // create synbol for degree (Celsius)
lcd.setCursor(0, 0);
lcd.print(" Sistem control ");
lcd.setCursor(0, 1);
lcd.print("temperatura sera");
  
  // initialize the digital pin as an output.
  pinMode(pin1, OUTPUT);     
  pinMode(pin2, OUTPUT);    
  pinMode(pin3, OUTPUT);     
  pinMode(pin4, OUTPUT);    
  
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH
delay(pauza);
lcd.clear();
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.print("Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  te = sensors.getTempCByIndex(0);
  Serial.print("Temperature is: ");
  Serial.print(te);  
  Serial.println(" gr.C");

lcd.setCursor(0, 0);
lcd.print("t=");
if (te < 10.) lcd.print(" ");
lcd.print(te,1);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");

if (te > tecald)
{
  lcd.print(">=");
}
else
{
  lcd.print("< ");
}
  lcd.print(tecald,1);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");


// control firt motor
lcd.setCursor(0, 1);
if (te > tecald)
{
 Serial.println("Motor 1 -");
 digitalWrite(pin1, releuatras);    // turn the relay 1 on by making the voltage LOW 
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
lcd.print("Motor 1 <-");
}
else
{
 Serial.println("Motor 1 +");
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin2, releuatras);    // turn the relay 2 on by making the voltage LOW
lcd.print("Motor 1 ->");
}
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH
delay(pauza);  // wait for complete movements

lcd.setCursor(0, 1);
lcd.print("          ");
// free all relays
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH
delay(pauza);  // wait for "recover"  battery

// control second relay
lcd.setCursor(0, 1);
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
if (te > tecald)
{
  Serial.println("Motor 2 -");
 digitalWrite(pin3, releuatras);    // turn the relay 3 on by making the voltage LOW
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH
lcd.print("Motor 2 <-");
}
else
{
  Serial.println("Motor 2 +");
 digitalWrite(pin3, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin4, releuatras);    // turn the relay 2 on by making the voltage LOW
lcd.print("Motor 2 ->");
}
delay(pauza);  // wait for complete movements


// free all relays
lcd.setCursor(0, 1);
lcd.print("          ");
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH
delay(pauza);  // wait for "recover"  battery


}  // end main loop
