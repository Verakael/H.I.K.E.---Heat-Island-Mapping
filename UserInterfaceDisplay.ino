// User interface display written by Jack Hotchkiss
// Last updated: 11/8/22


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <String.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHT11, 6);//connect dht out to d2 on board

//getTemp will retrieve the current temperature data from the Sensors. This function can be expanded to properly retrieve temp data later.
float getTemp(){
    return dht.readTemperature(true); 
}

//getHum will retrieve the current humidity data from the Sensors. This function can be expanded to properly retrieve humidity data later.
float getHum(){
  return dht.readHumidity(); 
}

void setup() {
  Serial.begin(9600);
  dht.begin();
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
    Serial.print(getTemp());
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


void displayTemp(float t) {

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


void displayHumidity(float h) {
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















