#ifndef _OLED_DISPLAY_H_
#define _OLED_DISPLAY_H_

#include "EnvData.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>

const int OLED_ADDRESS_1 = 0x3C;
const int OLED_WIDTH = 128;
const int OLED_HEIGHT = 64;


// In charge of displaying all data to my OLED display.
class OLED_Wrapper {
private:
    Adafruit_SSD1306 myDisplay;

public:
    OLED_Wrapper() : myDisplay(-1) {
        myDisplay.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS_1);
        myDisplay.display();
        myDisplay.setTextColor(WHITE);
    }

    void print(EnvData *data) {
        myDisplay.clearDisplay();
        myDisplay.setCursor(0, 0);
        myDisplay.printf("%02d/%02d/%04d     %02d:%02d\n", Time.day(), Time.month(), Time.year(), Time.hour(), Time.minute());
        myDisplay.printf("Temp: %2d C\n", data->temperature);
        myDisplay.printf("Humid: %d hPa\n", data->humidity);
        myDisplay.printf("Soil: %04d\n", data->soilMoisture);
        myDisplay.printf("Air: ");
        switch (data->airQuality) {
        case 1:
            myDisplay.printf("High Polution\n");
            break;
        case 2:
            myDisplay.printf("Low Polution\n");
            break;
        case 3:
            myDisplay.printf("Fresh\n");
            break;
        default:
            myDisplay.printf("Unknown\n");
            break;
        }
        myDisplay.printf("Dust: %.2f cs/10mcf", data->dustDensity);
        myDisplay.display();
    }
};

#endif