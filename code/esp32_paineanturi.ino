/*
 * Alipaineellinen Filamenttikotelo - ESP32 Automaatiojärjestelmä
 * 
 * Versio: 2.0 - TÄYSI AUTOMAATIO
 * Päivitetty: 14.1.2026
 * 
 * Ominaisuudet:
 * - BME280: Paine + lämpötila + kosteus
 * - OLED-näyttö (128x64)
 * - Web UI: Reaaliaikainen seuranta, ohjaus, historia
 * - Automaattinen pumppuohjaus (säädettävä tavoitepaine)
 * - Automaattinen kannen avaus (lineaaritoimilaite)
 * - RGB LED-nauha (WS2812B): Tilavalo + animaatiot
 * - Magneettikytkimet: Kannen tilan tunnistus
 * - Sähköventtiili: Paineen vapautus
 * - Ääniefektit (DFPlayer Mini, valinnainen)
 * - Historia: SD-korE280.h>  // Vaihdettu BMP280 -> BME280 (paine+lämpö+kosteus)
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <FastLED.h>           // RGB LED-nauha
#include <ESP32Servo.h>        // Lineaaritoimilaite/servo
// #include <DFRobotDFPlayerMini.h>  // Valinnainen: ääniefektitGFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

// ========== ASETUKSET ==========

// WiFi-asetukset
const char* ssid = "VAIHDA_ - SÄÄDETTÄVISSÄ WEB UI:STA
float PRESSURE_TARGET = -25.0;           // Tavoitepaine
float PRESSURE_HYSTERESIS = 3.0;         // Hystereesin leveys
const float PRESSURE_ALARM = -5.0;       // Hälytys: vuoto havaittu
const float HUMIDITY_ALARM = 60.0;       // Hälytys: liikaa kosteutta

// Kannen avauksen asetukset
const int LID_OPEN_DELAY = 5000;         // Odotus ennen avausta (ms)
const int LID_CLOSE_DURATION = 8000;     // Kannen sulkemisen kesto (ms)
const int ACTUATOR_OPEN_POSITION = 180;  // Täysin auki (PWM tai servo-kulma)
const int ACTUATOR_CLOSED_POSITION = 0;  // Kiinnius)
const int LINEAR_ACTUATOR_PIN = 15;    // Lineaaritoimilaite (kannen avaus)
const int LID_CLOSED_SENSOR = 32;      // Magneettikytkimet: kiinni
const int LID_OPEN_SENSOR = 33;        // Magneettikytkimet: auki
const int LED_STRIP_PIN = 13;          // WS2812B RGB LED-nauha
const int BUZZER_PIN = 12;             // Buzzeri äänille (valinnainen)

// LED-nauhan asetukset
#define NUM_LEDS 30
CRGB leds[NUM_LEDS];s päältä
const float PRESSURE_HIGH_THRESHOLD = -15.0;  // Pumppu päälle
const float PRESSURE_ALARM = -5.0;            // Hälytys: vuoto havaittu

// GPIO-pinE280 bme;  // Vaihdettu BMP280 -> BME280
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WebServer server(80);
Servo actuatorServo;  // Lineaaritoimilaite (voi olla servo tai PWM)

// Anturidata
float referencePressure = 0;      // Ulkoilman paine (kPa) - alustetaan käynnistyksessä
float currentPressure = 0;        // Nykyinen absoluuttinen paine (kPa)
float relativePressure = 0;       // Suhteellinen paine (kPa), negatiivinen = alipaine
float temperature = 0;            // Lämpötila (°C)
float humidity = 0;               // Kosteus (% RH)

// Tila
bool pumpState = false;           // Pumpun tila
bool alarmState = false;          // Hälytyksen tila
bool lidClosed = false;           // Kansi kiinni
bool lidOpening = false;          // Kansi avautumassa
bool autoMode = true;             // Automaattinen pumppu + avaus
enum LidState { CLOSED, OPENING, OPEN, CLOSING };
LidState lidState = CLOSED;nta mittausta tallennetaan historiaan
E280-anturi
bool initBME280() {
  if (!bme.begin(0x76)) {  // BME280 osoite yleensä 0x76 tai 0x77
    Serial.println("BME280-anturia ei löydy!");
    return false;
  }
  
  // Anturin asetukset
  bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                  Adafruit_BME280::SAMPLING_X2,   // Temp
                  Adafruit_BME280::SAMPLING_X16,  // Paine
                  Adafruit_BME280::SAMPLING_X1,   // Kosteus
                  Adafruit_BME280::FILTER_X16,
                  Adafruit_BME280::STANDBY_MS_500);
  
  Serial.println("BME = 0;        // Nykyinen absoluuttinen paine (kPa)
float relativePressure = 0;       // Suhteellinen paine (kPa), negatiivinen = alipaine
bool pumpState = false;           // Pumpun tila
bool alarmState = false;          // Hälytyksen tila

// Paineen historia
float pressureHistory[HISTORY_SIZE];
int historyIndex = 0;
int historyCount = 0;

unsigned long lastMeasurement = 0;
unsigned long lastLog = 0;

// ========== FUNKTIOT ==========

// Alusta BMP280-anturi
bool initBMP280() {
  if (!bmp.begin(0x76)) {  // BMP280 osoite yleensä 0x76 tai 0x77
    Serial.println("BMP280-anturia ei löydy!");
    return false;
  }
  
  // Anturin asetukset
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
  
  Serial.println("BMP280 alustettu!");
  return true;
}

// Alusta OLED-näyttö
bool initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED-näyttöä ei löydy!");
    return false;
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Filamenttikotelo");
  display.println("Alustetaan...");
  display.display();
  
  Seriakaikki anturidata
void readSensors() {
  currentPressure = bme.readPressure() / 1000.0;  // Muunna Pa -> kPa
  relativePressure = currentPressure - referencePressure;
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  
  // Lisää historiaan
  pressureHistory[historyIndex] = relativePressure;
  historyIndex = (historyIndex + 1) % HISTORY_SIZE;
  if (historyCount < HISTORY_SIZE) historyCount++;
  
  // Lue kannen tila magneettikytkimistä
  lidClosed = digitalRead(LID_CLOSED_SENSOR) == LOW;  // LOW = magneetti lähellä
  bool lidFullyOpen = digitalRead(LID_OPEN_SENSOR) == LOW;
  
  // Päivitä kannen tila
  if (lidFullyOpen) lidState = OPEN;
  else if (lidClosed) lidState = CLOSED
  WiFi.begin(ssid, password);
  : ");
  display.print(relativePressure, 1);
  display.println(" kPa");
  
  display.print("T: ");
  display.print(temperature, 1);
  display.print("C  H: ");
  display.print(humidity, 0);
  display.println("%");
  
  display.println();
  
  // Tila
  if (alarmState) {
    display.println("! HALYTYS !");
  } else if (lidState == OPENING) {
    display.println("Avataan...");
  } else if (lidState == OPEN) {
    display.println("AUKI");
  } else if (relativePressure < (PRESSURE_TARGET + 5)) {
    display.println("OK - TIIVIS");
  } else {
    display.println("Pumpataan...");
  }
  
  display.println();
  
  // Pumpun tila ja kansi
  display.print("Pump:");
  display.print(pumpState ? "ON " : "OFF");
  display.print(" Lid:");
  display.println(lidClosed ? "KIINNI" : "AUKI1000.0;  // Muunna Pa -> kPa
  relativePressure = currentPressure - referencePressure;
  
  // Lisää historiaan
  pressureHistory[historyIndex] = relativePressure;
  historyIndex = (historyIndex + 1) % HISTORY_SIZE;
  if (historyCount < HISTORY_SIZE) historyCount++;
}

// Päivitä OLED-näyttö
void updateDisplay() {
  display.clearD (säädettävällä tavoitepaineella)
void controlPump() {
  if (!autoMode || !lidClosed) {
    // Ei automaattista pumppua jos ei automaatissa tai kansi auki
    if (pumpState) {
      pumpState = false;
      digitalWrite(PUMP_RELAY_PIN, LOW);
    }
    return;
  }
  
  float upperLimit = PRESSURE_TARGET + PRESSURE_HYSTERESIS;
  float lowerLimit = PRESSURE_TARGET - PRESSURE_HYSTERESIS;
  
  if (relativePressure > upperLimit && !pumpState) {
    // Paine liian korkea → käynnistä pumppu
    pumpState = true;
  bool alarm = false;
  
  // Paine-hälytys
  if (relativePressure > PRESSURE_ALARM && lidClosed) {
    alarm = true;
    Serial.println("HÄLYTYS: Vuoto - Automaatio</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; max-width: 900px; margin: 0 auto; padding: 20px; background: #1e1e1e; color: #fff; }";
  html += "h1 { color: #4CAF50; text-align: center; }";
  html += ".grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); gap: 15px; }";
  html += ".card { padding: 20px; background: #2d2d2d; border-radius: 8px; }";
  html += ".value { font-size: 2.5em; color: #4CAF50; font-weight: bold; }";
  html += ".small-value { font-size: 1.8em; color: #4CAF50; }";
  html += ".alarm { color: #ff4444; }";
  html += ".ok { color: #4CAF50; }";
  html += ".warning { color: #ffaa00; }";
  html += "button { padding: 12px 24px; margin: 5px; font-size: 16px; background: #4CAF50; color: white; border: none; border-radius: 4px; cursor: pointer; width: calc(50% - 10px); }";
  html += "button:hover { background: #45a049; }";
  html += "button.danger { background: #ff4444; }";
  html += "button.danger:hover { background: #cc0000; }";
  html += "input[type='range'] { width: 100%; }";
  html += ".lid-big { font-size: 3em; text-align: center; margin: 20px 0; }";
  html += "</style>";
  html += "<script>";
  html += "setInterval(function(){ fetch('/data').then(r=>r.json()).then(d=>{";
  html += "document.getElementById('pressure').innerText=d.pressure.toFixed(1);";
  html += "document.getElementById('temp').innerText=d.temperature.toFixed(1);";
  html += "document.getElementById('humidity').innerText=d.humidity.toFixed(0);";
  html += "document.getElementById('status').innerText=d.status;";
  html += "document.getElementById('status').className=d.alarm?'alarm':'ok';";
  html += "document.getElementById('pump').innerText=d.pump;";
  html += "document.getElementById('lid').innerText=d.lid;";
  html += "document.getElementById('target').innerText=d.target;";
  html += "}); }, 2000);";
  html += "</script>";
  html += "</head><body>";
  
  html += "<h1>🗄️ Filamenttikotelo - Automaatio v2.0</h1>";
  
  // Kannen tila (iso)
  html += "<div class='card'>";
  html += "<h2>Kannen tila</h2>";
  html += "<div class='lid-big' id='lid'>" + String(lidClosed ? "🔒 KIINNI" : "🔓 AUKI") + "</div>";
  html += "<button onclick=\"fetch('/lid/open')\" style='width: 100%;'>🚪 AVAA KANSI</button>";
  html += "</div>";
  
  // Grid: Mittaukset
  html += "<div class='grid'>";
  
  html += "<div class='card'>";
  html += "<h3>Paine</h3>";
  html += "<div class='value' id='pressure'>" + String(relativePressure, 1) + "</div>";
  html += "<p>kPa (tavoite: <span id='target'>" + String(PRESSURE_TARGET, 1) + "</span>)</p>";
  html += "</div>";
  
  html += "<div class='card'>";
  html += "<h3>Lämpötila</h3>";
  html += "<div class='small-value' id='temp'>" + String(temperature, 1) + "</div>";
  html += "<p>°C</p>";
  html += "</div>";
  
  html += "<div class='card'>";
  html += "<h3>Kosteus</h3>";
  html += "<div class='small-value' id='humidity'>" + String(humidity, 0) + "</div>";
  html += "<p>% RH</p>";
  html += "</temperature\":" + String(temperature, 2) + ",";
  json += "\"humidity\":" + String(humidity, 1) + ",";
  json += "\"target\":" + String(PRESSURE_TARGET, 1) + ",";
  json += "\"status\":\"" + String(alarmState ? "HÄLYTYS" : "OK") + "\",";
  json += "\"alarm\":" + String(alarmState ? "true" : "false") + ",";
  json += "\"pump\":\"" + String(pumpState ? "PÄÄLLÄ" : "POIS") + "\",";
  json += "\"lid\":\"" + String(lidClosed ? "KIINNI" : "AUKI
  html += "</div>";
  
  // Tila
  html += "<div class='card'>";
  html += "<h2>Järjestelmän tila</h2>";
  html += "<p class='" + String(alarmState ? "alarm" : "ok") + "' id='status' style='font-size:1.5em;'>";
  html += alarmState ? "⚠️ HÄLYTYS" : "✓ Kaikki OK";
  html += "</p>";
  html += "<p>Pumppu: <strong id='pump'>" + String(pumpState ? "PÄÄLLÄ" : "POIS") + "</strong></p>";
  html += "</div>";
  
  // Ohjaus
  html += "<div class='card'>";
  html += "<h2>Manuaalinen ohjaus</h2>";
  html += "<button onclick=\"fetch('/pump/on')\">▶️ Pumppu ON</button>";
  html += "<button onclick=\"fetch('/pump/off')\" class='danger'>⏸️ Pumppu OFF</button>";
 

// Avaa kansi
void handleLidOpen() {
  openLid();
  server.send(200, "text/plain", "Kansi avataan...");
}

// Venttiiliohjaus
void handleValveOpen() {
  digitalWSOLENOID_VALVE_PIN, OUTPUT);
  pinMode(LID_CLOSED_SENSOR, INPUT_PULLUP);
  pinMode(LID_OPEN_SENSOR, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(PUMP_RELAY_PIN, LOW);
  digitalWrite(SOLENOID_VALVE_PIN, LOW);  // Venttiili kiinni
  
  // Alusta servo/lineaaritoimilaite
  actuatorServo.attach(LINEAR_ACTUATOR_PIN);
  actuatorServo.write(ACTUATOR_CLOSED_POSITION);
  E280()) {
    Serial.println("VIRHE: BME
  FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  fill_solid(leds, NUM_LEDS, CRGB::Yellow);
  FastLED.show(, LOW);
  server.send(200, "text/plain", "Venttiili kiinni");
}

// Asetukset: tavoitepaine
void handleSettingsTarget() {
  if (server.hasArg("vale.readPressure() / 1000.0;
  Serial.print("Referenssipaine: ");
  Serial.print(referencePressure);
  Serial.println(" kPa");
  
  // Lue alku lämpötila ja kosteus
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  Serial.print("Lämpötila: ");
  Serial.print(temperature);
  Serial.print(" °C, Kosteus: ");
  Serial.print(humidity);
  Serial.println(" %SSURE_TARGET);
    server.senlid/open", handleLidOpen);
  server.on("/valve/open", handleValveOpen);
  server.on("/valve/close", handleValveClose);
  server.on("/settings/target", handleSettingsTarget);
  server.on("/d(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Virheellinen pyyntö");
  }
} html += "<button onclick=\"fetch('/valve/open')\">💨 Avaa venttiili</button>";
  html += "<button onclick=\"fetch('/valve/close')\" class='danger'>🔒 Sulje venttiili</button>";
  html += "</div>";
  
  // Asetukset
  html += "<div class='card'>";
  html += "<h2>Asetukset</h2>";
  html += "<p>Tavoitepaine: <strong>" + String(PRESSURE_TARGET, 1) + " kPa</strong></p>";
  html +Sensors();
    controlPump();
    checkAlarms();
    updateDisplay();
    updateLEDs();
    
    // Tulosta sarjaporttiin
    Serial.print("P: ");
    Serial.print(relativePressure, 2);
    Serial.print(" kPa | T: ");
    Serial.print(temperature, 1);
    Serial.print(" °C | H: ");
    Serial.print(humidity, 0);
    Serial.print(" % | Pump: ");
    Serial.print(pumpState ? "ON" : "OFF");
    Serial.print(" | Lid: ");
    Serial.print(lidClosed ? "CLOSED" : "OPEN");
    Serial.print(" | Alarm: ");
    Serial.println(alarmState ? "YES" : "NO
  digitalWrite(PUMP_RELAY_PIN, LOW);
  
  // 2. Avaa venttiili (paine tasaantuu)
  digitalWrite(SOLENOID_VALVE_PIN, HIGH);
  Serial.println("Venttiili auki - paine tasaantuu...");
  
  // 3. Odota että paine tasaantuu
  unsigned long startTime = millis();
  while (millis() - startTime < LID_OPEN_DELAY) {
    readSensors();
    updateDisplay();
    updateLEDs();
    delay(100);
    
    // Tarkista onko paine tasaantunut
    if (relativePressure > -2.0) {
      Serial.println("Paine tasaantunut!");
      break;
    }
  }
  
  // 4. Ääniefekti (valinnainen)
  tone(BUZZER_PIN, 1000, 200);
  delay(300);
  tone(BUZZER_PIN, 1500, 200);
  
  // 5. Avaa kansi lineaaritoimilaitteella
  Serial.println("Avataan kantta...");
  actuatorServo.write(ACTUATOR_OPEN_POSITION);
  
  // 6. Odota että kansi on täysin auki
  delay(LID_CLOSE_DURATION);
  
  lidState = OPEN;
  Serial.println("Kansi auki!");
}

// Sulje kansi automaattisesti
void closeLid() {
  if (lidState != OPEN) return;
  
  Serial.println(">>> SULJETAAN KANSI <<<");
  lidState = CLOSING;
  
  // 1. Sulje kansi lineaaritoimilaitteella
  actuatorServo.write(ACTUATOR_CLOSED_POSITION);
  delay(LID_CLOSE_DURATION);
  
  // 2. Sulje venttiili
  digitalWrite(SOLENOID_VALVE_PIN, LOW);
  
  // 3. Käynnistä pumppu automaattisesti
  if (autoMode) {
    delay(1000);
    pumpState = true;
    digitalWrite(PUMP_RELAY_PIN, HIGH);
    Serial.println("Pumppu käynnistetty");
  }
  
  lidState = CLOSED;
  Serial.println("Kansi suljettu!");f (alarmState) {
    display.println("VUOTO!");
  } else if (relativePressure < -10) {
    display.println("OK - TIIVIS");
  } else {
    display.println("Huom: Alipaine");
  }
  
  display.println();
  
  // Pumpun tila
  display.print("Pumppu: ");
  display.println(pumpState ? "ON" : "OFF");
  
  // WiFi-tila
  if (WiFi.status() == WL_CONNECTED) {
    display.print("IP: ");
    display.println(WiFi.localIP().toString().substring(0, 15));
  }
  
  display.display();
}

// Ohjaa pumppua
void controlPump() {
  if (relativePressure > PRESSURE_HIGH_THRESHOLD && !pumpState) {
    // Paine liian korkea → käynnistä pumppu
    pumpState = true;
    digitalWrite(PUMP_RELAY_PIN, HIGH);
    Serial.println("Pumppu PÄÄLLE");
  } else if (relativePressure < PRESSURE_LOW_THRESHOLD && pumpState) {
    // Paine riittävän alhainen → sammuta pumppu
    pumpState = false;
    digitalWrite(PUMP_RELAY_PIN, LOW);
    Serial.println("Pumppu POIS");
  }
}

// Tarkista hälytykset
void checkAlarms() {
  if (relativePressure > PRESSURE_ALARM) {
    alarmState = true;
    digitalWrite(LED_ALARM_PIN, HIGH);
    digitalWrite(LED_OK_PIN, LOW);
    Serial.println("HÄLYTYS: Vuoto havaittu!");
  } else {
    alarmState = false;
    digitalWrite(LED_ALARM_PIN, LOW);
    digitalWrite(LED_OK_PIN, HIGH);
  }
}

// Web-palvelin: pääsivu
void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Filamenttikotelo</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; background: #1e1e1e; color: #fff; }";
  html += "h1 { color: #4CAF50; }";
  html += ".status { padding: 20px; background: #2d2d2d; border-radius: 8px; margin: 20px 0; }";
  html += ".value { font-size: 2em; color: #4CAF50; }";
  html += ".alarm { color: #ff4444; }";
  html += ".ok { color: #4CAF50; }";
  html += "button { padding: 10px 20px; font-size: 16px; background: #4CAF50; color: white; border: none; border-radius: 4px; cursor: pointer; }";
  html += "button:hover { background: #45a049; }";
  html += "</style>";
  html += "<script>";
  html += "setInterval(function(){ fetch('/data').then(r=>r.json()).then(d=>{ document.getElementById('pressure').innerText=d.pressure.toFixed(1); document.getElementById('status').innerText=d.status; document.getElementById('pump').innerText=d.pump; }); }, 2000);";
  html += "</script>";
  html += "</head><body>";
  
  html += "<h1>🗄️ Filamenttikotelo</h1>";
  
  html += "<div class='status'>";
  html += "<h2>Paine kotelossa</h2>";
  html += "<div class='value' id='pressure'>" + String(relativePressure, 1) + "</div>";
  html += "<p>kPa (negatiivinen = alipaine)</p>";
  html += "</div>";
  
  html += "<div class='status'>";
  html += "<h2>Tila</h2>";
  html += "<p class='" + String(alarmState ? "alarm" : "ok") + "' id='status'>";
  html += alarmState ? "VUOTO!" : "OK - Tiivis";
  html += "</p>";
  html += "</div>";
  
  html += "<div class='status'>";
  html += "<h2>Pumppu</h2>";
  html += "<p id='pump'>" + String(pumpState ? "PÄÄLLÄ" : "POIS PÄÄLTÄ") + "</p>";
  html += "</div>";
  
  html += "<div class='status'>";
  html += "<h2>Ohjaus</h2>";
  html += "<button onclick=\"fetch('/pump/on')\">Pumppu päälle</button> ";
  html += "<button onclick=\"fetch('/pump/off')\">Pumppu pois</button> ";
  html += "<button onclick=\"fetch('/reset')\">Nollaa hälytys</button>";
  html += "</div>";
  
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

// Web-palvelin: JSON-data
void handleData() {
  String json = "{";
  json += "\"pressure\":" + String(relativePressure, 2) + ",";
  json += "\"status\":\"" + String(alarmState ? "VUOTO" : "OK") + "\",";
  json += "\"pump\":\"" + String(pumpState ? "PÄÄLLÄ" : "POIS") + "\"";
  json += "}";
  
  server.send(200, "application/json", json);
}

// Manuaalinen pumppuohjaus
void handlePumpOn() {
  pumpState = true;
  digitalWrite(PUMP_RELAY_PIN, HIGH);
  server.send(200, "text/plain", "Pumppu päällä");
}

void handlePumpOff() {
  pumpState = false;
  digitalWrite(PUMP_RELAY_PIN, LOW);
  server.send(200, "text/plain", "Pumppu pois");
}

void handleReset() {
  alarmState = false;
  server.send(200, "text/plain", "Hälytys nollattu");
}

// ========== SETUP ==========

void setup() {
  Serial.begin(115200);
  Serial.println("Käynnistetään Filamenttikotelo...");
  
  // Alusta pinnit
  pinMode(PUMP_RELAY_PIN, OUTPUT);
  pinMode(LED_OK_PIN, OUTPUT);
  pinMode(LED_ALARM_PIN, OUTPUT);
  
  digitalWrite(PUMP_RELAY_PIN, LOW);
  digitalWrite(LED_OK_PIN, LOW);
  digitalWrite(LED_ALARM_PIN, LOW);
  
  // Alusta I2C
  Wire.begin();
  
  // Alusta anturi ja näyttö
  if (!initBMP280()) {
    Serial.println("VIRHE: BMP280 ei käynnisty!");
    while (1) delay(1000);
  }
  
  if (!initDisplay()) {
    Serial.println("VIRHE: OLED ei käynnisty!");
  }
  
  // Lue referenssipaine (ulkoilman paine)
  delay(1000);
  referencePressure = bmp.readPressure() / 1000.0;
  Serial.print("Referenssipaine: ");
  Serial.print(referencePressure);
  Serial.println(" kPa");
  
  // Alusta WiFi
  initWiFi();
  
  // Web-palvelin
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.on("/pump/on", handlePumpOn);
  server.on("/pump/off", handlePumpOff);
  server.on("/reset", handleReset);
  server.begin();
  Serial.println("Web-palvelin käynnistetty!");
  
  Serial.println("Valmis!");
}

// ========== LOOP ==========

void loop() {
  unsigned long currentMillis = millis();
  
  // Mittaus
  if (currentMillis - lastMeasurement >= MEASUREMENT_INTERVAL) {
    lastMeasurement = currentMillis;
    
    readPressure();
    controlPump();
    checkAlarms();
    updateDisplay();
    
    // Tulosta sarjaporttiin
    Serial.print("Paine: ");
    Serial.print(relativePressure, 2);
    Serial.print(" kPa | Pumppu: ");
    Serial.print(pumpState ? "ON" : "OFF");
    Serial.print(" | Hälytys: ");
    Serial.println(alarmState ? "KYLLÄ" : "EI");
  }
  
  // Web-palvelin
  server.handleClient();
  
  delay(10);
}
