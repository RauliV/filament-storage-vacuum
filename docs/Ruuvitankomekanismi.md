# Ruuvitankomekanismi - Kannen automaattinen avaus

**Päivitetty:** 14.1.2026  
**Status:** Suunnittelu  
**Tyyppi:** Kaksipuolinen DC-moottoripohjainen nosto

---

## 📐 Yleiskuvaus

Kansi nostetaan symmetrisesti kahdella DC-moottorilla, jotka pyörittävät kierretankoja (M8 tai M6). Kanteen kiinnitetyt mutterit (pähkinät) liikkuvat tankojen mukana ylös/alas, nostaen kantta tasaisesti molemmilta puolilta.

**Edut:**
- ✅ Itsejäykistävä - kansi ei putoa sähkökatkon aikana
- ✅ Tarkka asemointi - hidas ja hallittu liike
- ✅ Symmetrinen nosto - ei vääntymistä tai kulmautumista
- ✅ Edullinen - käytetään olemassa olevia DC-moottoreita
- ✅ 3D-tulostettava vaihteisto - optimoitavissa

**Haitat:**
- ⚠️ Hidas (riippuu välityksestä) - arvio 5-10s kannen avaamiseen
- ⚠️ Vaatii synkronoinnin (molemmat moottorit samaan aikaan)

---

## 🔩 Komponentit

### Ostettavat osat (~€25-30)

| Komponentti | Määrä | Hinta | Toimittaja | Huom |
|------------|-------|-------|------------|------|
| M8 kierretanko 300-400mm | 2 kpl | ~€5 | Biltema, K-Rauta | Tai M6 kevyemmälle rakenteelle |
| M8 mutteri (pähkinä) | 2 kpl | ~€1 | " | Kiinnitys kanteen |
| M8 mutteri (kiinnitys) | 2 kpl | ~€1 | " | Tanko kiinni pohjaan |
| 608 kuulalaakeri (8x22x7mm) | 4 kpl | ~€5 | TME.eu, AliExpress | Ylä- ja alapää tangoille |
| L298N moottoriohjain | 1 kpl | ~€3-5 | AliExpress, Partco | Ohjaa 2 moottoria, 3-12V |
| DC-moottorit 3-6V | 2 kpl | **Olemassa** | - | "Yellow DC Gear Motor" tai vastaava |
| M3 ruuvit + mutterit | 20 kpl | ~€2 | Biltema | Kiinnityksiin |
| M4 ruuvit | 8 kpl | ~€2 | " | Raskaampiin kiinnityspisteisiin |

**Yhteensä:** ~€20 + olemassa olevat moottorit

---

## 🖨️ 3D-tulostettavat osat

### 1. Vaihteisto (2 kpl)
**Materiaali:** PETG tai ABS  
**Tulostusaika:** ~3-4h per kpl  
**Infill:** 40-50% (voimansiirto!)

**Osat:**
- Moottorilaippa (kiinnitys moottoriin)
- Hammaspyörät (3-6V moottoreille suositus):
  - 1. vaihde: 10T (moottori) → 40T (akseli) = 4:1
  - 2. vaihde: 15T (akseli) → 60T (kierretanko) = 4:1
  - **Kokonaisvälitys: 16:1** (3-6V moottoreille)
  - Jos sinulla on valmiiksi vaihteistettu moottori (60 rpm), käytä: 10T → 30T = 3:1
- Laakeripesät akseleille (3-5mm akselit)
- Vaihteiston kotelo (suojaa pölyltä)

**Suunnitteluvinkit:**
- Käytä **moduuli 1.0** hammastusta (hyvä kompromissi vahvuus/koko)
- Lisää 0.2mm välyä hammaspyörien väliin
- D-akseli tai heksalaippa kierretangon kytkentään
- OpenSCAD/FreeCAD: Involute gear generator

### 2. Pähkinäkiinnike kanteen (2 kpl)
**Materiaali:** PETG  
**Tulostusaika:** ~1h per kpl  
**Infill:** 50%

**Rakenne:**
```
 ┌────────────┐
 │  M4 reiät  │ ← Kiinnitys kanteen (4x M4 ruuvi)
 └────┬───────┘
      │
 ┌────▼───────┐
 │  Lokero    │ ← M8 mutteri painetaan tähän
 │  mutterille│   (heksasokkelo, ei pääse pyörimään)
 └────────────┘
```

**Tärkeää:**
- Mutterin lokero **tarkkaan M8 mutterin kokoinen** (13mm heksagoni)
- Syvyys: 8-10mm (mutteri ei pääse liikkumaan)
- 4x M4 reiät kiinnitykseen (kannen sisäpuolelle)
- Vahvikkeet kulmiin (estää halkeaminen)

