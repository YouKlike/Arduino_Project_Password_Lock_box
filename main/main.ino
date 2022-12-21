#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
#include <Servo.h>   //載入函式庫，這是內建的，不用安裝

Servo myservo;  // 建立SERVO物件

// LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。
LiquidCrystal_I2C lcd(0x27, 16, 2); 
#include <Adafruit_Fingerprint.h>

#include <Keypad.h>    // 引用Keypad程式庫
// #define KEY_ROWS 4 // 按鍵模組的列數
// #define KEY_COLS 4 // 按鍵模組的行數
// int colPins[KEY_COLS] = {14, 15, 16, 17};	   // 按鍵模組，行1~4接腳。
// int rowPins[KEY_ROWS] = {18, 19, 20, 21}; // 按鍵模組，列1~4接腳。


#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(8, 9);

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define mySerial Serial1

#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
  pinMode(11,INPUT);
  myservo.attach(10); // 設定要將伺服馬達接到哪一個PIN腳
  myservo.write(0);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }

  
}
void touch_Sensor() {
  if (digitalRead(11) == HIGH) {
    myservo.write(90);
  }
}


void detectNumber() {
}

void loop() {
  touch_Sensor();
  // detectNumber();
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      lcd.setCursor(0, 0); // (colum, row)從第一排的第三個位置開始顯示
      lcd.print("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    lcd.setCursor(0, 0); // (colum, row)從第一排的第三個位置開始顯示
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Error");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  myservo.write(0);
  lcd.setCursor(12,0);
  lcd.print("    ");
  lcd.setCursor(0, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print("ID: ");
  lcd.print(finger.fingerID);
  lcd.print(" unlock");
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}
 
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  lcd.setCursor(2, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print(finger.fingerID);
  lcd.setCursor(2, 1); // (colum,row)從第二排第三格位置開始顯示
  lcd.print(finger.confidence);

  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}