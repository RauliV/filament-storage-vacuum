# Komponenttilista – Alipaineellinen Filamenttikotelo

---

## 🔧 Pakolliset komponentit (perusversio)

### 1. Tiiviste

**Silikoninauha:**
- **Tyyppi:** Pyöreä silikoninauha, Ø 1 mm tai matala profiili 1 × 2 mm
- **Kovuus:** Shore A 40–60
- **Pituus:** Mitattava kotelon kehän mukaan + 5 cm varalle
- **Toimittajat (Suomi):**
  - **Biltema:** Silikoninauha rullalla (~10 €)
  - **Motonet:** Tiivistenauhat ja -profiilit
  - **TME.eu / Farnell:** Teolliset silikonitiivistein auhat
  - **AliExpress:** Halpaa massaa, toimitusaika 2–4 viikkoa
  
**Vaihtoehto:**
- O-renkaat (jos kannen reuna on sopiva)
- Valmis tiivistenauha itseliimautuvalla pohjalla (vähemmän tiivis)

---

### 2. Alipaineventtiili

**Vaihtoehto A: Schrader-venttiili**
- Auton/pyörän venttiili
- **Hinta:** 2–5 €
- **Toimittajat:** Biltema, Motonet, pyöräliikkeet
- **Edut:** Halpa, yleinen, helppo asentaa
- **Haitat:** Tarvitsee sovittimen käsipumppuun

**Vaihtoehto B: Presta-venttiili**
- Pyöräilystä tuttu venttiili
- **Hinta:** 3–6 €
- **Toimittajat:** Pyöräliikkeet
- **Edut:** Tiivis, kevyt

**Vaihtoehto C: Pikaliitin + takaiskuventtiili**
- Pneumatiikkapikaliitin (esim. 6 mm letkulle)
- **Hinta:** 5–15 €
- **Toimittajat:** K-Rauta, Starkki, TME.eu
- **Edut:** Helppo kiinnittää pumppu, nopea irrotus
- **Haitat:** Vaatii sopivan letkun

**Vaihtoehto D: 3D-printattu liitin + O-rengas**
- Printaat oman venttiilikiinnikkeen
- O-rengas tiivistää (esim. M8 × 2 mm)
- **Hinta:** < 1 € + printti
- **Edut:** Täysin räätälöity
- **Haitat:** Pitää suunnitella itse

**Suositus aloittelijalle:** Schrader + sovite (halvin ja helpoin)

---

### 3. Alipaineen lähde

**Vaihtoehto A: Käsipumppu (helpointa)**
- Jarrun ilmauspumppu / vakuumipumppu
- **Hinta:** 20–50 €
- **Toimittajat:** Biltema, Motonet, verkkokaupat
- **Edut:** Ei tarvitse sähköä, halpa, toimii varmasti
- **Haitat:** Manuaalinen → täytyy muistaa pumpata

**Vaihtoehto B: 12V vakuumipumppu (automaatioon)**
- Pieni 12V DC vakuumipumppu
- **Suorituskyky:** -60...-80 kPa, 10–15 L/min
- **Hinta:** 20–60 € (AliExpress, Amazon)
- **Toimittajat:** AliExpress, Biltema (kompressorit), hobby-elektroniikka
- **Edut:** Automatisoitavissa, "asenna ja unohda"
- **Haitat:** Tarvitsee virtalähteen (12V, ~2 A), äänekkäämpi

**Esimerkkejä (AliExpress):**
- "12V Mini Vacuum Pump" (haku)
- "DC Diaphragm Vacuum Pump -80kPa"

**Suositus:** Aloita käsipumpulla, lisää sähköpumppu myöhemmin jos tuntuu tarpeelliselta.

---

### 4. Paineen mittaus (valinnainen)

**Manometri (mekaaninen):**
- Alipainemittari -1...0 bar
- **Hinta:** 15–40 €
- **Toimittajat:** Biltema, K-Rauta, AliExpress
- **Edut:** Ei tarvitse elektroniikkaa, näkee paineen aina
- **Haitat:** Ei loggausta eikä hälytyksiä

**Digitaalinen paineanturi + ESP32:**
- Katso "Automaatio-osuus" alempana

---

## 🤖 Automaatio (valinnainen lisäosa)

### 1. Paineanturi

