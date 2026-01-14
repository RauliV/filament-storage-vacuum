# 4-Moottorisen kannen nosto-ohjaus

**Käyttötarkoitus:** Jos 2 moottoria ei riitä nostamaan kantta vakuumia vastaan  
**Ratkaisu:** 4 moottoria (2 per tanko) → tuplavoimaa

---

## 📋 Kytkentä

```
ESP32          L298N #1 (Vasen tanko)       L298N #2 (Oikea tanko)
─────          ─────────────────────        ─────────────────────
GPIO 16    →   IN1  (M1 suunta)             
GPIO 17    →   IN2  (M1 suunta)
GPIO 18    →   ENA  (M1 nopeus)
GPIO 19    →   IN3  (M2 suunta)
GPIO 21    →   IN4  (M2 suunta)
GPIO 22    →   ENB  (M2 nopeus)

GPIO 25    →                                IN1  (M3 suunta)
GPIO 26    →                                IN2  (M3 suunta)
GPIO 27    →                                ENA  (M3 nopeus)
GPIO 32    →                                IN3  (M4 suunta)
GPIO 33    →                                IN4  (M4 suunta)
GPIO 14    →                                ENB  (M4 nopeus)

6V PSU     →   +12V (molemmat L298N)
GND        →   GND (yhteinen)
```

---

## 💻 ESP32-koodi

### Lisää alkuun (päivitetyt pinnit):

```cpp
// ===== 4 MOOTTORIN OHJAUS (2x L298N) =====

// L298N #1: Vasen tanko (Moottorit 1+2)
const int MOTOR_1_IN1 = 16;
const int MOTOR_1_IN2 = 17;
const int MOTOR_1_EN = 18;

const int MOTOR_2_IN3 = 19;
const int MOTOR_2_IN4 = 21;
const int MOTOR_2_EN = 22;

// L298N #2: Oikea tanko (Moottorit 3+4)
const int MOTOR_3_IN1 = 25;
const int MOTOR_3_IN2 = 26;
const int MOTOR_3_EN = 27;

const int MOTOR_4_IN3 = 32;
const int MOTOR_4_IN4 = 33;
const int MOTOR_4_EN = 14;

// Moottoriasetukset
const int MOTOR_SPEED = 255; // 0-255 (täysi teho 3-6V moottoreille)
const int OPEN_TIME_MS = 40000; // 40 sekuntia (säädä testauksen mukaan)
const int CLOSE_TIME_MS = 40000;
```

---

### Setup() -funktio:

```cpp
void setup() {
  Serial.begin(115200);
  
  // ===== MOOTTORIPINNIT =====
  // L298N #1
  pinMode(MOTOR_1_IN1, OUTPUT);
  pinMode(MOTOR_1_IN2, OUTPUT);
  pinMode(MOTOR_1_EN, OUTPUT);
  pinMode(MOTOR_2_IN3, OUTPUT);
  pinMode(MOTOR_2_IN4, OUTPUT);
  pinMode(MOTOR_2_EN, OUTPUT);
  
  // L298N #2
  pinMode(MOTOR_3_IN1, OUTPUT);
  pinMode(MOTOR_3_IN2, OUTPUT);
  pinMode(MOTOR_3_EN, OUTPUT);
  pinMode(MOTOR_4_IN3, OUTPUT);
  pinMode(MOTOR_4_IN4, OUTPUT);
  pinMode(MOTOR_4_EN, OUTPUT);
  
  // Pysäytä kaikki moottorit
  stopAllMotors();
  
  Serial.println("✅ 4-moottorinen kannen nosto-ohjaus valmis");
  
  // ... muu setup-koodi ...
}
```

---

### Uudet funktiot:

```cpp
// ===== PYSÄYTÄ KAIKKI MOOTTORIT =====
void stopAllMotors() {
  // L298N #1
  digitalWrite(MOTOR_1_IN1, LOW);
  digitalWrite(MOTOR_1_IN2, LOW);
  digitalWrite(MOTOR_2_IN3, LOW);
  digitalWrite(MOTOR_2_IN4, LOW);
  analogWrite(MOTOR_1_EN, 0);
  analogWrite(MOTOR_2_EN, 0);
  
  // L298N #2
  digitalWrite(MOTOR_3_IN1, LOW);
  digitalWrite(MOTOR_3_IN2, LOW);
  digitalWrite(MOTOR_4_IN3, LOW);
  digitalWrite(MOTOR_4_IN4, LOW);
  analogWrite(MOTOR_3_EN, 0);
  analogWrite(MOTOR_4_EN, 0);
}

// ===== AVAA KANSI (4 moottoria ylöspäin) =====
void openLidMotors() {
  Serial.println("🔼 Avataan kansi (4 moottoria)...");
  
  // Kaikki moottorit ylöspäin (sama suunta)
  digitalWrite(MOTOR_1_IN1, HIGH);
  digitalWrite(MOTOR_1_IN2, LOW);
  digitalWrite(MOTOR_2_IN3, HIGH);
  digitalWrite(MOTOR_2_IN4, LOW);
  digitalWrite(MOTOR_3_IN1, HIGH);
  digitalWrite(MOTOR_3_IN2, LOW);
  digitalWrite(MOTOR_4_IN3, HIGH);
  digitalWrite(MOTOR_4_IN4, LOW);
  
  // Aseta nopeus (voit hienosäätää per moottori)
  analogWrite(MOTOR_1_EN, MOTOR_SPEED);
  analogWrite(MOTOR_2_EN, MOTOR_SPEED);
  analogWrite(MOTOR_3_EN, MOTOR_SPEED);
  analogWrite(MOTOR_4_EN, MOTOR_SPEED);
  
  delay(OPEN_TIME_MS);
  
  stopAllMotors();
  Serial.println("✅ Kansi auki!");
}

// ===== SULJE KANSI (4 moottoria alaspäin) =====
void closeLidMotors() {
  Serial.println("🔽 Suljetaan kansi (4 moottoria)...");
  
  // Kaikki moottorit alaspäin (vastakkainen suunta)
  digitalWrite(MOTOR_1_IN1, LOW);
  digitalWrite(MOTOR_1_IN2, HIGH);
  digitalWrite(MOTOR_2_IN3, LOW);
  digitalWrite(MOTOR_2_IN4, HIGH);
  digitalWrite(MOTOR_3_IN1, LOW);
  digitalWrite(MOTOR_3_IN2, HIGH);
  digitalWrite(MOTOR_4_IN3, LOW);
  digitalWrite(MOTOR_4_IN4, HIGH);
  
  // Aseta nopeus
  analogWrite(MOTOR_1_EN, MOTOR_SPEED);
  analogWrite(MOTOR_2_EN, MOTOR_SPEED);
  analogWrite(MOTOR_3_EN, MOTOR_SPEED);
  analogWrite(MOTOR_4_EN, MOTOR_SPEED);
  
  delay(CLOSE_TIME_MS);
  
  stopAllMotors();
  Serial.println("✅ Kansi suljettu!");
}
```

---

### Hienosäätö (jos kansi kallistuu):

```cpp
// Jos vasen puoli nousee nopeammin kuin oikea:
analogWrite(MOTOR_1_EN, 250); // Vasen moottori 1
analogWrite(MOTOR_2_EN, 250); // Vasen moottori 2
analogWrite(MOTOR_3_EN, 255); // Oikea moottori 3 (täysi teho)
analogWrite(MOTOR_4_EN, 255); // Oikea moottori 4 (täysi teho)
```

---

## 🔧 Vaihtoehtoiset kytkentäratkaisut

### Vaihtoehto A: Molemmat moottorit rinnakkain per tanko

Jos **mekaanisesti** molemmat moottorit kiinni samaan vaihteistoon:

```cpp
// Vain 2 ryhmää (vasen + oikea)
void openLidMotors() {
  // Vasen tanko (moottorit 1+2 rinnakkain)
  digitalWrite(MOTOR_1_IN1, HIGH);
  digitalWrite(MOTOR_1_IN2, LOW);
  digitalWrite(MOTOR_2_IN3, HIGH);
  digitalWrite(MOTOR_2_IN4, LOW);
  analogWrite(MOTOR_1_EN, MOTOR_SPEED);
  analogWrite(MOTOR_2_EN, MOTOR_SPEED);
  
  // Oikea tanko (moottorit 3+4 rinnakkain)
  digitalWrite(MOTOR_3_IN1, HIGH);
  digitalWrite(MOTOR_3_IN2, LOW);
  digitalWrite(MOTOR_4_IN3, HIGH);
  digitalWrite(MOTOR_4_IN4, LOW);
  analogWrite(MOTOR_3_EN, MOTOR_SPEED);
  analogWrite(MOTOR_4_EN, MOTOR_SPEED);
  
  delay(OPEN_TIME_MS);
  stopAllMotors();
}
```

---

### Vaihtoehto B: Käytä vain kolmea moottoria

Jos et halua ostaa toista L298N:tä, käytä **3 moottoria**:
- 2 vasemmalla (L298N #1)
- 1 oikealla (MX1508 tai toinen L298N)

**Voima:** 3 × 30-50N = 90-150N (pitäisi riittää)

---

## ⚠️ Huomioitavaa

1. **Virrankulutus:** 4 moottoria @ 0.5A = 2A yhteensä → tarvitset vähintään 2-3A virtalähteen
2. **Kuumeneminen:** L298N:t voivat kuumentua → lisää heatsink tai tuuletus
3. **Synkronointi:** Kaikki moottorit TÄYTYY käynnistyä samaan aikaan
4. **Testaa ensin 2 moottorilla** - lisää 2 lisää vain jos voima ei riitä!

---

## 📊 Voimalaskelmat

**2 moottoria (alkuperäinen):**
- 2 × 30-50N = 60-100N
- Vakuumi: ~150N @ 30kPa
- ⚠️ Saattaa olla tiukilla

**4 moottoria:**
- 4 × 30-50N = **120-200N**
- ✅ Riittää varmasti!

**3 moottoria (kompromissi):**
- 3 × 30-50N = 90-150N
- ✅ Pitäisi riittää, halvempi kuin 4

---

## 🎯 Suositus

1. **Aloita 2 moottorilla** - testaa riittääkö voima
2. Jos ei riitä → **lisää 2 moottoria lisää** samaan tankoon
3. Jos haittaa monimutkaisuus → **päivitä 12V moottoreihin** (enemmän voimaa per moottori)

**Paras ratkaisu:** 4 moottoria antaa varmasti tarpeeksi voimaa 3-6V moottoreilla!
