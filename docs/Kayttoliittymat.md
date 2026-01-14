# Käyttöliittymät - Manuaalinen ja Web-pohjainen

**Päivitetty:** 14.1.2026  
**Arkkitehtuuri:** ESP32 (I/O-ohjaus) + Erillinen palvelin (Web UI)

---

## 🎛️ Arkkitehtuurin yleiskuvaus

```
┌─────────────────────────────────────────────────────┐
│                FILAMENTTIKOTELO                     │
│  ┌──────────────────────────────────────────────┐  │
│  │  ESP32 (I/O-ohjain)                          │  │
│  │  - BME280 sensori                            │  │
│  │  - Moottorit/pumput                          │  │
│  │  - LED-nauha                                 │  │
│  │  - OLED-näyttö + potentiometri + painikkeet │  │
│  │  - MQTT/HTTP client                          │  │
│  └────────┬─────────────────────────────────────┘  │
│           │ WiFi (ympäristön WLAN)                 │
└───────────┼────────────────────────────────────────┘
            │
            │ MQTT/HTTP
            ▼
┌───────────────────────────────────────┐
│  PALVELIN (Tietokone/Raspberry Pi)   │
│  ┌─────────────────────────────────┐ │
│  │  Python/Node.js palvelin        │ │
│  │  - Web UI (React/Vue/HTML)      │ │
│  │  - MQTT broker / HTTP API       │ │
│  │  - Historia-tietokanta          │ │
│  │  - Grafiikka (Plotly/Chart.js)  │ │
│  └─────────────────────────────────┘ │
│                                       │
│  Käytettävissä kaikissa laitteissa:  │
│  📱 Puhelin, 💻 Tietokone, 📱 Tabletti│
└───────────────────────────────────────┘
```

**Edut:**
- ✅ ESP32 kevyt (vain I/O ja kommunikaatio)
- ✅ Raskas UI tietokoneella/Raspberry Pi:llä
- ✅ Historia-tietokanta palvelimella
- ✅ Modernit web-työkalut (React, grafiikka)
- ✅ Ei ESP32:n muistirajoituksia
- ✅ Useammat käyttäjät samanaikaisesti

---

## 🖥️ Manuaalinen käyttöliittymä (ESP32 + OLED)

### Komponentit

| Komponentti | Määrä | Hinta | Pinni | Huom |
|------------|-------|-------|-------|------|
| OLED 128x64 (SSD1306) | 1 kpl | €5 | I2C (21, 22) | Näyttö |
| Potentiometri 10kΩ | 1 kpl | €1 | GPIO 34 (ADC) | Säätö |
| Mikrokytkin (tact switch) | 4 kpl | €2 | GPIO 25, 26, 27, 33 | Valikko |
| 3D-tulostettu kotelo | 1 kpl | - | - | **Irrallinen paneeli** |
| Kaapeli 6-johtiminen | 50-100cm | €2 | - | Yhteys ESP32:een |
| M12 läpivientinippa | 1 kpl | €3 | - | Tiivis läpivienti takaseinästä |

**Yhteensä:** ~€13

**Huom:** UI-paneeli on **täysin irrallinen laite** - ei kiinni kotelon seinässä!

---

### Kytkentä (Irrallinen paneeli)

