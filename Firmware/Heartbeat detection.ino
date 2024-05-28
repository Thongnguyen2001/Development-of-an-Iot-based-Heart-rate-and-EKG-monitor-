unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 50;          // interval at which to blink (milliseconds)

#define pin_sinyal PA0
int BPM,BPM_total;
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels..
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const unsigned char epd_bitmap_heartbeat[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
  0xc0, 0x1f, 0xe0, 0x00, 0x00, 0x7f, 0xe0, 0x3f, 0xf0, 0x00, 0x01, 0xff, 0xf0, 0x7f, 0xfc, 0x00,
  0x01, 0xff, 0xf8, 0xff, 0xfc, 0x00, 0x03, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xff, 0xff,
  0xff, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x07, 0xff, 0x3f, 0xff, 0xff, 0x00, 0x07, 0xff, 0x1f, 0xff, 0xff, 0x00,
  0x07, 0xff, 0x0f, 0xcf, 0xff, 0x00, 0x07, 0xfe, 0x0f, 0xc7, 0xff, 0x00, 0x07, 0xfe, 0x4f, 0x87,
  0xff, 0x00, 0x03, 0xfc, 0x47, 0x87, 0xfe, 0x00, 0x00, 0xf8, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xe3, 0x30, 0x00, 0x00, 0x00, 0x00, 0xf2, 0x38, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x7f, 0xf0, 0x00,
  0x00, 0x3f, 0xf8, 0x7f, 0xe0, 0x00, 0x00, 0x1f, 0xf8, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xfc, 0xff,
  0x80, 0x00, 0x00, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x01,
  0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
void setup() {
  Serial1.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial1.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.clearDisplay();
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000);  // Pause for 2 seconds
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.setTextSize(2);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);
  display.println(F("Heart Beat"));
  display.setTextSize(3);
  display.setCursor(10, 30);
  display.println(F("999"));
  display.setTextSize(1);
  display.setCursor(65, 50);
  display.println(F("BPM"));
  display.drawBitmap(84, 22, epd_bitmap_heartbeat, 44, 41, 1);
  display.setTextSize(3);
  display.display();
}
unsigned long clear_screen;
int a=123;
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    hitung_HR(analogRead(pin_sinyal));
    //    Serial1.println(analogRead(pin_sinyal));
  }
  if ((unsigned long)(millis() - clear_screen) > 1000) {
    display.fillRect(10, 30, 51, 23, SSD1306_BLACK);
    display.setCursor(10, 30);
    display.println(BPM);
    display.display();
    clear_screen = millis();
  }
  //Serial1.println(BPM);
}

unsigned long oldtime = 0;
unsigned long newtime = 0;
unsigned long beat_time = 0;
unsigned long cek_beat_time = 0;
int data_now, data_old, delta_data;
bool flag_detek = false;
float HR, HR_old;
int count;
void hitung_HR(int data_pulse) {
  data_now = data_pulse;
  
  Serial1.println(String(data_now) + "," + String(BPM));
  
  delta_data = data_now - data_old;
  if (delta_data < 0)
    delta_data = delta_data * -1;
  data_old = data_now;

  //Serial1.println(data_now);
  //Serial1.println(delta_data);d
  if (delta_data > 140)  // detek pertama
  {
    if (flag_detek == false) {
      flag_detek = true;
      newtime = millis();
    } else {
      beat_time = millis() - newtime;
      if (beat_time < 400) {
        newtime = millis();
        //        beat_time = millis();
      } else {
        HR = 60 / (((float)beat_time) / 1000);
        HR = HR * 0.6 + HR_old * 0.4;
        if (abs(HR - HR_old) > 10) {
          HR = 60 / (((float)beat_time) / 1000);
          HR = HR * 0.1 + HR_old * 0.9;
        }
        //Serial1.println(beat_time);
        flag_detek = false;
        HR_old = HR;
      }
    }
  }

  // cancel pertitungan
  // 150 BPM = 400 ms dan 40 BPM = 1500 ms
  cek_beat_time = millis() - newtime;
  if (cek_beat_time > 10000) {
    newtime = millis();
    HR = 0;
  }
count++;
BPM_total=BPM_total+HR;

if(count==100)
{
  BPM=BPM_total/100;
  BPM=BPM*0.9258+2.4162;
  BPM_total=0;
  count=0;
}

}