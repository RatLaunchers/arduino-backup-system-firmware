/**
 * Backup system for CanSat
 * Has not been tested yet
 * @author Suyu
 * @version 0.2
 * 
 * SD Card Module Wiring:
 *  CS      -- 10
 *  SCK     -- 13
 *  MOSI    -- 11
 *  MISO    -- 12
 *  VCC     -- 5V
 *  GND     -- GND
 * 
 * DHT11 Wiring:
 *  VCC     -- 3.3V or 5V
 *  GND     -- GND
 *  S       -- 9
 * 
 * BMP280 Wiring:
 *  VCC     -- 3.3V or 5V
 *  GND     -- GND
 *  SCL     -- A5
 *  SDA     -- A4
 */
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <SD.h>
#include <SPI.h>

#define DHT_PIN 8
#define BUZZER_PIN 9
#define ERROR_BEEP_FREQ 500
#define BEEP_DURATION 500

#define SD_ERROR 1
#define FILE_ERROR 2
#define BMP_ERROR 3

DHT dht(DHT_PIN, DHT11);
Adafruit_BMP280 bmp;  // no parameters defaults to using I2C

File dataFile;

void setup() {
    Serial.begin(9600);

    // initialize SD and file
    if (!SD.begin()) {
        Serial.println("SD card error");
        errorBeep(SD_ERROR);
    }
    dataFile = SD.open("data.txt", FILE_WRITE);
    if (!dataFile) {
        Serial.println("File opening error");
        errorBeep(FILE_ERROR);
    }

    // initialize sensors
    dht.begin();
    if (!bmp.begin()) {
        Serial.println("BMP280 error");
        errorBeep(BMP_ERROR);
    }

    // add this to separate data from anything previously written in the file
    dataFile.println("\nNEW DATA LOG");
}

void loop() {
    dataFile.print(millis() / 1000);  // time in seconds
    dataFile.print(" DHT T:");
    dataFile.print(dht.readTemperature());
    dataFile.print(" DHT H:");
    dataFile.print(dht.readHumidity());
    dataFile.print(" BMP T:");
    dataFile.print(bmp.readTemperature());
    dataFile.print(" BMP P:");
    dataFile.println(bmp.readPressure());
    dataFile.flush();  // physically save data to SD card
    delay(1000);
}

void errorBeep(byte errorCode){
    while(1){
        tone(BUZZER_PIN, ERROR_BEEP_FREQ);
        delay(BEEP_DURATION*errorCode);
        noTone(BUZZER_PIN);
        delay(BEEP_DURATION);
    }
}