```
┌─────────────────────────────────────────────────────────┐
│  FILAMENTTIKOTELO (sisällä ESP32)                       │
│                                                          │
│   ESP32                                                 │
│   GPIO 21 (SDA)  ┐                                      │
│   GPIO 22 (SCL)  │                                      │
│   3.3V           ├─→ Kaapeli (6 johdinta) ──┐          │
│   GND            │                           │          │
│   GPIO 34 (ADC)  │                           │          │
│   GPIO 25-33     ┘                           │          │
│                                               │          │
└───────────────────────────────────────────────┼──────────┘
                                                │
                                          M12 läpivienti
                                         (tiivis, takaseinä)
                                                │
                                                │ 50-100cm kaapeli
                                                │
                                                ▼
        ┌───────────────────────────────────────────┐
        │  UI-PANEELI (irrallinen)                  │
        │  ┌─────────────────────┐                 │
        │  │   OLED 128x64       │                 │
        │  │                     │                 │
        │  │  Paine: -25.3 kPa   │                 │
        │  │  Lämpö:  22.5 °C    │                 │
        │  └─────────────────────┘                 │
        │                                           │
        │  [YLÖS] [ALAS] [MENU] [BACK]             │
        │                                           │
        │  Potentiometri: ◄═══●═══►                │
        │                                           │
        │  Seinäkiinnike tai jalusta                │
        └───────────────────────────────────────────┘
```

**Kaapelin johtimet:**
1. SDA (I2C data) - OLED:lle
2. SCL (I2C clock) - OLED:lle
3. 3.3V (VCC) - OLED + potentiometri
4. GND (Ground) - Yhteinen maa
5. ADC (GPIO 34) - Potentiometrin keskijalka
6. BUTTONS (GPIO 25) - Painikkeet yhteiseen pull-down -järjestelmään

**Läpivienti takaseinästä:**
- **M12 läpivientinippa** (IP67-luokka, vesitiivisyy) ~€3
- **Tiivistysrengas** (NBR tai silikoni)
- **Kaapelityyppi:** 6×0.25mm² joustava, suojattu (esim. ystokaapeli)
- **Pituus:** 50-100 cm (riittää että paneeli on käden ulottuvilla)
- **Liitin (valinnainen):** JST-XH 6-pin tai vastaava (helppo irrottaa)

**Asennusvaihtoehdot:**
1. **Seinälle:** 3D-tulostettu seinäkiinnike (2× M4 ruuvi)
2. **Pöydälle:** Tulostettu jalusta (kallistettava)
3. **Magneettikiinnitys:** Magneetti taakse → kiinni metallirunkoon
4. **Ripustettava:** Silmukka taakse → ripustetaan koukusta

---

### Käyttöliittymän rakenne

**Päävalikko:**
```
┌────────────────────┐
│  FILAMENTIT v2.1   │
│──────────────────────
│ Paine:  -25.3 kPa  │
│ Lämpö:   22.5 °C   │
│ Kost:    35 %      │
│ Kansi:   KIINNI    │
│                    │
│ [VALIKKO]          │
└────────────────────┘
```

**Valikkorakenne:**
```
PÄÄVALIKKO
├─ 1. Kannen ohjaus
│  ├─ Avaa kansi
│  └─ Sulje kansi
│
├─ 2. Pumpun ohjaus
│  ├─ Pumppu ON/OFF
│  ├─ Automaatti ON/OFF
│  └─ Tavoitepaine: [pot] -10 ... -40 kPa
│
├─ 3. Asetukset
│  ├─ LED kirkkaus: [pot] 0-255
│  ├─ Ääniefektit: ON/OFF
│  └─ WiFi: Yhdistä/Katkaise
│
├─ 4. Historia
│  ├─ Min paine (24h)
│  ├─ Max kosteus (24h)
│  └─ Toiminta-aika
│
└─ 5. Info
   ├─ IP-osoite
   ├─ WiFi-signaali
   └─ Versio
```

---

### Painikkeiden toiminnot

**Päänäkymässä:**
- **YLÖS/OK**: Avaa valikko
- **ALAS**: (ei toimintoa)
- **VALIKKO**: Pikakomennot (pumppu ON/OFF)
- **TAKAISIN**: Näytä historiagraafi

**Valikossa:**
- **YLÖS/OK**: Valitse/Hyväksy
- **ALAS**: Seuraava vaihtoehto
- **VALIKKO**: (ei toimintoa)
- **TAKAISIN**: Palaa takaisin

