# ESP32 Paineanturi - Asennusohje

## 📦 Tarvittavat kirjastot

Asenna Arduino IDE:ssä (Tools → Manage Libraries):

1. **Adafruit BMP280 Library** (Adafruit)
2. **Adafruit GFX Library** (Adafruit)
3. **Adafruit SSD1306** (Adafruit)
4. **Adafruit Unified Sensor** (Adafruit)

## 🔌 Kytkennät

### BMP280 → ESP32
```
VCC  → 3.3V
GND  → GND
SCL  → GPIO 22 (I2C SCL)
SDA  → GPIO 21 (I2C SDA)
```

### OLED (128x64 I2C) → ESP32
```
VCC  → 3.3V
GND  → GND
SCL  → GPIO 22 (I2C SCL)
SDA  → GPIO 21 (I2C SDA)
```

### Rele (pumppua varten) → ESP32
```
VCC  → 5V
GND  → GND
IN   → GPIO 25
```

### LED-indikaattorit → ESP32
```
LED OK (vihreä):
  + → GPIO 26 → 220Ω vastus → LED → GND

LED HÄLYTYS (punainen):
  + → GPIO 27 → 220Ω vastus → LED → GND
```

### 12V Pumppu → Rele
```
12V virtalähde + → Rele COM
Rele NO → Pumppu +
Pumppu - → 12V virtalähde -
```

## ⚙️ Asetukset

Muokkaa koodissa:

```cpp
// WiFi-tiedot
const char* ssid = "OMA_WIFI_SSID";
const char* password = "OMA_WIFI_SALASANA";

// Paineen raja-arvot (muuta tarpeen mukaan)
const float PRESSURE_LOW_THRESHOLD = -30.0;   // Pumppu pois
const float PRESSURE_HIGH_THRESHOLD = -15.0;  // Pumppu päälle
const float PRESSURE_ALARM = -5.0;            // Hälytysraja
```

## 🚀 Käyttöönotto

1. **Lataa koodi ESP32:lle** Arduino IDE:llä
2. **Avaa Serial Monitor** (115200 baud)
3. **Tarkista:**
   - BMP280 löytyy ja alustetaan
   - OLED-näyttö toimii
   - WiFi yhdistää
   - IP-osoite näkyy
4. **Avaa selaimessa:** `http://[ESP32_IP_OSOITE]`
5. **Testaa:**
   - Näytön päivitys
   - Paineen lukeminen
   - Pumppuohjaus web UI:sta

## 🌐 Web UI

Käytä selainta osoitteessa, jonka ESP32 tulostaa Serial Monitor:iin.

**Ominaisuudet:**
- Reaaliaikainen paineen näyttö
- Tilan seuranta (OK / VUOTO)
- Manuaalinen pumppuohjaus
- Automaattinen päivitys 2 sekunnin välein

## 🐛 Vianmääritys

**"BMP280-anturia ei löydy"**
- Tarkista kytkennät (SCL, SDA)
- Kokeile osoitetta 0x77 koodissa (vaihda `bmp.begin(0x77)`)

**"OLED-näyttöä ei löydy"**
- Tarkista kytkennät
- Varmista että OLED on I2C-versio (ei SPI)

**"WiFi-yhteys epäonnistui"**
- Tarkista SSID ja salasana
- Varmista että WiFi on 2.4 GHz (ESP32 ei tue 5 GHz)

**Pumppu ei käynnisty**
- Tarkista relekytkentä
- Mittaa jännite GPIO 25:llä (pitäisi olla ~3.3V kun päälle)
- Varmista että 12V virtalähde on kytketty

## 📊 Ominaisuudet

- ✅ Paineen mittaus BMP280:lla
- ✅ OLED-näyttö
- ✅ Web UI WiFi:n yli
- ✅ Automaattinen pumppuohjaus
- ✅ Hälytysjärjestelmä vuodoille
- ✅ LED-indikaattorit
- ✅ Paineen historia (100 mittausta)
- ✅ JSON API

## 🔮 Tulevat parannukset

- [ ] SPIFFS: tallenna historia pysyvästi
- [ ] MQTT: lähetä data kotiautomaatioon
- [ ] OTA: langaton päivitys
- [ ] Graafiset kuvaajat web UI:hin
- [ ] Kosteusmittaus (BME280:lla)
