# Projektin Yhteenveto ja Rakenne

**Tila:** Fyysinen rakenne valmis, elektroniikka suunnitteilla  
**Tyyppi:** Alipaineellinen filamenttisäilytys automaatiolla

---

## 🎯 Projektin tavoite

Rakentaa **toimiva, kuiva ja puhdas filamenttisäilytys** joka:
- Säilyttää filamentit **alipaineessa** (-25 kPa tyypillisesti)
- **Automaattisesti** seuraa tilaa ja ohjaa pumppua
- **Automatisoi kannen avauksen** DC-moottoreilla
- Näyttää tilan **OLED-paneelilla** ja **web-käyttöliittymällä**
- Sisältää **älykkäät efektit**: LED-animaatiot ja vakuumiäänet
- Optimoitu **BambuLab P1S + AMS** -käyttöön

---

## 📐 Fyysiset mitat ja rakenne

### Valmistettu rakenne:
- **Tukirunko:** Hitsattu teräs (käsin tehty)
- **Sivulevyt:** 3 mm peilaava muovi (TTC450PRO jyrsimellä leikattu)
- **Kansilevy:** 3 mm läpinäkyvä polykarbonaatti (TTC450PRO)
- **Tiivistys:** 1 mm silikonikaru urituksissa
- **Saranat:** Integroitu 3D-mallissa (Filamenttiteline.3mf, 45 osaa)

**Huom:** Teräsrunko tehty fyysisesti, mutta ei vielä lisätty 3D-malliin.

---

## 🛠️ Käytetyt työkalut

### Valmistus:
| Työkalu | Malli | Käyttö |
|---------|-------|--------|
| **CNC-jyrsin** | TTC450PRO | Sivulevyt, kansilevy, urat |
| **3D-tulostin** | BambuLab P1S | Kiinnikkeet, vaihteistot, kotelot |
| **Hitsauslaite** | (käsin) | Teräsrunko |

### Suunnittelu:
- **CAD:** Fusion 360 / FreeCAD (3MF-malli olemassa)
- **Slicer:** BambuStudio
- **Koodiympäristö:** Arduino IDE (ESP32)
- **Elektroniikkasuunnittelu:** Fritzing (piirikaaviot)

---

## ⚙️ Järjestelmän arkkitehtuuri

```
┌──────────────────────────────────────────────────────────┐
│                 FILAMENTTIKOTELO                         │
│  ┌────────────────────────────────────────────────────┐  │
│  │  ESP32 (Ohjausyksikkö)                             │  │
│  │  ├─ BME280 (Paine/Lämpö/Kosteus)                   │  │
│  │  ├─ 2-4× DC-moottorit 3-6V (Kannen nosto)          │  │
│  │  ├─ 12V Vakuumipumppu (Alipaineen luonti)          │  │
│  │  ├─ Sähköventtiili (Paineen vapautus)              │  │
│  │  ├─ WS2812B LED-nauha 30 LEDiä (Animaatiot)        │  │
│  │  ├─ Passive buzzer (Ääniefektit)                   │  │
│  │  └─ Magneettikytkimet (Kannen tila)                │  │
│  └────────────────────────────────────────────────────┘  │
│                                                           │
│  Filamentit: 4-8 rullaa (1 kg kukin)                     │
│  Materiaali: PLA, PETG, ABS, TPU                         │
└───────────────────────┬───────────────────────────────────┘
                        │ WiFi (MQTT)
                        │
         ┌──────────────┴──────────────┐
         │                             │
    ┌────▼────┐                  ┌─────▼─────┐
    │ UI-Panel│                  │  Palvelin │
    │ (OLED)  │                  │ (PC/RPi)  │
    │ Irrall. │                  │ Web UI    │
    └─────────┘                  └───────────┘
```

---

## 📚 Dokumentaation rakenne

Projekti on jaettu **loogisiin moduuleihin**:

### 🔹 Perustiedot
1. **[README.md](../README.md)** - Projektin pääsivu
2. **Tämä tiedosto** - Kokonaisuuden yhteenveto