**Potentiometri:**
- Päänäkymässä: Vieritä historiaa
- Valikossa "Tavoitepaine": Säädä arvoa reaaliajassa
- Valikossa "LED kirkkaus": Säädä kirkkautta

---

### ESP32-koodi (manuaalinen UI)

```cpp
#include <Adafruit_SSD1306.h>

// Painikkeet
const int BTN_UP = 25;
const int BTN_DOWN = 26;
const int BTN_MENU = 27;
const int BTN_BACK = 33;
const int POT_PIN = 34;

// Valikkorakenne
enum MenuState {
  MENU_MAIN,
  MENU_LID_CONTROL,
  MENU_PUMP_CONTROL,
  MENU_SETTINGS,
  MENU_HISTORY,
  MENU_INFO
};

MenuState currentMenu = MENU_MAIN;
int menuSelection = 0;

// Päänäkymä
void displayMain() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, 0);
  display.println("FILAMENTIT v2.1");
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
  
  display.setCursor(0, 15);
  display.print("Paine:  ");
  display.print(relativePressure, 1);
  display.println(" kPa");
  
  display.print("Lampo:  ");
  display.print(temperature, 1);
  display.println(" C");
  
  display.print("Kost:   ");
  display.print(humidity, 0);
  display.println(" %");
  
  display.print("Kansi:  ");
  display.println(lidState == OPEN ? "AUKI" : "KIINNI");
  
  // Pieni ikoni alhaalla
  display.setCursor(0, 56);
  display.print(pumpState ? "PUMP:ON" : "PUMP:OFF");
  
  display.display();
}

// Valikko: Kannen ohjaus
void displayLidMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("KANNEN OHJAUS");
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
  
  display.setCursor(0, 20);
  if (menuSelection == 0) display.print("> ");
  display.println("Avaa kansi");
  
  display.setCursor(0, 35);
  if (menuSelection == 1) display.print("> ");
  display.println("Sulje kansi");
  
  display.display();
}

// Valikko: Pumpun ohjaus
void displayPumpMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("PUMPUN OHJAUS");
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
  
  display.setCursor(0, 20);
  if (menuSelection == 0) display.print("> ");
  display.print("Pumppu: ");
  display.println(pumpState ? "ON" : "OFF");
  
  display.setCursor(0, 35);
  if (menuSelection == 1) display.print("> ");
  display.print("Auto: ");
  display.println(autoMode ? "ON" : "OFF");
  
  display.setCursor(0, 50);
  if (menuSelection == 2) display.print("> ");
  
  // Jos menuSelection == 2, lue potentiometri
  if (menuSelection == 2) {
    int potValue = analogRead(POT_PIN);
    float targetPressure = map(potValue, 0, 4095, -40, -10); // -40 kPa ... -10 kPa
    display.print("Tavoite: ");
    display.print(targetPressure, 0);
    display.println(" kPa");
  } else {
    display.print("Tavoite: ");
    display.print(PRESSURE_TARGET, 0);
    display.println(" kPa");
  }
  
  display.display();
}

// Painikkeiden lukeminen (debounce)
bool readButton(int pin) {
  static unsigned long lastPress[4] = {0, 0, 0, 0};
  static int pinIndex = 0;
  
  if (pin == BTN_UP) pinIndex = 0;
  else if (pin == BTN_DOWN) pinIndex = 1;
  else if (pin == BTN_MENU) pinIndex = 2;
  else if (pin == BTN_BACK) pinIndex = 3;
  
  if (digitalRead(pin) == LOW) {
    if (millis() - lastPress[pinIndex] > 200) {
      lastPress[pinIndex] = millis();
      return true;
    }
  }
  return false;
}

// Päivitä käyttöliittymä
void updateManualUI() {
  // Lue painikkeet
  if (readButton(BTN_UP)) {
    if (currentMenu == MENU_MAIN) {
      currentMenu = MENU_LID_CONTROL;
      menuSelection = 0;
    } else if (currentMenu == MENU_LID_CONTROL) {
      if (menuSelection == 0) {
        openLid();
      } else if (menuSelection == 1) {
        closeLid();
      }
    } else if (currentMenu == MENU_PUMP_CONTROL) {
      if (menuSelection == 0) {
        pumpState = !pumpState;
        digitalWrite(PUMP_RELAY_PIN, pumpState);
      } else if (menuSelection == 1) {
        autoMode = !autoMode;
      } else if (menuSelection == 2) {
        // Tallenna potentiometrin arvo
        int potValue = analogRead(POT_PIN);
        PRESSURE_TARGET = map(potValue, 0, 4095, -40, -10);
      }
    }
  }
  
  if (readButton(BTN_DOWN)) {
    if (currentMenu != MENU_MAIN) {
      menuSelection++;
      if (currentMenu == MENU_LID_CONTROL && menuSelection > 1) menuSelection = 0;
      if (currentMenu == MENU_PUMP_CONTROL && menuSelection > 2) menuSelection = 0;
    }
  }
  
  if (readButton(BTN_MENU)) {
    // Pika-toggle pumpulle päänäkymästä
    if (currentMenu == MENU_MAIN) {
      pumpState = !pumpState;
      digitalWrite(PUMP_RELAY_PIN, pumpState);
    }
  }
  
  if (readButton(BTN_BACK)) {
    if (currentMenu != MENU_MAIN) {
      currentMenu = MENU_MAIN;
      menuSelection = 0;
    }
  }
  
  // Näytä oikea valikko
  switch (currentMenu) {
    case MENU_MAIN:
      displayMain();
      break;
    case MENU_LID_CONTROL:
      displayLidMenu();
      break;
    case MENU_PUMP_CONTROL:
      displayPumpMenu();
      break;
    default:
      displayMain();
  }
}
```

