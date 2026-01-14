# Lisäominaisuudet – Automaatio ja efektit

---

## 🤖 Automaattinen avaus/sulku

### Perusidea:

**Logiikka:**
1. **Kansi kiinni** → ESP32 tunnistaa (magneettikytkimen tai reedkytkin)
2. **Automaattinen pumppuohjaus:**
   - Pumppu käynnistyy → saavuttaa tavoitepaineen
   - Paine pidetään säädettävällä tasolla
3. **Nappia painetaan** → "AVAA KANSI" (web UI tai fyysinen painike)
   - Pumppu pois päältä
   - Sähköventtiili avautuu → paine tasaantuu (3-5s)
   - **Lineaaritoimilaite nostaa kantta automaattisesti**
   - LED-animaatio + ääniefekti
4. **Kansi auki** → Pumppu ei käynnisty, valo valkoinen

**TÄRKEÄ:** Alipaine (~30 kPa = 300 N/m²) pitää kannen lukkiutuneena ilman erillistä lukkoa!
- Esim. 0.5 m² kansi → ~150 N voima (15 kg) joka pitää kannen kiinni
- Lineaaritoimilaitteen täytyy olla riittävän vahva TAI paine vapautetaan ensin

---

### Toteutus

#### ✅ SUOSITELTU RATKAISU: Lineaaritoimilaite + Venttiili

**Komponentit:**
- **Magneettikytkimet (2 kpl)** – kannen tilan tunnistus
  - Yksi kiinni-asennossa, toinen täysin auki-asennossa
  - **Hinta:** 5 € / pari
  - **Toimittajat:** Partco, AliExpress
  
- **Sähköventtiili (12V solenoid valve)** – paineen vapautus
  - Avautuu ennen kannen nostoa
  - **Hinta:** 10–20 €
  - **Toimittajat:** AliExpress, TME.eu
  
- **Lineaaritoimilaite (Linear Actuator)**
  - 12V DC, 50-100 mm isku
  - Voima: 100-300 N (riippuu kannen koosta)
  - PWM-ohjattavissa (nopeus säädettävissä)
  - **Hinta:** 30–80 €
  - **Toimittajat:** AliExpress, eBay
  
- **Motor driver** (L298N tai BTS7960)
  - Ohjaa lineaaritoimilaitetta
  - **Hinta:** 5–15 €

**Asennusesimerkki:**
```
Kansi
  │
  ├── Saranat (toisella puolella)
  │
  └── Lineaaritoimilaite (nostaa/laskee toiselta reunalta)
       - Kiinni: 0 mm
       - Auki: 80 mm (kansi 15-20° ylös)
```

**Toimintalogiikka (ESP32-koodissa):**
```
Kun "AVAA KANSI" painetaan:
  1. Pumppu pois päältä
  2. Avaa sähköventtiili (paine → 0)
  3. Odota 5 sekuntia (paine tasaantuu)
  4. LED-animaatio alkaa (virtaus sisään)
  5. Ääniefekti: "Pssshhh"
  6. Lineaaritoimilaite ulos (kansi nousee)
  7. Odota että magneetti havaitsee "täysin auki"
  8. Valaise sisätila valkoisella
  9. Valmis!

Kun kansi suljetaan manuaalisesti:
  1. Magneetti havaitsee "kiinni"
  2. Lineaaritoimilaite sisään (varmistus)
  3. Sulje sähköventtiili
  4. Käynnistä pumppu automaattisesti
```

---

## 💨 Ilmavirran käyttö efekteihin

### Idea: Ilmavirtaus alipaineen tasaantuessa

Kun kansi avataan ja paine tasaantuu, ilma virtaa sisään (~30 kPa paine-ero → melko voimakas virtaus).

#### Efekti 1: LED-nauha "virtausvaloilla"

**Toteutus:**
- WS2812B LED-nauha kotelon sisäreunassa
- Animaatio kun paine tasaantuu:
  - "Virtausmaisema" sisään virtaavalla suunnalla
  - Väri muuttuu paineen mukaan (punainen → vihreä)

**Koodi:**
```cpp
if (pressure_releasing) {
  // Animoi LEDit virtaussuuntaan
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(map(currentPressure, -30, 0, 0, 96), 255, 255);
    FastLED.show();
    delay(20);
  }
}
```

---

#### Efekti 2: Pieni viuhka + "Fog effect"

