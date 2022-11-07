// First iteration of a user interface display written by Jack Hotchkiss
// 11/6/22


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <String.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//getTemp will retrieve the current temperature data from the Sensors. This function can be expanded to properly retrieve temp data later.
int getTemp(){
    return random(70,80); //70 as minimum random value and 80 as maximum
}

//getHum will retrieve the current humidity data from the Sensors. This function can be expanded to properly retrieve humidity data later.
int getHum(){
  return random(40,60); //40 as minimum random value and 60 as maximum
}

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();  //clear the display before anything else happens
  
  while(true){ //start with another clear display call, display time/date/battery at top, draw the line 10 pixels from the top, display temp and humidity, repeat after 1.5 seconds
    display.clearDisplay();
    timeBattery();
    display.drawLine(0, 10, 128, 10, WHITE);
    displayTemp(getTemp());
    displayHumidity(getHum());
    delay(1500);
  }
}

void loop() {

}

void timeBattery(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.write("Time/Date    Battery");
  display.display();
}


void displayTemp(int t) {

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  String temp = "\n\nTemperature: ";
  temp += t;                  // adds the retrieved temp to the end of the string that will be converted to a charArray for displaying
  char out[20];
  temp.toCharArray(out, 20);
  display.write(out);
  display.display();
}


void displayHumidity(int h) {
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  String humidity = "\n\n\n\nHumidity: ";
  humidity += h;                // adds the retrieved humidity to the end of the string that will be converted to a charArray for displaying
  char out[20];
  humidity.toCharArray(out, 20);
  display.write(out);
  
  display.display();
}