---

## 🌐 Web-käyttöliittymä (Erillinen palvelin)

### Arkkitehtuuri: MQTT-pohjainen

**Miksi MQTT?**
- ✅ Kevyt protokolla (säästää ESP32:n resursseja)
- ✅ Pub/Sub-malli (ESP32 julkaisee dataa, palvelin kuuntelee)
- ✅ Toimii WiFi:n yli
- ✅ Erittäin luotettava
- ✅ Valmis Home Assistant -integraatio

---

### Komponentit

| Osa | Tekniikka | Sijainti | Rooli |
|-----|-----------|----------|-------|
| **MQTT Broker** | Mosquitto | Tietokone/RPi | Viestien välitys |
| **Backend** | Python FastAPI/Flask | Tietokone/RPi | REST API + WebSocket |
| **Frontend** | React/Vue/HTML+JS | Selain | Käyttöliittymä |
| **Tietokanta** | SQLite/InfluxDB | Tietokone/RPi | Historia |
| **ESP32** | Arduino C++ | Filamenttikotelo | Sensori + I/O |

---

### MQTT-topicsit

```
filament/status          → ESP32 julkaisee tilaa (JSON)
filament/sensor/pressure → Paineen mittaus (kPa)
filament/sensor/temperature → Lämpötila (°C)
filament/sensor/humidity → Kosteus (%)
filament/pump/state      → Pumpun tila (ON/OFF)
filament/lid/state       → Kannen tila (OPEN/CLOSED)

filament/command/pump    ← Palvelin lähettää komennon
filament/command/lid     ← Kannen avaus/sulku
filament/command/target  ← Tavoitepaineen asetus
```

---

### ESP32-koodi (MQTT client)

