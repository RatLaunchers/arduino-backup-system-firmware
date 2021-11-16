/**
 * Backup system for CanSat
 * Has not been tested yet
 * @author Suyu
 * @version 0.1 
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

#define DHT_PIN 9

DHT dht(DHT_PIN, DHT11);
Adafruit_BMP280 bmp;  // no parameters defaults to using I2C

File dataFile;

void setup() {
    Serial.begin(9600);

    // initialize SD and file
    if (!SD.begin()) {
        Serial.println("initialization failed!");
        while (1);
    }
    dataFile = SD.open("data.txt", FILE_WRITE);
    if (!dataFile) {
        Serial.println("Error opening file");
        while (1);
    }

    // initialize sensors
    dht.begin();
    if (!bmp.begin()) {
        Serial.println("BMP280 error");
        while (1);
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