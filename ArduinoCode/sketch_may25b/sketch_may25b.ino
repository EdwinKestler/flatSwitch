


// Copyright 2013 Pervasive Displays, Inc.
//
//
//


#include <inttypes.h>
#include <ctype.h>

#include <SPI.h>
#include <Wire.h>
#include <EPD.h>
#include <LM75A.h>
#include <SD.h>
#include <EReader.h>
#include <SoftwareSerial.h>

SoftwareSerial bleShield(2, 3);

/*
// configure images for display size
// change these to match display size above

#define TEXT_IMAGE "pantalla.xbm"
#define TEXT_BITS pantalla_bits

#define ESCUDO_IMAGE "escudo.xbm"
#define ESCUDO_BITS escudo_bits


#define PICTURE_IMAGE "flatboxEPDlogobmp.xbm"
#define PICTURE_BITS flatboxEPDlogobmp_bits
*/
// no futher changed below this point

// current version number
#define DEMO_VERSION "1"



// Add Images library to compiler path
/*#include <Images.h>  // this is just an empty file

// images
PROGMEM const
#define unsigned
#define char uint8_t
#include TEXT_IMAGE
#undef char
#undef unsigned

PROGMEM const
#define unsigned
#define char uint8_t
#include ESCUDO_IMAGE
#undef char
#undef unsigned

PROGMEM const
#define unsigned
#define char uint8_t
#include PICTURE_IMAGE
#undef char
#undef unsigned
*/



// Arduino IO layout
const int Pin_PANEL_ON = A2;
const int Pin_BORDER = A3;
const int Pin_DISCHARGE = 4;
const int Pin_PWM = 5;
const int Pin_RESET = 6;
const int Pin_BUSY = 7;
const int Pin_EPD_CS = 8;
const int Pin_RED_LED = 13;


// declare pin for relay
const int Pin_Relay = A0;


// LED anode through resistor to I/O pin
// LED cathode to Ground
#define LED_ON  HIGH
#define LED_OFF LOW


// pre-processor convert to string
#define MAKE_STRING1(X) #X
#define MAKE_STRING(X) MAKE_STRING1(X)


// define the E-Ink display

LM75A_Class LM75A;
File unifont_file;
File display_file;

// I/O setup
void setup() {
  pinMode(Pin_RED_LED, OUTPUT);
  pinMode(Pin_PWM, OUTPUT);
  pinMode(Pin_BUSY, INPUT);
  pinMode(Pin_RESET, OUTPUT);
  pinMode(Pin_PANEL_ON, OUTPUT);
  pinMode(Pin_DISCHARGE, OUTPUT);
  pinMode(Pin_BORDER, OUTPUT);
  pinMode(Pin_EPD_CS, OUTPUT);
  pinMode(SD_CS, OUTPUT);

  digitalWrite(Pin_RED_LED, LOW);
  digitalWrite(Pin_PWM, LOW);
  digitalWrite(Pin_RESET, LOW);
  digitalWrite(Pin_PANEL_ON, LOW);
  digitalWrite(Pin_DISCHARGE, LOW);
  digitalWrite(Pin_BORDER, LOW);
  digitalWrite(Pin_EPD_CS, LOW);
  ereader.setup(EPD_2_7);
  
  //Setup pin for the relay
  
  pinMode(A0, OUTPUT);
  digitalWrite(Pin_Relay, LOW);
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  
  bleShield.begin(19200);
  Serial.begin(19200);
  
#if !defined(__MSP430_CPU__)
  // wait for USB CDC serial port to connect.  Arduino Leonardo only
  while (!Serial) {
  }
  
#endif
  Serial.println();
  Serial.println();
  Serial.println("Demo version: " DEMO_VERSION);
  Serial.println("Display: " MAKE_STRING(EPD_SIZE));
  Serial.println();
}

static int state = 0;

// main loop
void loop() {          
  int temperature = LM75A.read();
    
  //read serial and stateof serial
  
  if (bleShield.available()) {
    char Estado = bleShield.read();
    Serial.write(Estado);
        if (Estado == 'o'){
      TurnLightOn();
      //PrintScreenOn();
    }
    else if (Estado == 'f'){
      TurnLightOff ();
      //PrintScreenOff();
    }
  }  

    

  // flash LED for 5 seconds
  for (int x = 0; x < 50; ++x) {
    digitalWrite(Pin_RED_LED, LED_ON);
    delay(50);
    digitalWrite(Pin_RED_LED, LED_OFF);
    delay(50);
  }
}

void TurnLightOn(){
  digitalWrite (Pin_Relay, HIGH); //set relay on 
  //EPD.image(PICTURE_BITS, ESCUDO_BITS);

  }

void TurnLightOff(){
  digitalWrite (Pin_Relay, LOW); //set relay off}
 
  //EPD.image(PICTURE_BITS, TEXT_BITS);
  
}