```cpp
#include <WiFi.h>
#include <PubSubClient.h>

// MQTT-asetukset
const char* mqtt_server = "192.168.1.100";  // Palvelimen IP
const int mqtt_port = 1883;
const char* mqtt_user = "filament";
const char* mqtt_pass = "salasana";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Yhdistä MQTT-brokeriin
void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Yhdistetään MQTT:hen...");
    
    if (mqttClient.connect("FilamentBox", mqtt_user, mqtt_pass)) {
      Serial.println(" OK!");
      
      // Tilaa komento-topicit
      mqttClient.subscribe("filament/command/pump");
      mqttClient.subscribe("filament/command/lid");
      mqttClient.subscribe("filament/command/target");
    } else {
      Serial.print(" VIRHE: ");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}

// Vastaanota MQTT-viestejä
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("MQTT: ");
  Serial.print(topic);
  Serial.print(" = ");
  Serial.println(message);
  
  // Käsittele komennot
  if (String(topic) == "filament/command/pump") {
    if (message == "ON") {
      pumpState = true;
      digitalWrite(PUMP_RELAY_PIN, HIGH);
    } else {
      pumpState = false;
      digitalWrite(PUMP_RELAY_PIN, LOW);
    }
  }
  
  if (String(topic) == "filament/command/lid") {
    if (message == "OPEN") {
      openLid();
    } else if (message == "CLOSE") {
      closeLid();
    }
  }
  
  if (String(topic) == "filament/command/target") {
    PRESSURE_TARGET = message.toFloat();
    Serial.print("Uusi tavoitepaine: ");
    Serial.println(PRESSURE_TARGET);
  }
}

void setup() {
  // ... (muu setup-koodi)
  
  // MQTT
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(mqttCallback);
  connectMQTT();
}

void loop() {
  // ... (muu loop-koodi)
  
  // MQTT
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.loop();
  
  // Julkaise sensoridata 1s välein
  static unsigned long lastPublish = 0;
  if (millis() - lastPublish > 1000) {
    publishStatus();
    lastPublish = millis();
  }
}

// Julkaise tila MQTT:hen
void publishStatus() {
  char buffer[200];
  
  // JSON-muotoinen status
  snprintf(buffer, sizeof(buffer),
    "{\"pressure\":%.2f,\"temperature\":%.1f,\"humidity\":%.0f,\"pump\":\"%s\",\"lid\":\"%s\",\"alarm\":%s}",
    relativePressure, temperature, humidity,
    pumpState ? "ON" : "OFF",
    lidState == OPEN ? "OPEN" : "CLOSED",
    alarmState ? "true" : "false"
  );
  
  mqttClient.publish("filament/status", buffer);
  
  // Erillisiä topicseja (jos halutaan Home Assistant -integraatio)
  mqttClient.publish("filament/sensor/pressure", String(relativePressure, 2).c_str());
  mqttClient.publish("filament/sensor/temperature", String(temperature, 1).c_str());
  mqttClient.publish("filament/sensor/humidity", String(humidity, 0).c_str());
}
```

---

### Palvelin: Python FastAPI + MQTT

**Asenna palvelimelle:**
```bash
# Raspberry Pi tai Linux-tietokone
sudo apt install mosquitto mosquitto-clients
pip install fastapi uvicorn paho-mqtt sqlalchemy

# Tai Docker:
docker-compose up -d
```