### 🔹 Mekaniikka
3. **[3D-Malli.md](3D-Malli.md)** - 45-osaisen CAD-mallin kuvaus
4. **[Rakenne.md](Rakenne.md)** - Kokoonpano-ohjeet, tiivistys
5. **[3D-Printattavat-Osat.md](3D-Printattavat-Osat.md)** - Mitä tulostaa (~€113 säästö)

### 🔹 Automaatio & Mekaniikka
6. **[Ruuvitankomekanismi.md](Ruuvitankomekanismi.md)** - DC-moottorit + kierretangot
7. **[4-Moottorin-Koodi.md](4-Moottorin-Koodi.md)** - Lisävoima 3-6V moottoreille

### 🔹 Elektroniikka
8. **[Komponentit.md](Komponentit.md)** - Ostoslista (€78-158 + työkalut)
9. **[code/esp32_paineanturi.ino](../code/esp32_paineanturi.ino)** - ESP32-koodi
10. **[code/README.md](../code/README.md)** - Koodin asennus

### 🔹 Käyttöliittymät
11. **[Kayttoliittymat.md](Kayttoliittymat.md)** - OLED-paneeli + MQTT Web UI
12. **[Aaniefektit-ja-Animaatiot.md](Aaniefektit-ja-Animaatiot.md)** - LED-show + äänet

### 🔹 Lisäominaisuudet
13. **[Lisaominaisuudet.md](Lisaominaisuudet.md)** - Automaatio, efektit
14. **[Filamenttien-Syotto-AMS.md](Filamenttien-Syotto-AMS.md)** - BambuLab AMS-integraatio
15. **[Muistiinpanot.md](Muistiinpanot.md)** - Projektipäiväkirja

---

## 🚀 Aloitusopas uudelle lukijalle

### 1️⃣ Aloita perusteista
Lue ensin: **[README.md](../README.md)** ja **[Komponentit.md](Komponentit.md)**

### 2️⃣ Tutki mekaanista rakennetta
- **[3D-Malli.md](3D-Malli.md)** - Ymmärrä 45-osainen rakenne
- **[Rakenne.md](Rakenne.md)** - Kokoonpano-ohjeet

### 3️⃣ Suunnittele automaatio
- **[Ruuvitankomekanismi.md](Ruuvitankomekanismi.md)** - Kannen avaus
- **[Kayttoliittymat.md](Kayttoliittymat.md)** - Ohjaus

### 4️⃣ Koodaa ja testaa
- **[code/esp32_paineanturi.ino](../code/esp32_paineanturi.ino)** - Lataa ESP32:lle
- **[Aaniefektit-ja-Animaatiot.md](Aaniefektit-ja-Animaatiot.md)** - Testaa efektit

### 5️⃣ Integraatio tulostimeen
- **[Filamenttien-Syotto-AMS.md](Filamenttien-Syotto-AMS.md)** - Yhdistä BambuLab P1S:ään

---

## 📊 Kustannukset

| Kategoria | Hinta | Huomiot |
|-----------|-------|---------|
| **Elektroniikka (perus)** | €78 | ESP32, BME280, pumppu, rele |
| **Automaatio (täysi)** | +€80 | Moottorit, ohjaimet, LEDit, venttiili |
| **Mekaaniikka** | €20 | Kierretangot, laakerit, M8-mutterit |
| **Materiaali (levyt)** | €50-100 | 3mm muovi/PC (jos ostat itse) |
| **3D-tulosteet** | €0 | BambuLab P1S (oma tulostin) |
| **Työ (hitsaus, jyrsintä)** | €0 | Itse tehty |
| **AMS-integraatio** | €30-50 | PTFE-tuubit, liittimet, solenoidi |
| **YHTEENSÄ** | **€258-328** | Täysin automaattinen järjestelmä |

**Jos ostat valmiin metallikaapin ja muutat sen:** -€100-200 (ei hitsausta)

---

## 🔧 Teknologiat ja kirjastot

### ESP32-koodi:
```cpp
#include <Adafruit_BME280.h>      // Paineanturi
#include <Adafruit_SSD1306.h>     // OLED-näyttö
#include <FastLED.h>               // LED-animaatiot
#include <WiFi.h>                  // WiFi-yhteys
#include <PubSubClient.h>          // MQTT-viestit
```

