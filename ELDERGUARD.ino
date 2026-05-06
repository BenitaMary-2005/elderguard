#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ====== Wi-Fi Credentials ======
const char* ssid = "AASHIQ";
const char* password = "04000106";

// ====== Telegram Bot Info ======
String botToken = "8411883834:AAFrhV2Orv5_13GrMkFogj8M_2z28Wlx7jA";
String chatID = "-1003150496794";

// ====== Pin Configuration ======
int pirPin = 27;
int buzzer = 26;
int led = 25;
int buttonPin = 18;  // Push button

// ====== Timing ======
unsigned long lastMovementTime = 0;
unsigned long alertDelay = 10000; // 10 seconds (no movement alert)
bool alertNoMovementSent = false;
bool alertMovementSent = false;

// ====== LCD Setup ======
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ====== Function: Send Telegram Message ======
void sendTelegramMessage(String text) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + botToken + "/sendMessage?chat_id=" + chatID + "&text=" + text;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Telegram Message Sent: " + text);
    } else {
      Serial.println("Error sending message");
    }
    http.end();
  }
}

// ====== Setup Function ======
void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up for button
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("ELDER GUARD");
  lcd.setCursor(0, 1);
  lcd.print("Status: Idle");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // Send Telegram startup message
  sendTelegramMessage("🟢 ElderGuard System Started! Monitoring is active 👀");
  lastMovementTime = millis();
}

// ====== Loop Function ======
void loop() {
  int motion = digitalRead(pirPin);
  int buttonState = digitalRead(buttonPin); // Read button state
  unsigned long idleTime = millis() - lastMovementTime;

  // ====== Manual Reset via Button ======
  if (buttonState == LOW) { // Button pressed
    Serial.println("Button Pressed: Resetting alerts");
    alertNoMovementSent = false;
    alertMovementSent = false;
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status: Reset  ");
    delay(500); // Debounce
  }

  // ====== PIR Motion Detection ======
  if (motion == HIGH) {
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    lastMovementTime = millis();
    lcd.setCursor(0, 1);
    lcd.print("Status: Moving ");

    // Send movement alert (once)
    if (!alertMovementSent) {
      sendTelegramMessage("✅ Movement detected! The person is active 🏃‍♀");
      Serial.println("Movement alert sent!");
      alertMovementSent = true;
      alertNoMovementSent = false;
    }

  } else {
    lcd.setCursor(0, 1);
    lcd.print("Status: Idle   ");

    // Send alert if no movement for 10 seconds
    if (idleTime >= alertDelay && !alertNoMovementSent) {
      digitalWrite(led, HIGH);
      digitalWrite(buzzer, HIGH);
      sendTelegramMessage("⚠ ALERT! No movement detected for 10 seconds ⏳ Please check!");
      Serial.println("No movement alert sent!");
      alertNoMovementSent = true;
      alertMovementSent = false;
    }
  }

  delay(100);
}