**`server.py`:**
```python
from fastapi import FastAPI, WebSocket
from fastapi.staticfiles import StaticFiles
from fastapi.responses import HTMLResponse
import paho.mqtt.client as mqtt
import json
from datetime import datetime
import sqlite3

app = FastAPI()

# SQLite-tietokanta historiaa varten
conn = sqlite3.connect('filament_history.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''
    CREATE TABLE IF NOT EXISTS measurements (
        timestamp DATETIME,
        pressure REAL,
        temperature REAL,
        humidity REAL
    )
''')
conn.commit()

# MQTT-client
mqtt_client = mqtt.Client()
current_status = {}

def on_mqtt_message(client, userdata, message):
    global current_status
    
    topic = message.topic
    payload = message.payload.decode()
    
    if topic == "filament/status":
        current_status = json.loads(payload)
        
        # Tallenna tietokantaan
        cursor.execute(
            "INSERT INTO measurements VALUES (?, ?, ?, ?)",
            (datetime.now(), 
             current_status['pressure'],
             current_status['temperature'],
             current_status['humidity'])
        )
        conn.commit()

mqtt_client.on_message = on_mqtt_message
mqtt_client.connect("localhost", 1883)
mqtt_client.subscribe("filament/#")
mqtt_client.loop_start()

# REST API
@app.get("/api/status")
def get_status():
    return current_status

@app.get("/api/history")
def get_history(hours: int = 24):
    cursor.execute(f"""
        SELECT * FROM measurements
        WHERE timestamp > datetime('now', '-{hours} hours')
        ORDER BY timestamp DESC
    """)
    rows = cursor.fetchall()
    return {
        "data": [
            {
                "timestamp": row[0],
                "pressure": row[1],
                "temperature": row[2],
                "humidity": row[3]
            }
            for row in rows
        ]
    }

@app.post("/api/command/pump/{state}")
def control_pump(state: str):
    mqtt_client.publish("filament/command/pump", state.upper())
    return {"status": "ok"}

@app.post("/api/command/lid/{action}")
def control_lid(action: str):
    mqtt_client.publish("filament/command/lid", action.upper())
    return {"status": "ok"}

@app.post("/api/command/target/{pressure}")
def set_target(pressure: float):
    mqtt_client.publish("filament/command/target", str(pressure))
    return {"status": "ok"}

# Tarjoa staattinen frontend
app.mount("/", StaticFiles(directory="frontend", html=True), name="frontend")
```

**Käynnistä:**
```bash
uvicorn server:app --host 0.0.0.0 --port 8000
```

---

### Frontend: HTML + JavaScript (yksinkertainen)