### 3. Ylälaakerikiinnike (2 kpl)
**Materiaali:** PLA/PETG  
**Tulostusaika:** ~1h per kpl  
**Infill:** 30%

**Rakenne:**
- 608-laakeripesä (press-fit, 22mm ulkohalkaisija)
- M8 reikä keskellä (kierretanko läpi)
- Kiinnitys kotelon ylärakenteeseen (4x M3 ruuvi)
- Tanko pyörii vapaasti laakerin ansiosta

### 4. Pohjan moottorikotelo (2 kpl)
**Materiaali:** PETG  
**Tulostusaika:** ~2h per kpl  
**Infill:** 30%

**Rakenne:**
- Tukeva pohja (kiinnitys kotelon pohjaan M4-ruuveilla)
- Integroitu vaihteisto + 608-laakeri alaosaan
- Moottorikiinnike (M3-reiät)
- Johdotusreikä (5mm)
- Kannellinen suojus (estää pöly/filamenttikuitu)

---

## ⚙️ Mekaaninen asennus

### Vaihe 1: Pohjan asennus

1. **Kiinnitä moottorikoteloiden pohjat**
   - Molemmat päädyt kotelon pohjaan
   - M4 ruuvit betonipohjaan/teräsrunkoon
   - Tarkista että etäisyys vastaa kannen leveyttä

2. **Asenna vaihteistot moottoreihin**
   - Paina moottoriakseli vaihteiston 10T-pyörään
   - Kiinnitä moottorit laippoihin (M3 ruuvit)
   - Aseta vaihteisto koteloihin

3. **Asenna kierretangot**
   - Kierretanko läpi vaihteiston viimeisen pyörän (60T)
   - Alalaakeri kotelon pohjaan
   - M8 mutteri tangon alapäähän (lukitsee paikoilleen)
   - Tanko ei nouse/laske, vain pyörii paikallaan

### Vaihe 2: Kannen asennus

4. **Kiinnitä pähkinäkiinnikkeet kanteen**
   - Kannen sisäpuolelle molemmat päädyt
   - M4 ruuvit läpi kannen
   - Paina M8 mutterit lokeroihin

5. **Asenna ylälaakerikiinnikkeet**
   - Kotelon ylärakenteeseen/kattolevyyn
   - 608-laakerit pesiin
   - Kierretangot läpi laakereiden

6. **Testaa liike manuaalisesti**
   - Pyöritä kierretankoja käsin
   - Kannen pitää nousta/laskea sulavasti
   - Ei kiinni jäämistä

### Vaihe 3: Elektroniikka

7. **Kytke moottorit L298N-ohjaimeen**
   - Moottor A → OUT1, OUT2
   - Moottor B → OUT3, OUT4
   - +12V, GND L298N:ään

8. **Kytke L298N ESP32:een**
   ```
   L298N      ESP32
   ─────      ─────
   IN1    →   GPIO 16 (Moottor A suunta)
   IN2    →   GPIO 17 (Moottor A suunta)
   ENA    →   GPIO 18 (Moottor A PWM nopeus)
   IN3    →   GPIO 19 (Moottor B suunta)
   IN4    →   GPIO 21 (Moottor B suunta)
   ENB    →   GPIO 22 (Moottor B PWM nopeus)
   
   12V    →   VIN (ESP32)
   GND    →   GND (yhteinen)
   ```

9. **Testaa moottoreiden synkronointi**
   - Molemmat moottorit samalla nopeudella
   - Jos kansi kallistuu, säädä PWM-arvoja

---

## 💻 ESP32-koodi

### Päivitykset esp32_paineanturi.ino:ssa

**Lisää alkuun:**
```cpp
// ===== DC-MOOTTORIOHJAUS (L298N) =====
// Moottor A (vasen puoli)
const int MOTOR_A_IN1 = 16;
const int MOTOR_A_IN2 = 17;
const int MOTOR_A_EN = 18; // PWM nopeus

// Moottor B (oikea puoli)
const int MOTOR_B_IN3 = 19;
const int MOTOR_B_IN4 = 21;
const int MOTOR_B_EN = 22; // PWM nopeus

// Hall-sensori kannen asemalle (valinnainen)
const int HALL_SENSOR_PIN = 34; // Analoginen sisääntulo

// Moottoriasetukset
const int MOTOR_SPEED = 200; // 0-255 (PWM)
const int OPEN_TIME_MS = 8000; // Aika kannen avaamiseen (8s)
const int CLOSE_TIME_MS = 8000; // Aika kannen sulkemiseen (8s)
```

**Lisää setup():iin:**
```cpp
  // Moottoreiden pinnit
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_A_EN, OUTPUT);
  pinMode(MOTOR_B_IN3, OUTPUT);
  pinMode(MOTOR_B_IN4, OUTPUT);
  pinMode(MOTOR_B_EN, OUTPUT);
  
  // Molemmat moottorit pois päältä
  stopMotors();
```

