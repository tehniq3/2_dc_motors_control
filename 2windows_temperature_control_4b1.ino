/*
  sketch by niq_ro for control 2 DC motors using 4 relay board
  http://nicuflorica.blogspot.ro/
  http://www.tehnic.go.ro
  http://arduinotehniq.blogspot.com/
ver.0 - just test control mode, 10 March 2018, Craiova - Romania
ver.1 - put DS18B20 for measure temperature
ver.2 - put LCD1602 on i2c
ver.3 - new version with few updates
ver.4 - add switch for OPEN - AUTO - CLOSE
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
#define pin1 9  // D9 for relay 1
#define pin2 10  // D10 for relay 2
#define pin3 11  // D11 for relay 3
#define pin4 12  // D12 for relay 4
#define comutator A0 // A0 for measure state

#define releuatras LOW
#define releuliber HIGH

//int pauza = 150;  // pause between commands (just fort tests)
int pauza = 1000;  // pause between commands
int secundeactive = 30;
int secundepauza = 10;

float te;
float tecald = 30.;  // 
float terece = 27.; //
byte stare = 1;  // 0, 1 or 2
byte stareant = 2;
int tensiune = 0;
int e;

// the setup routine runs once when you press reset:
void setup() {  
  Serial.begin(9600);  // start serial port
  Serial.println("Sistem made by Nicu FLORICA (niq_ro)");
  
  // initialize the digital pin as an output.
  pinMode(pin1, OUTPUT);     
  pinMode(pin2, OUTPUT);    
  pinMode(pin3, OUTPUT);     
  pinMode(pin4, OUTPUT);    
  
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH

pinMode(comutator, INPUT);

sensors.begin();  // Start up the library

lcd.begin();  // initialize the LCD
lcd.backlight();  // Turn on the blacklight and print a message.
lcd.createChar(0, grad);  // create synbol for degree (Celsius)
lcd.setCursor(0, 0);
lcd.print(" Sistem control ");
lcd.setCursor(0, 1);
lcd.print("temperatura sera");
delay(2500);
lcd.clear();
lcd.setCursor(1, 0);
lcd.print("conceptie a lui");
lcd.setCursor(0, 1);
lcd.print("Nicu FLORICA v.4");
delay(2500);
lcd.clear();

}

// the loop routine runs over and over again forever:
void loop() {

citire();

if (stare == 0)  // both windows must closed
{
lcd.setCursor(0, 0);
lcd.print("Inchidere       ");
motorminus1();
pauze();
}
if (stare == 0)  // both windows must closed
{
lcd.setCursor(0, 0);
lcd.print("Inchidere       ");
motoareoprite();
pauze2();
}
if (stare == 0)  // both windows must closed
{
lcd.setCursor(0, 0);
lcd.print("Inchidere       ");
motorminus2();
pauze();
}
if (stare == 0)  // both windows must closed
{
lcd.setCursor(0, 0);
lcd.print("Inchidere       ");
motoareoprite();
pauze2();
} // end manual mode to close windows

if (stare == 1)  // both windows must opened
{
lcd.setCursor(0, 0);
lcd.print("Deschidere      ");
motorplus1();
pauze();
}
if (stare == 1)  // both windows must opened
{
lcd.setCursor(0, 0);
lcd.print("Deschidere      ");
motoareoprite();
pauze2();
}
if (stare == 1)  // both windows must opened
{
lcd.setCursor(0, 0);
lcd.print("Deschidere      ");
motorplus2();
pauze();
}
if (stare == 1)  // both windows must opened
{
lcd.setCursor(0, 0);
lcd.print("Deschidere      ");
motoareoprite();
pauze2();
} // end manual mode to open windows


if (stare == 2)  // auto mode
{
termometru();
termometru2();
// control first motor
lcd.setCursor(8, 0);
lcd.print("        ");
if (te > tecald)
{
lcd.setCursor(8, 0);
lcd.print(" >= ");
lcd.print(tecald,0);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");
motorplus1();
}
if (te < terece)
{
lcd.setCursor(8, 0);
lcd.print(" <= ");
lcd.print(terece,0);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");
motorminus1();
}
pauze();
}
if (stare == 2)  // auto mode
{
termometru2();
lcd.setCursor(8, 0);
lcd.print("        ");
lcd.setCursor(0, 1);
lcd.print("                ");
if (te > tecald)
{
lcd.setCursor(8, 0);
lcd.print(" >= ");
lcd.print(tecald,0);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");
lcd.setCursor(0, 1);
lcd.print("prea cald ! ");
}
if (te < terece)
{
lcd.setCursor(8, 0);
lcd.print(" <= ");
lcd.print(terece,0);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");
lcd.setCursor(0, 1);
lcd.print("prea rece ! ");
}
lcd.setCursor(0, 1);
lcd.print("pauza       ");
motoareoprite();
pauze2();
}
if (stare == 2)  // auto mode
{
termometru();
termometru2();
// control second relay
lcd.setCursor(8, 0);
lcd.print("        ");
if (te > tecald)
{
motorplus2();
lcd.setCursor(8, 0);
lcd.print(" >= ");
lcd.print(tecald,0);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");
}
if (te < terece)
{
motorminus2();
lcd.setCursor(8, 0);
lcd.print(" <= ");
lcd.print(terece,0);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");
}
pauze();
}
if (stare == 2)  // auto mode
{
termometru2();
// free all relays
lcd.setCursor(8, 0);
lcd.print("        ");
lcd.setCursor(0, 1);
lcd.print("                ");
if (te > tecald)
{
lcd.setCursor(8, 0);
lcd.print(" >= ");
lcd.print(tecald,0);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");
lcd.setCursor(0, 1);
lcd.print("prea cald ! ");
}
if (te < terece)
{
lcd.setCursor(8, 0);
lcd.print(" <= ");
lcd.print(terece,0);
// lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
lcd.print("C");
lcd.setCursor(0, 1);
lcd.print("prea rece ! ");
}

lcd.setCursor(0, 1);
lcd.print("pauza       ");
motoareoprite();
pauze2();
} // end auto mode


}  // end main loop


void citire()
{
tensiune = analogRead (comutator);
if (tensiune < 100)  // switch at ground
{
stare = 0; 
//lcd.clear();  
}
if (tensiune > 900)  // switch at Vcc (5V)
{
stare = 1;
//lcd.clear();    
}
if ((tensiune > 400) and (tensiune < 600)) // switch at midle
{
stare = 2;
//lcd.clear(); 
}
Serial.print("stare = ");
Serial.println(stare);
if (stareant != stare)
{
  lcd.clear();
  e=0;
  stareant = stare;
  motoareoprite();
  pauzamica();
if (stare == 2) termometru();
}
}

void pauze()
{
  for (e = secundeactive; e >= 0; e--)
{
lcd.setCursor(12,1);
if (e<100) lcd.print(" ");
if (e<10) lcd.print(" "); 
lcd.print(e);
lcd.print("s");
delay(pauza);
citire();
}
}

void pauze2()
{
  for (e = secundepauza; e >= 0; e--)
{
lcd.setCursor(12,1);
if (e<100) lcd.print(" ");
if (e<10) lcd.print(" "); 
lcd.print(e);
lcd.print("s");
delay(pauza);
citire();
}
}

void pauzamica()
{
lcd.clear();
lcd.print("schimbare mod !");
  for (e = 10; e >= 0; e--)
{
lcd.setCursor(12,1);
if (e<100) lcd.print(" ");
if (e<10) lcd.print(" "); 
lcd.print(e);
lcd.print("%");
delay(pauza);
citire();
}
}

void motoareoprite()
{
 lcd.setCursor(0, 1);
 lcd.print("pauza       ");
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH
}

void motorminus1()
{
 Serial.println("Motor 1 -");
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin2, releuatras);    // turn the relay 2 on by making the voltage LOW
 lcd.setCursor(0, 1);
 lcd.print("mot.1 inch. ");
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH
}

void motorminus2()
{
 Serial.println("Motor 2 -");
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH 
 digitalWrite(pin4, releuatras);    // turn the relay 4 on by making the voltage LOW
 lcd.setCursor(0, 1);
 lcd.print("mot.2 inch. ");
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
}

void motorplus1()
{
 Serial.println("Motor 1 +");
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH 
 digitalWrite(pin1, releuatras);    // turn the relay 1 on by making the voltage LOW
 lcd.setCursor(0, 1);
 lcd.print("mot.1 desch.");
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH
}

void motorplus2()
{
 Serial.println("Motor 2 +");
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH 
 digitalWrite(pin3, releuatras);    // turn the relay 3 on by making the voltage LOW
 lcd.setCursor(0, 1);
 lcd.print("mot.2 desch.");
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
}

void termometru()
{
  Serial.print("Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  te = sensors.getTempCByIndex(0);
  Serial.print("Temperature is: ");
  Serial.print(te);  
  Serial.println(" gr.C");
}

void termometru2()
{
 lcd.clear();
 lcd.setCursor(0, 0);
 //lcd.print("t = ");
 if (te < 10.) lcd.print(" ");
 lcd.print(te,1);
 // lcd.write(0b11011111);  // caracter asemanatpor cu gradul Celsius
 lcd.write(byte(0));  // simbolul de grad Celsius creat de mine
 lcd.print("C");
}
