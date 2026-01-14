# Ääniefektit ja visuaaliset efektit - Dokumentaatio

**Lisätty ESP32-koodiin:** Versio 2.1

---

## 🎵 Ääniefektit (Passive Buzzer)

### Komponentti:
- **Passive Buzzer** (ei aktiivinen)
- **Pinni:** GPIO 12 (BUZZER_PIN)
- **Hinta:** ~€1-2
- **Toimittaja:** AliExpress, Partco

---

### Toteutetut äänet:

#### 1. Vakuumin vapautuminen "Pssshhhhh" 💨
```cpp
void playVacuumReleaseSound() {
  // Simuloi ilman virtausta laskevalla taajuudella
  for (int freq = 2000; freq > 400; freq -= 50) {
    tone(BUZZER_PIN, freq, 30);
    delay(35);
  }
  noTone(BUZZER_PIN);
}
```

**Käyttö:** Automaattisesti kun venttiili avautuu  
**Kesto:** ~1.1 sekuntia  
**Efekti:** Korkeasta taajuudesta (2000 Hz) alas (400 Hz) = ilman virtauksen ääni

---

#### 2. Kannen avautuminen "Beep-beep" 🔔
```cpp
void playLidOpenSound() {
  tone(BUZZER_PIN, 1200, 150);
  delay(200);
  tone(BUZZER_PIN, 1500, 150);
  delay(200);
  noTone(BUZZER_PIN);
}
```

**Käyttö:** Kun kansi alkaa nousta  
**Kesto:** 400ms  
**Efekti:** Kaksi nousevaa piippaus (1200 Hz → 1500 Hz)

---

#### 3. Hälytys (jo olemassa koodissa)
```cpp
// Hälytysääni (esim. vuoto tai korkea kosteus)
tone(BUZZER_PIN, 800, 500);  // Matala, varoittava ääni
```

---

## 🌈 LED-animaatiot (WS2812B RGB-nauha)

### Komponentti:
- **WS2812B LED-nauha** (30 LEDiä)
- **Pinni:** GPIO 13 (LED_STRIP_PIN)
- **Kirjasto:** FastLED

---

### Toteutetut animaatiot:

#### 1. Flow-animaatio 🌊 (Ilman virtaus sisään)
```cpp
void flowAnimation(int duration_ms) {
  unsigned long startTime = millis();
  int position = 0;
  
  while (millis() - startTime < duration_ms) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    
    // "Virtaavan ilman" efekti: sinisestä -> valkoiseksi
    for (int i = 0; i < 5; i++) {
      int ledIndex = (position + i) % NUM_LEDS;
      if (i == 0) leds[ledIndex] = CRGB::White;
      else if (i == 1) leds[ledIndex] = CRGB(150, 150, 255);
      else if (i == 2) leds[ledIndex] = CRGB(100, 100, 200);
      else leds[ledIndex] = CRGB(50, 50, 150);
    }
    
    FastLED.show();
    delay(50);
    position++;
  }
}
```

**Käyttö:** Vakuumin vapautuksen aikana (4 sekuntia)  
**Efekti:** "Aallot" kulkevat LED-nauhassa simuloiden ilman virtausta  
**Värit:** Sininen → Valkoinen (ilman väri)

---

#### 2. Sateenkaari-animaatio 🌈 (Kansi nousee)
```cpp
void rainbowAnimation(int duration_ms) {
  unsigned long startTime = millis();
  uint8_t hue = 0;
  
  while (millis() - startTime < duration_ms) {
    fill_rainbow(leds, NUM_LEDS, hue, 7);
    FastLED.show();
    delay(20);
    hue += 2;
  }
}
```

**Käyttö:** Kun lineaaritoimilaite nostaa kantta  
**Kesto:** ~8 sekuntia (kannen nousun ajan)  
**Efekti:** Pyörivä sateenkaari, "happy mode" 🎉

---

#### 3. Tilavärit (jatkuva)
```cpp
void updateLEDs() {
  if (alarmState) {
    // Hälytys: Punainen vilkkuu (500ms interval)
    fill_solid(leds, NUM_LEDS, ledOn ? CRGB::Red : CRGB::Black);
  } else if (lidState == OPEN) {
    // Kansi auki: Valkoinen (kirkas valo sisään)
    fill_solid(leds, NUM_LEDS, CRGB::White);
  } else if (pumpState) {
    // Pumppaus käynnissä: Sininen
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
  } else if (relativePressure < (PRESSURE_TARGET + 5)) {
    // Hyvä alipaine: Vihreä (kaikki OK)
    fill_solid(leds, NUM_LEDS, CRGB::Green);
  } else {
    // Normaali/odotus: Keltainen
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);
  }
  FastLED.show();
}
```

**Tila-indikaattorit:**
| Tila | Väri | Kuvaus |
|------|------|---------|
| Hälytys (vuoto/kosteus) | 🔴 Punainen vilkkuu | Vaatii huomiota |
| Kansi auki | ⚪ Valkoinen | Työvalo filamenteille |
| Pumppaus käynnissä | 🔵 Sininen | Akaavumia luodaan |
| Hyvä alipaine | 🟢 Vihreä | Kaikki OK, tiivis |
| Normaali | 🟡 Keltainen | Odotustila |

---

## 🎬 Täydellinen sekvenssi: Kannen avaus