**Uudet funktiot:**
```cpp
// Pysäytä molemmat moottorit
void stopMotors() {
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, LOW);
  analogWrite(MOTOR_A_EN, 0);
  analogWrite(MOTOR_B_EN, 0);
}

// Avaa kansi (moottorit ylöspäin)
void openLidMotors() {
  Serial.println("🔼 Avataan kansi...");
  
  // Moottorit ylöspäin
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  digitalWrite(MOTOR_B_IN3, HIGH);
  digitalWrite(MOTOR_B_IN4, LOW);
  
  // Aseta nopeus
  analogWrite(MOTOR_A_EN, MOTOR_SPEED);
  analogWrite(MOTOR_B_EN, MOTOR_SPEED); // Voit säätää jos kallistuu
  ~40 sekuntia (3-6V moottorit hitaampia)
  delay(OPEN_TIME_MS); // Pyöritä 8 sekuntia
  
  stopMotors();
  Serial.println("✅ Kansi auki!");
}

// Sulje kansi (moottorit alaspäin)
void closeLidMotors() {
  Serial.println("🔽 Suljetaan kansi...");
  
  // Moottorit alaspäin
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
  
  // Aseta nopeus
  analogWrite(MOTOR_A_EN, MOTOR_SPEED);
  analogWrite(MOTOR_B_EN, MOTOR_SPEED);
  ~40
  delay(CLOSE_TIME_MS); // Pyöritä 8 sekuntia
  
  stopMotors();
  Serial.println("✅ Kansi suljettu!");
}
```

**Päivitä openLid() -funktio:**
```cpp
void openLid() {
  if (lidState == LID_OPEN) {
    Serial.println("⚠️ Kansi jo auki");
    return;
  }
  
  lidState = LID_OPENING;
  Serial.println("🔓 Aloitetaan kannen avaus...");
  
  // 1. Sammuta pumppu
  stopPump();
  delay(500);
  
  // 2. Avaa venttiili → ilma sisään
  digitalWrite(VALVE_PIN, HIGH);
  Serial.println("💨 Venttiili auki - tasataan painetta...");
  delay(5000); // Odota että paine tasautuu
  
  // 3. Sulje venttiili
  digitalWrite(VALVE_PIN, LOW);
  
  // 4. Avaa kansi moottoreilla
  openLidMotors();
  
  // 5. LED: valkoinen (auki)
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
  
  lidState = LID_OPEN;
  Serial.println("✅ Kansi kokonaan auki!");
}
```

---

## 🔧 Kalibrointi ja säätö

### 1. Nopeuden säätö
Jos kansi kallistuu (toinen puoli nousee nopeammin):
```cpp
analogWrite(MOTOR_A_EN, 200); // Vasen
analogWrite(MOTOR_B_EN, 195); // Oikea hieman hitaammin
```

### 2. Ajan säätö (TÄRKEÄ 3-6V moottoreille!)
Mittaa TODELLINEN aika kännykän sekuntikellolla:
```cpp
// Ensimmäinen testi: aseta pitkä aika, pysäytä manuaalisesti
const int OPEN_TIME_MS = 60000; // 1 minuutti testiä varten

// Mittaa stopparilla → esim. 45 sekuntia → aseta:
const int OPEN_TIME_MS = 45000; // 45 sekuntia
```

**3-6V moottorit ovat HUOMATTAVASTI hitaampia** kuin 12V!

### 3. Hall-sensorin käyttö (valinnainen)
Jos haluat tarkemman asemoinnin, lisää Hall-sensori:
```cpp
// Lue asema
int position = analogRead(HALL_SENSOR_PIN);
if (position > 3000) { // Kansi ylhäällä
  stopMotors();
}
```

---
 (3-6V DC-moottorit)

### Moottorin tyyppi vaikuttaa:

#### A) Jos sinulla on **valmiiksi vaihteistettu moottori** (60-100 rpm @ 6V):
- M8 kierretanko: nousu **1.25mm/kierros**
- Lisävaihteisto 3:1
- Kannen nostokorkeus: **100mm**
- Tarvittavat kierrokset: 100 / 1.25 = **80 kierrosta tankoa**
- Moottorin kierrokset: 80 × 3 = **240 kierrosta**
- **Aika:** 240 / 60 rpm = **4 minuuttia** ✅ SOPIVA
- **Voima:** 60 rpm moottori + 3:1 = riittävä nostoon

#### B) Jos sinulla on **nopea moottori ilman vaihteistoa** (3000+ rpm @ 6V):
- Tarvitsee **16:1 vaihteiston** (tulostettava)
- Moottorin nopeus kuorman alla: ~2000 rpm @ 6V
- Vaihteiston jälkeen: 2000 / 16 = **125 rpm tankoa**
- Kannen nostokorkeus: **100mm**
- Tarvittavat kier (3-6V moottorit)