**`frontend/index.html`:**
```html
<!DOCTYPE html>
<html lang="fi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Filamenttikotelo</title>
    <script src="https://cdn.plot.ly/plotly-2.27.0.min.js"></script>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
            background: #1a1a1a;
            color: #fff;
        }
        .card {
            background: #2a2a2a;
            border-radius: 10px;
            padding: 20px;
            margin-bottom: 20px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.3);
        }
        .value {
            font-size: 3em;
            font-weight: bold;
            text-align: center;
        }
        .grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
        }
        button {
            background: #4CAF50;
            color: white;
            border: none;
            padding: 15px 30px;
            font-size: 1.1em;
            border-radius: 5px;
            cursor: pointer;
            margin: 5px;
        }
        button:hover { background: #45a049; }
        button.danger { background: #f44336; }
        button.danger:hover { background: #da190b; }
        #chart { height: 400px; }
    </style>
</head>
<body>
    <h1>🗄️ Filamenttikotelo - Web UI</h1>
    
    <div class="card">
        <h2>Kannen tila</h2>
        <div class="value" id="lid-status">-</div>
        <button onclick="controlLid('OPEN')">🚪 AVAA KANSI</button>
        <button onclick="controlLid('CLOSE')" class="danger">🔒 SULJE KANSI</button>
    </div>
    
    <div class="grid">
        <div class="card">
            <h3>Paine</h3>
            <div class="value" id="pressure">-</div>
        </div>
        <div class="card">
            <h3>Lämpötila</h3>
            <div class="value" id="temperature">-</div>
        </div>
        <div class="card">
            <h3>Kosteus</h3>
            <div class="value" id="humidity">-</div>
        </div>
    </div>
    
    <div class="card">
        <h2>Ohjaus</h2>
        <button onclick="controlPump('ON')">▶️ Pumppu ON</button>
        <button onclick="controlPump('OFF')" class="danger">⏸️ Pumppu OFF</button>
        <br><br>
        <label>Tavoitepaine:</label>
        <input type="range" min="-40" max="-10" value="-25" id="target-slider">
        <span id="target-value">-25</span> kPa
        <button onclick="setTarget()">Aseta</button>
    </div>
    
    <div class="card">
        <h2>Historia (24h)</h2>
        <div id="chart"></div>
    </div>

    <script>
        // Päivitä tila 1s välein
        setInterval(updateStatus, 1000);
        
        async function updateStatus() {
            const response = await fetch('/api/status');
            const data = await response.json();
            
            document.getElementById('pressure').textContent = 
                data.pressure?.toFixed(1) + ' kPa' || '-';
            document.getElementById('temperature').textContent = 
                data.temperature?.toFixed(1) + ' °C' || '-';
            document.getElementById('humidity').textContent = 
                data.humidity?.toFixed(0) + ' %' || '-';
            document.getElementById('lid-status').textContent = 
                data.lid === 'OPEN' ? '🔓 AUKI' : '🔒 KIINNI';
        }
        
        async function controlPump(state) {
            await fetch(`/api/command/pump/${state}`, { method: 'POST' });
        }
        
        async function controlLid(action) {
            await fetch(`/api/command/lid/${action}`, { method: 'POST' });
        }
        
        async function setTarget() {
            const value = document.getElementById('target-slider').value;
            await fetch(`/api/command/target/${value}`, { method: 'POST' });
        }
        
        document.getElementById('target-slider').oninput = function() {
            document.getElementById('target-value').textContent = this.value;
        };
        
        // Lataa historia ja piirrä graafi
        async function loadHistory() {
            const response = await fetch('/api/history?hours=24');
            const data = await response.json();
            
            const timestamps = data.data.map(d => d.timestamp);
            const pressures = data.data.map(d => d.pressure);
            const temperatures = data.data.map(d => d.temperature);
            const humidities = data.data.map(d => d.humidity);
            
            Plotly.newPlot('chart', [
                { x: timestamps, y: pressures, name: 'Paine (kPa)', yaxis: 'y' },
                { x: timestamps, y: temperatures, name: 'Lämpötila (°C)', yaxis: 'y2' },
                { x: timestamps, y: humidities, name: 'Kosteus (%)', yaxis: 'y3' }
            ], {
                title: 'Historian 24h',
                yaxis: { title: 'Paine' },
                yaxis2: { title: 'Lämpötila', overlaying: 'y', side: 'right' },
                yaxis3: { title: 'Kosteus', overlaying: 'y', side: 'right', position: 0.95 }
            });
        }
        
        loadHistory();
        setInterval(loadHistory, 60000);  // Päivitä minuutin välein
    </script>
</body>
</html>
```

**Käytä selaimella:**
```
http://192.168.1.100:8000
```

---

## 🔩 Gearboxien sijoittaminen kotelon ulkopuolelle

### Etu ulkopuolisesta asennuksesta:
- ✅ Ei vie tilaa sisältä
- ✅ Helppo huolto/säätö
- ✅ Vähemmän melua koteloon
- ✅ Lämpö ei pääse sisään

### Haaste: Tiivis läpivienti kierretangolle

---

### Ratkaisu 1: Laakeroidulla läpiviennillä

```
Ulkopuoli (Gearbox)      │   Sisäpuoli (Kotelon paine)
                         │
  Moottor + Vaihteisto   │   M8 Kierretanko
        │                │        │
        └─ Liitoslaikka ═╪════════╡ Läpivienti
                         │        │
                    O-rengas      │
                    (tiiviste)    │
                                  │
                           Pähkinä (kannessa)
```

**Komponentit:**
- **Läpivientinippa M16** (~€5, rautakauppa)
- **O-rengas 12×2mm NBR** (~€1)
- **Laakeripesä sisäpuolella** (3D-tulostettu)
- **608-laakeri** (kierretanko pyörii vapaasti läpiviennissä)

**Asennus:**
1. Poraa M16-reikä kotelon takaseinään
2. Asenna läpivientinippa + O-rengas
3. Kierretanko läpi läpiviennin
4. Laakeripesä sisäpuolelle (3D-tulostettu)
5. Gearbox kiinni ulkopuolelle