**Vaihtoehto A: BMP280 / BME280**
- **Tyyppi:** Barometrinen paineanturi (I2C)
- **Mittausalue:** 300–1100 hPa (30–110 kPa)
- **Tarkkuus:** ± 1 hPa
- **Hinta:** 3–8 €
- **Toimittajat:** AliExpress, Amazon, Sparkfun, Adafruit
- **Edut:** Halpa, helppo käyttää, I2C-väylä
- **Haitat:** Mittaa absoluuttista painetta → pitää laskea ulkoilman paineesta

**Vaihtoehto B: MPX5100DP**
- **Tyyppi:** Differentaalipaineanturi
- **Mittausalue:** 0–100 kPa (ero)
- **Tarkkuus:** ± 2.5 %
- **Hinta:** 15–25 €
- **Toimittajat:** Farnell, TME.eu, Mouser
- **Edut:** Mittaa suoraan alipaineen, tarkempi
- **Haitat:** Kalliimpi, analoginen lähtö (vaatii ADC:n)

**Suositus:** BMP280 riittää mainiosti (halpa ja helppo käyttää)

---

### 2. Mikrokontrolleri

**ESP32 DevKit V1:**
- **Ominaisuudet:** WiFi, Bluetooth, I2C, GPIO
- **Hinta:** 8–15 €
- **Toimittajat:** AliExpress, Amazon, Partco
- **Käyttö:** Paineen lukeminen, web UI, pumppuohjaus

**Vaihtoehto:** Arduino Nano / STM32 (jos ei tarvitse WiFi:ä)

---

### 3. Muut elektroniikkakomponentit

**Rele / MOSFET (pumppua varten):**
- 1-kanavainen 5V rele tai IRLZ44N MOSFET
- **Hinta:** 2–5 €
- **Toimittajat:** AliExpress, Partco

**Virtalähde:**
- 12V 2A virtalähde (jos käytät pumppua)
- **Hinta:** 10–15 €

**Buck-muunnin:**
- 12V → 5V (ESP32:lle)
- **Hinta:** 2–5 €

**Näyttö (valinnainen):**
- 0.96" OLED I2C (128×64)
- **Hinta:** 5–10 €

---

## 📦 Kotelo ja rakenneosat

### Valmis laatikko (helpoin ratkaisu)

**IKEA:**
- **SAMLA:** Läpinäkyvä muovilaatikko, eri kokoja (5–130 L)
- **Hinta:** 5–30 €
- **Edut:** Halpa, tiivis kansi, helppo modailla

**Clas Ohlson / K-Rauta:**
- Säilytyslaatikot, työkalulaatikot
- **Hinta:** 10–40 €

**Suositus:** SAMLA 22 L tai 45 L (riittää 2–4 rullalle)

---

### 3D-printatut osat

**Mitä printtailla:**
- Venttiilikiinnike kotelon seinään
- Tiivisterengasura (jos ei muuten onnistu)
- Filamentin läpiviennit
- Rullateline kotelon sisälle

**Materiaalit:**
- PETG (kestää kosteutta paremmin kuin PLA)
- Hyvä infill (> 50 %) ja monta perimetriä

---

## 💰 Kustannusarvio

### Perusversio (ei automaatiota)

| Komponentti | Hinta |
|------------|-------|
| Valmis laatikko (IKEA SAMLA) | 15 € |
| Silikoninauha (2 m) | 8 € |
| Schrader-venttiili + sovite | 5 € |
| Käsipumppu | 30 € |
| Manometri (valinnainen) | 20 € |
| **Yhteensä** | **~78 €** |

---

### Automaattiversio

| Komponentti | Hinta |
|------------|-------|
| Perusversio | 78 € |
| ESP32 | 12 € |
| BMP280 | 5 € |
| 0.96" OLED | 8 € |
| 12V vakuumipumppu | 35 € |
| Rele + virtalähde + buck | 20 € |
| **Yhteensä** | **~158 €** |

---

## 🛒 Suositeltavat toimittajat (Suomi)

1. **Biltema** – tiivisteet, pumput, venttiilit, työkalut
2. **K-Rauta / Starkki** – laatikot, liittimet, tiivisteet
3. **IKEA** – SAMLA-laatikot
4. **Partco.fi** – ESP32, anturit, elektroniikkakomponentit (nopea toimitus Suomesta)
5. **TME.eu** – laaja valikoima, nopea toimitus Puolasta
6. **AliExpress** – halpa, mutta hidas (2–4 viikkoa)

---

## 📌 Muistiinpanot / lisättävää

- Omat huomiot testauksesta
- Toimivat komponenttikombinaatiot
- Tekniset datasheetit → tallenna `komponentit/`-kansioon
