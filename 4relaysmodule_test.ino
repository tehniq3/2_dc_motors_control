/*
  "Blink" is original sketch
  changed sketch by niq_ro for test 4 relay board
  http://nicuflorica.blogspot.ro/
  http://www.tehnic.go.ro
  http://arduinotehniq.blogspot.com/
 */
 
// inputs for relays:
#define pin1 2  // D2 for relay 1
#define pin2 3  // D3 for relay 2
#define pin3 4  // D4 for relay 3
#define pin4 5  // D5 for relay 4

#define releuatras LOW
#define releuliber HIGH

int pauza = 2000;  // pause between commands

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(pin1, OUTPUT);     
  pinMode(pin2, OUTPUT);    
  pinMode(pin3, OUTPUT);     
  pinMode(pin4, OUTPUT);    
  
 digitalWrite(pin1, releuliber);    // turn the relay 1 off by making the voltage HIGH 
 digitalWrite(pin2, releuliber);    // turn the relay 2 off by making the voltage HIGH
 digitalWrite(pin3, releuliber);    // turn the relay 3 off by making the voltage HIGH
 digitalWrite(pin4, releuliber);    // turn the relay 4 off by making the voltage HIGH
}

// the loop routine runs over and over again forever:
void loop() {
// all relays free
  digitalWrite(pin1, releuliber);   
  digitalWrite(pin2, releuliber);    
  digitalWrite(pin3, releuliber);   
  digitalWrite(pin4, releuliber);    
delay(pauza);

// first relay powerred , other relays free
  digitalWrite(pin1, releuatras);   
  digitalWrite(pin2, releuliber);    
  digitalWrite(pin3, releuliber);   
  digitalWrite(pin4, releuliber);    
delay(pauza);

// all relays free
  digitalWrite(pin1, releuliber);   
  digitalWrite(pin2, releuliber);    
  digitalWrite(pin3, releuliber);   
  digitalWrite(pin4, releuliber);    
delay(pauza);

// second relay powerred, other relays free
  digitalWrite(pin1, releuliber);   
  digitalWrite(pin2, releuatras);    
  digitalWrite(pin3, releuliber);   
  digitalWrite(pin4, releuliber);    
delay(pauza);

// all relays free
  digitalWrite(pin1, releuliber);   
  digitalWrite(pin2, releuliber);    
  digitalWrite(pin3, releuliber);   
  digitalWrite(pin4, releuliber);    
delay(pauza);

// third relay powered, other relays free
  digitalWrite(pin1, releuliber);   
  digitalWrite(pin2, releuliber);    
  digitalWrite(pin3, releuatras);   
  digitalWrite(pin4, releuliber);    
delay(pauza);

// all relays free
  digitalWrite(pin1, releuliber);   
  digitalWrite(pin2, releuliber);    
  digitalWrite(pin3, releuliber);   
  digitalWrite(pin4, releuliber);    
delay(pauza);

// forth relay powerred, other relays free
  digitalWrite(pin1, releuliber);   
  digitalWrite(pin2, releuliber);    
  digitalWrite(pin3, releuliber);   
  digitalWrite(pin4, releuatras);    
delay(pauza);

}  // end main loop