**Toteutus:**
- Pieni **sisäänpäin virtaava ilmakanava** jossa:
  - Viuhka (5V PC-tuuletin) saa virtauksen näkyväksi
  - Valinnainen: Kosteutin (ultrasonic mist maker) → "höyryefekti"

**Edut:**
- Todella cooli visuaalinen efekti
- Teknisesti yksinkertainen

**Haitat:**
- Lisää kosteutta (ei välttämättä hyvä filamentille!)
- Suositus: Käytä vain viuhkaa ilman kosteutinta

---

#### Efekti 3: Ääniefekti

**Toteutus:**
- Pieni kaiutin (buzzeri tai 8 Ω kaiutin)
- ESP32 soittaa äänen:
  - "Pssshhhh" (ilmavirtaus)
  - "Beep beep" (kansi vapaa)
  - Sci-fi-tyylinen "depressurization sound"

**Koodi:**
```cpp
// DFPlayer Mini MP3-soitin (2 €)
myDFPlayer.play(1); // "depressurization.mp3"
```

---

## 💡 Valaistus

### Sisävalaistus

**LED-nauha kotelon sisällä:**
- **WS2812B RGB LED-nauha** (5V, addressoitava)
- **Hinta:** 10–20 € / metri
- **Sijoitus:** Kotelon sisäreunoihin tai kannen alle

**Ominaisuudet:**
- Automaattinen sytytys kun kansi auki
- Värikoodi paineen mukaan:
  - 🔴 Punainen: Alipaine kadonnut / vuoto
  - 🟢 Vihreä: OK, tiivis
  - 🔵 Sininen: Pumppu päällä
  - 🟡 Keltainen: Kansi auki, ei painetta

**ESP32-koodi:**
```cpp
#include <FastLED.h>

#define NUM_LEDS 30
#define LED_PIN 13
CRGB leds[NUM_LEDS];

void updateLighting() {
  if (!lidClosed) {
    // Valkoinen valo kun kansi auki
    fill_solid(leds, NUM_LEDS, CRGB::White);
  } else if (alarmState) {
    // Punainen vilkkuu jos vuoto
    fill_solid(leds, NUM_LEDS, (millis() % 1000 < 500) ? CRGB::Red : CRGB::Black);
  } else if (relativePressure < -20) {
    // Vihreä jos hyvä alipaine
    fill_solid(leds, NUM_LEDS, CRGB::Green);
  } else if (pumpState) {
    // Sininen kun pumpataan
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
  }
  FastLED.show();
}
```

---

### Ulkovalaistus / Statusinäyttö

**LED-indikaattorit ulkopuolella:**
- 🟢 OK – Alipaine kunnossa
- 🔴 ALARM – Vuoto havaittu
- 🔵 PUMP – Pumppu päällä

Tai **OLED-näyttö** kannen ulkopuolelle → Paine, tila, lämpötila

---

## 🌡️ Lämpötila- ja kosteusseuranta

### Anturit

**BME280 (SUOSITUS):**
- Mittaa: Paine, lämpötila, kosteus
- **Hinta:** 5–10 €
- **Edut:** Kolme mittausta yhdellä anturilla!
- **Liitäntä:** I2C (sama väylä kuin BMP280)

**DHT22 (vaihtoehto):**
- Mittaa: Lämpötila, kosteus (ei painetta)
- **Hinta:** 3–7 €
- **Edut:** Halpa
- **Haitat:** Hitaampi, ei painetta

---

### Toiminnallisuus

**Seuranta:**
- Loggaa lämpötila ja kosteus
- Näytä web UI:ssa:
  - Nykyinen lämpötila: 22.5 °C
  - Kosteus: 35 % RH
  - Paine: -25 kPa

**Hälytykset:**
- Jos kosteus > 50 % → Hälytys (vuoto tai riittämätön tiiveys)
- Jos lämpötila > 30 °C → Varoitus (liian lämmin)

**Kuvaaja:**
- Paine, lämpötila ja kosteus samassa kuvaajassa (web UI)
- Historian tallennus SPIFFS:iin tai SD-kortille

---

## 🎮 Käyttöliittymä (laajennettu)

### Web UI (laajennettu versio)

**Lisäominaisuudet:**
1. **Kannen tila:**
   - "Kansi kiinni ja lukittu"
   - "Kansi auki"
   - Painike: "Avaa kansi" (vapauttaa paineen ja lukon)

2. **Valaistuksen ohjaus:**
   - Värinvalitsin
   - Kirkkaus
   - Automaattinen / manuaalinen