**Tiiviys:** O-rengas tiivistää kiertävän tangon ympäriltä. Hyväksyttävä pieni vuoto (pumppu kompensoi).

---

### Ratkaisu 2: Magneettikytkentä (täysin tiivis)

```
Ulkopuoli:                 │   Sisäpuoli:
  Moottori + Vaihteisto    │   M8 Kierretanko
         │                 │         │
    Magneetti (ulompi) ◄───┼───► Magneetti (sisempi)
         │                 │         │
    Pyörii ilman kontaktia │    Pyörii mukana
```

**Komponentit:**
- **Neodyymimagneetti N52** (20×10mm, 2 kpl) (~€10)
- **3D-tulostetut magneettikiinnikkeet**
- **Laakerointi molemmille puolille**

**Edut:**
- ✅ Täysin tiivis (ei läpivientejä)
- ✅ Ei kosketusta = ei kulumista

**Haitat:**
- ⚠️ Kalliimpi
- ⚠️ Momentti rajoittunut (max ~2-3 Nm)
- ⚠️ Voi luistaa kovalla kuormalla

**Suositus:** Kokemuksellisille, jos läpivientiratkaisulla on ongelmia.

---

### Ratkaisu 3: Tiivistysrasva + labyrinth seal

```
    Ulkopuoli              │   Sisäpuoli
                           │
  Gearbox                  │   Kierretanko
     │                     │      │
     └─ Akseli  ═══════════╪══════╡
                ↑          │
            Tiivisteen     │
            sokkelokammio  │
            + rasva        │
```

**Lisää sokkelotiivistys:**
- 3D-tulostettu monisyvennys akselin ympärille
- Täytetään tiivistysrasvalla (esim. silikonirasva)
- Useampi este ilman pääsylle

**Käyttö:** Yhdistettynä O-rengastiivistykseen = erittäin tiivis.

---

## 📦 3D-tulostettavat osat käyttöliittymille

### Manuaalinen UI-paneeli

**Kotelo:**
- OLED-näytön kehys
- 4x painikereikä (12mm halkaisija)
- Potentiometrin reikä
- Kaapeliläpivienti takaosaan
- Kiinnitys ruuveilla takaseinään

**Materiaali:** PLA (riittää)  
**Tulostusaika:** ~3h

---

### Gearbox-kotelot (ulkoasennus)

**Kotelo + kiinnitysjalat:**
- Suljettu kotelo moottorin + vaihteiston ympärille
- Tuuletusreiät (verkolla suojattu)
- Kiinnitysjalat takaseinään (M6-ruuvit)
- Akselin läpivienti laakeroidulla männällä

**Materiaali:** PETG (kestää ympäristöä)  
**Tulostusaika:** ~4h per kotelo

---

### Läpivientikiinnikkeet

**Laakeripesä sisäpuolelle:**
- 608-laakeripesä
- Tiivistys-uritettu O-rengasta varten
- Kiinnitys koteloon M4-ruuveilla

**Materiaali:** PETG  
**Tulostusaika:** ~1.5h per kpl

---

## 🎯 Yhteenveto: Suositellut ratkaisut

| Osa | Suositus | Hinta | Vaikeusaste |
|-----|----------|-------|-------------|
| **Manuaalinen UI** | OLED + 4 painiketta + potentiometri | €9 | ⭐⭐ Keskivaikea |
| **Web-palvelin** | Raspberry Pi 4 + FastAPI + React | €50* | ⭐⭐⭐ Vaativa |
| **Kommunikaatio** | MQTT (Mosquitto) | €0 | ⭐⭐ Keskivaikea |
| **Gearbox-sijainti** | Ulkopuolella + O-rengastiivistys | €10 | ⭐⭐ Keskivaikea |

*Jos sinulla on jo tietokone/RPi, ei lisäkustannuksia!

---

**Dokumentit päivitetty! 🚀**  
Täysi käyttöliittymä manuaalisella ohjauksella ja modernilla web-UI:lla!