```
USER: Painaa "AVAA KANSI" -nappia Web UI:ssa

1. PUMPPU PYSÄHTYY
   └─ Serial: "🛑 Pumppu pysäytetty"

2. VENTTIILI AVAUTUU
   ├─ Serial: "💨 Venttiili auki - paine tasaantuu..."
   └─ GPIO: SOLENOID_VALVE_PIN = HIGH

3. ÄÄNI: "Pssshhhhh" (1.1s)
   └─ playVacuumReleaseSound()
   └─ Taajuus: 2000 Hz → 400 Hz (laskeva)

4. LED: Flow-animaatio (4s)
   ├─ Serial: "🌊 Flow-animaatio käynnistyy..."
   └─ Siniset "aallot" kulkevat nauhassa

5. ODOTUS: Paineen tasaantuminen
   ├─ Serial: "⏳ Varmistetaan paineen tasaantuminen..."
   ├─ Luetaan BME280 (tarkistetaan paine > -2 kPa)
   └─ Max 1 sekunti lisäaika

6. VENTTIILI SULKEUTUU
   └─ Serial: "🔒 Venttiili suljettu"

7. ÄÄNI: "Beep-beep" (400ms)
   └─ playLidOpenSound()
   └─ 1200 Hz → 1500 Hz

8. KANSI NOUSEE + LED-sateenkaari (8s)
   ├─ Serial: "🌈 Avataan kantta..."
   ├─ Servo/Lineaaritoimilaite: 0° → 180°
   └─ Sateenkaari pyörii koko nousun ajan

9. VALMIS
   ├─ Serial: "✅ KANSI AUKI - Filamentit saatavilla!"
   ├─ LED: Valkoinen (työvalo)
   └─ Tila: OPEN

KOKONAISKESTO: ~15-20 sekuntia
```

---

## 🛠️ Räätälöinti

### Muuta ääniefektien taajuuksia:

```cpp
// Vakuumin vapautus - nopeampi:
for (int freq = 2500; freq > 300; freq -= 80) {  // Alkup: 2000 → 400, step 50

// Kannen avaus - korkeampi:
tone(BUZZER_PIN, 1500, 150);  // Alkup: 1200
delay(200);
tone(BUZZER_PIN, 1800, 150);  // Alkup: 1500
```

---

### Muuta LED-animaatioiden nopeutta:

```cpp
// Flow-animaatio - hitaampi:
delay(80);  // Alkup: 50ms → hitaampi virtaus

// Sateenkaari - nopeampi:
hue += 5;  // Alkup: 2 → nopeampi pyöriminen
```

---

### Lisää oma animaatio:

```cpp
void pulseAnimation() {
  for (int brightness = 0; brightness < 255; brightness += 5) {
    fill_solid(leds, NUM_LEDS, CRGB(0, brightness, 0));  // Vihreä pulssi
    FastLED.show();
    delay(10);
  }
  for (int brightness = 255; brightness > 0; brightness -= 5) {
    fill_solid(leds, NUM_LEDS, CRGB(0, brightness, 0));
    FastLED.show();
    delay(10);
  }
}
```

---

## 💡 Vaihtoehtoiset toteutukset

### Vaihtoehto A: DFPlayer Mini (MP3-tiedostot)

Jos haluat "oikean" vakuumiäänen (ei buzzeria):

**Komponentti:** DFPlayer Mini + SD-kortti + kaiutin  
**Hinta:** ~€3 + €2 (kaiutin)  
**Edut:**
- Todellinen "pssshhh"-ääni (nauhoitettu)
- Voit lisätä puheääniä: "Kansi avataan..."
- Parempi laatu kuin passive buzzer

**Kirjasto:** `DFRobotDFPlayerMini.h`

```cpp
#include <DFRobotDFPlayerMini.h>

DFPlayerMini_UART myDFPlayer(Serial2);  // RX=16, TX=17

void setup() {
  myDFPlayer.begin(9600);
  myDFPlayer.volume(20);  // 0-30
}

void playVacuumRelease() {
  myDFPlayer.play(1);  // Toista "001.mp3" SD-kortilta
}
```

**SD-kortin sisältö:**
- `001.mp3` - Vakuumin vapautus (esim. https://freesound.org/)
- `002.mp3` - "Kansi avataan"
- `003.mp3` - "Kansi auki"
- `004.mp3` - Hälytysääni

---

### Vaihtoehto B: Ei ääniä (silent mode)

Jos haluat hiljaisen toiminnan:

```cpp
// Kommentoi pois tai lisää asetus:
bool silentMode = true;

void playVacuumReleaseSound() {
  if (silentMode) return;  // Ei ääniä
  // ... buzzer-koodi
}
```

Asetus voidaan lisätä Web UI:hin:
```html
<input type="checkbox" id="silent" onchange="fetch('/settings/silent?value='+this.checked)">
<label>Hiljainen tila</label>
```

---

## 📊 Resurssit

**Buzzerin kulutus:** ~20 mA @ 5V  
**LED-nauhan kulutus:** ~1.8A @ 5V (kaikki LEDit valkoisena täydellä kirkkauden)  
**Suositus:** Käytä 2-3A virtalähdettä

**Buzzerin äänikirjasto:** ESP32 `tone()` funktio  
**LED-kirjasto:** FastLED (v3.5+)

---

## 🎯 Testausjärjestys

1. ✅ Testaa buzzeri erikseen: `tone(BUZZER_PIN, 1000, 1000);`
2. ✅ Testaa LED-nauha: `fill_solid(leds, NUM_LEDS, CRGB::Red); FastLED.show();`
3. ✅ Testaa vakuumiääni: `playVacuumReleaseSound();`
4. ✅ Testaa flow-animaatio: `flowAnimation(4000);`
5. ✅ Testaa sateenkaari: `rainbowAnimation(5000);`
6. ✅ Testaa koko sekvenssi: Paina "AVAA KANSI"

---

**Cool factor: 🌟🌟🌟🌟🌟**  
Filamenttikotelo joka näyttää ja kuulostaa sci-fi-laitteelta! 🚀