**Pieni 3-6V DC-moottori:**
- Vääntömomentti: ~0.5-1.0 Nm (vaihteistettu malli)
- Tai: ~0.01 Nm (nopea malli ilman vaihteistoa)

**M8 kierretanko:**
- Nousu: 1.25mm/kierros
- Mekaaninen etu: η = 1.25mm / (2π × 4mm) = 0.05 (5% hyötysuhde on huono, mutta turvallinen arvio)
- Teoreettinen nostovoima per tanko: T × (2π / nousu) = 1.0 Nm × (6.28 / 0.00125) = **5024 N** ❗ Teoria

**Käytännössä:**
- 3-6V moottori + 16:1 vaihteisto + M8 tanko ≈ **30-50N per tanko**
- 2 tankoa → **60-100N kokonaisvoima**
- Vakuumista johtuva voima: ~150N (0.5m² @ 30kPa)

**Johtopäätös:** 
- ⚠️ Riippuvainen moottorista - testaa!
- Jos3-6V pieni moottori: yleensä 0.2-0.8A → ei ongelmaa
   - Jos kuumenee → lisää heatsink tai tarkista että jännite on 6V (ei 12V!)ko
- Tai käytä suurempaa vaihteistoa (20:1 tai 24:1)
### Suositus 3-6V moottoreille:
- ✅ Jos valmiiksi vaihteistettu (60 rpm): **3:1 lisävaihteisto**
- ✅ Jos nopea moottori: **16:1 tai 20:1 vaihteisto***
- Tai 2:1 → 160 kierrosta → **2.7 minuuttia** ✅ PAREMPI

### Voimanlaskenta
- Vakuumista johtuva voima: ~150N (0.5m² @ 30kPa)
- M8 kierretanko + 3:1 vaihteisto: ~50N nostovoimaa per tanko
- 2 tankoa → **100N kokonaisvoima** - riittää!

---

## ⚠️ Turvallisuus

1. **Ylösajosuojaus**
   - Lisää Hall-sensori tai mekaaninen raja
   - Älä aja moottoreita liian pitkään

2. **Alasajosuojaus**
   - Tarkista kannen asema ennen vakuumin aloitusta
   - Älä käynnistä pumppua jos kansi ylhäällä

3. **Synkronointi**
   - Molemmat moottorit aina samaan aikaan
   - Jos toinen jumittuu → pysäytä molemmat

4. **Virtarajoitus**
   - L298N max 2A per moottori
   -⚠️ Jos 3-6V moottorit eivät riitä:

**Ratkaisu A: Kolmas moottori**
- Lisää kolmas tanko keskelle
- 3 × 30-50N = 90-150N → riittää varmasti
- L298N ohjaa vain 2 moottoria → tarvitset toisen L298N:n tai MX1508-ohjaimen

**Ratkaisu B: Suurempi vaihteisto**
- 20:1 tai 24:1 välitys → enemmän voimaa, hitaampi
- Kannen avaus ~60-90 sekuntia

**Ratkaisu C: Päivitä 12V moottoreihin**
- Huomattavasti enemmän voimaa
- Nopeampi toiminta
- ~€10-15 per moottori

###  Jos moottorit vedetään yli → lisää heatsink

---

## 🎯 Testausjärjestys

1. ✅ Testaa vaihteistot erikseen (pyörivät sujuvasti)
2. ✅ Testaa kierretankojen pyöriminen (ei kiinni)
3. ✅ Testaa yksittäiset moottorit (oikea suunta)
4. ✅ Testaa synkronoitu nosto ilman kuormaa
5. ✅ Testaa kannen nosto (symmetrinen)
6. ✅ Testaa täysi sykli: avaa → sulje → avaa
7. ✅ Testaa vakuumilla (todellinen kuorma)

---

## 📸 Dokumentointi

Ota kuvia:
- Vaihteiston kokoonpano
- Kierretankojen asennus
- Pähkinäkiinnikkeet kannessa
- Moottoreiden kytkentä
- Toimiva mekaniikka videolla

Lisää kuvat: `kuvat/mekaniikka/ruuvitanko/`

---

## 🔄 Vaihtoehdot ja parannukset

### Vaihtoehto 1: M6 kierretanko
- Kevyempi ja ohuempi
- Nousu 1mm/kierros → nopeampi
- Pienempi voima

### Vaihtoehto 2: NEMA17 stepperit
- Tarkka asemointi
- Ei tarvitse aikaohjattua pysäytystä
- Kalliimpi (~€10/kpl)

### Vaihtoehto 3: Hammashihna
- Nopea liike
- Vaatii monimutkaisemman rakenteen
- Ei itsejäykistävä

---

**Tämä dokumentti päivitetään rakennuksen edetessä!**