3. **Efektien valinta:**
   - "Virtausanimaatio" päällä/pois
   - "Ääniefektit" päällä/pois

4. **Historian näyttö:**
   - Paine, lämpötila, kosteus (kuvaaja)
   - Avauskerrat, pumppuaika

5. **Asetukset:**
   - Tavoitepaine (säädettävä)
   - Hälytysrajat
   - Automaattisen avauksen viive

---

## 🛠️ Komponenttiluettelo (lisäosat)

| Komponentti | Hinta | Käyttö |
|-------------|-------|--------|
| Magneettikytkimet (2x) | 5 € | Kannen tilan tunnistus |
| Sähköventtiili 12V | 15 € | Paineen vapautus |
| BME280 (paine+lämpö+kosteus) | 8 € | Ympäristöseuranta |
| WS2812B LED-nauha (1m) | 15 € | Sisävalaistus + efektit |
| DFPlayer Mini MP3 | 2 € | Ääniefektit |
| Servomoottori | 20 € | Automaattinen lukko |
| 5V Tuuletin (40mm) | 5 € | Visuaalinen efekti |
| SD-kortti (8GB) | 5 € | Historian tallennus |
| **YHTEENSÄ** | **~75 €** | Kaikki lisäosat |

---

## 💻 Laajennettu ESP32-koodi (runko)

```cpp
// Lisää kirjastot
#include <FastLED.h>
#include <DFRobotDFPlayerMini.h>

// Pinnit
#define LID_CLOSED_SENSOR 32
#define LID_OPEN_SENSOR 33
#define SOLENOID_VALVE_PIN 14
#define SERVO_PIN 15
#define LED_STRIP_PIN 13
#define NUM_LEDS 30

// Tilat
bool lidClosed = false;
bool autoMode = true;
float targetPressure = -25.0; // Säädettävissä

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(LID_CLOSED_SENSOR, INPUT_PULLUP);
  pinMode(LID_OPEN_SENSOR, INPUT_PULLUP);
  pinMode(SOLENOID_VALVE_PIN, OUTPUT);
  
  FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_LEDS);
  
  // ... loput alustusten
}

void loop() {
  // Lue kannen tila
  lidClosed = digitalRead(LID_CLOSED_SENSOR) == LOW;
  
  if (autoMode) {
    if (lidClosed) {
      // Kansi kiinni → sulje venttiili, pumppu päälle
      digitalWrite(SOLENOID_VALVE_PIN, LOW);
      controlPump(); // Säädä paine tavoitetasolle
    } else {
      // Kansi auki → avaa venttiili, pumppu pois
      digitalWrite(SOLENOID_VALVE_PIN, HIGH);
      pumpState = false;
      digitalWrite(PUMP_RELAY_PIN, LOW);
    }
  }
  
  updateLighting();
  updateDisplay();
  server.handleClient();
}
```

---

## 🎯 Toteutusjärjestys (ehdotus)

1. ✅ **Perusrakenne** (jo tehty!)
2. ⏳ **Tiivistys ja painemittaus** (seuraavana)
3. **Valaistus** → Helppo ja cooli lisä
4. **Lämpötila/kosteus** → Vaihda BMP280 → BME280
5. **Magneettikytkimet** → Automaattinen pumpunohjaus
6. **Sähköventtiili** → Turvallinen avaus
7. **LED-efektit** → Virtausanimaatio
8. **Ääniefektit** (valinnainen)
9. **Automaattinen lukko** (edistynyt, valinnainen)

---

## 🚀 "Ultimate" versio

Jos haluat rakentaa **maksimaalisen** version:

- ✅ Hitsattu teräsrunko + peilaava muovi + polykarbonaatti
- ✅ Automaattinen pumpunohjaus paineen mukaan
- ✅ BME280: Paine + lämpötila + kosteus
- ✅ WS2812B RGB-nauha: Virtausanimaatiot + värikoodit
- ✅ Magneettikytkimet: Kannen tilan tunnistus
- ✅ Sähköventtiili: Turvallinen paineen vapautus
- ✅ Ääniefektit: Sci-fi-depressurisaatio
- ✅ Web UI: Reaaliaikainen seuranta, historia, asetukset
- ✅ SD-kortti: Pitkä historia (kuukausia dataa)
- ⏸️ Valinnainen: Automaattinen lukko + lineaaritoimilaite

**Kokonaiskustannukset:** ~250–300 € (runko + elektroniikka + kaikki lisäosat)