### Palvelin (Python):
```python
fastapi                            # Web-palvelin
paho-mqtt                          # MQTT-client
uvicorn                            # ASGI-palvelin
sqlalchemy / sqlite3               # Tietokanta
plotly                             # Graafit (frontend)
```

### Frontend:
- **HTML5 + JavaScript** (yksinkertainen)
- **Plotly.js** (interaktiiviset graafit)
- **Vaihtoehto:** React/Vue.js (edistynyt)

---

## ⚡ Pikalinkit tärkeimpiin asioihin

| Kysymys | Dokumentti |
|---------|-----------|
| Mitä komponentteja tarvitaan? | [Komponentit.md](Komponentit.md) |
| Miten kansi avataan automaattisesti? | [Ruuvitankomekanismi.md](Ruuvitankomekanismi.md) |
| Miten koodaan ESP32:n? | [code/esp32_paineanturi.ino](../code/esp32_paineanturi.ino) |
| Miten teen Web UI:n? | [Kayttoliittymat.md](Kayttoliittymat.md) |
| Mitä osia voin 3D-tulostaa? | [3D-Printattavat-Osat.md](3D-Printattavat-Osat.md) |
| Miten yhdistän AMS:ään? | [Filamenttien-Syotto-AMS.md](Filamenttien-Syotto-AMS.md) |

---

## 📈 Projektin kehitysvaiheet

### ✅ Valmis:
- [x] 3D-CAD-malli (45 osaa)
- [x] Teräsrungon hitsaus
- [x] Levyjen jyrsintä (TTC450PRO)
- [x] ESP32-koodin v2.1 (täysi automaatio)
- [x] Dokumentaatio (15 tiedostoa)
- [x] GitHub-repo julkaistu

### 🔄 Käynnissä:
- [ ] Mekaniikan kokoonpano
- [ ] Tiivistyksen testaus
- [ ] Elektroniikan asennus
- [ ] DC-moottorien vaihteistojen tulostus

### 🔜 Seuraavaksi:
- [ ] Vakuumitestaus
- [ ] Web-palvelimen pystytys
- [ ] AMS-integraatio
- [ ] Lopputestit

---

## 🎓 Mitä tästä oppii?

Tämä projekti yhdistää:
- **Mekaniikka:** CNC-työstö, hitsaus, tiivistys, voimansiirto
- **Elektroniikka:** ESP32, anturit, moottorit, releet
- **Ohjelmointi:** C++ (Arduino), Python (web), JavaScript
- **IoT:** MQTT, WiFi, reaaliaikainen data
- **Automaatio:** PID-säätö, tilakoneet, animaatiot
- **3D-tulostus:** PETG-osat, vaihteistot, kiinnikkeet

**Vaikeustaso:** ⭐⭐⭐⭐ (Edistynyt - vaatii monipuolista osaamista)

---

## 🤝 Osallistuminen

Katso: **[CONTRIBUTING.md](../CONTRIBUTING.md)**

Projektiin voi osallistua:
- 🐛 Raportoimalla bugeja
- 💡 Ehdottamalla parannuksia
- 🔧 Koodaamalla
- 📝 Parantamalla dokumentaatiota
- 🎨 Suunnittelemalla 3D-osia
- 📸 Jakamalla toteutuskuvia

---

## 📞 Tuki ja yhteystiedot

- **GitHub Issues:** [RauliV/filament-storage-vacuum/issues](https://github.com/RauliV/filament-storage-vacuum/issues)
- **Keskustelu:** [Discussions](https://github.com/RauliV/filament-storage-vacuum/discussions)

---

## 🌟 Inspiraatio

Tämä projekti on syntynyt tarpeesta pitää filamentit **kuivina ja pölyttöminä** ilman jatkuvaa kuivaushormien käyttöä. Alipaine estää kosteuden pääsyn sisään ja LED-efektit tekevät kotelosta sci-fi-laitteen! 🚀

**"Miksi tyydyä tylsään laatikkoon, kun voi rakentaa älykkään filamenttitehtaan?"** 💡

---

Tehty ❤️:llä Suomessa 🇫🇮  
© 2026 [@RauliV](https://github.com/RauliV) | [MIT License](../LICENSE)
