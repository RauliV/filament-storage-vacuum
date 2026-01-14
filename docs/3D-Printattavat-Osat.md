# 3D-Printattavat osat ja komponentit

---

## ✅ VOIDAAN TULOSTAA (Suositus)

### 1. Venttiilikiinnikkeet ja adapterit

**Alipaineventtiili-kiinnike:**
- Poraat reiän koteloon (esim. Ø 10 mm)
- 3D-printtaat kiinnikkeen jossa O-rengas tiivistää
- Venttiili ruuvataan kiinnikkeeseen
- **Materiaalit:** PETG tai ABS (kestävämpi kuin PLA)
- **Säästö:** 5-10 € per liitin

**Suunnittelutips:**
```
┌─────────────┐
│  Kotelon    │
│   seinä     │
└──────┬──────┘
       │ Reikä
   ┌───┴───┐
   │ O-ring│  ← Tiivistää
   └───┬───┘
   ┌───┴───┐
   │ 3D    │  ← Printtattu kiinnike
   │ Print │     (kierteet sisällä)
   └───┬───┘
   ┌───┴───┐
   │Venttiili│
   └───────┘
```

---

### 2. Magneettikytkimien kiinnikkeet

**Kiinnityskotelot:**
- Reed-kytkimelle (kotelon sisään)
- Magneetille (kannen reunaan)
- Kiinnitys ruuveilla tai liimaamalla
- **Materiaalit:** PLA riittää (ei mekaanista rasitusta)
- **Säästö:** Ostat vain magneetin ja kytkimen (~3 €), kotelo tulostettuna

**Esimerkki:**
```
Kansi:  [========]
         │
         ▼ Magneetti (3D-printattu kotelo)
        
Runko:  [========]
         │
         ▼ Reed-kytkin (3D-printattu kotelo)
```

---

### 3. LED-nauhan kiinnikkeet ja diffuusorit

**LED-profiilit:**
- Kotelon sisäreunoihin
- Diffuusoiva kanava (valkoinen/luonnollinen PLA)
- Klipsikiinnitys
- **Materiaalit:** PLA tai PETG
- **Säästö:** 10-20 € (vs. alumiiniprofiilit)

**Diffuusori-vinkki:**
- Tulosta valkoisella filamentilla
- 2-3 perimetteriä, 20-30% infill
- Hajauttaa valon tasaisesti

---

### 4. Kaapeliläpiviennit

**Tiivistettävät läpiviennit:**
- Elektroniikan kaapeleille
- PTFE-putki filamentille (jos tulostat suoraan kotelosta)
- O-rengas tiivistämään
- **Materiaalit:** PETG (joustavampi)
- **Säästö:** 5-15 € per läpivienti

---

### 5. Anturikiinnikkeet

**BME280/BMP280 -kiinnike:**
- Kotelon sisäseinälle
- Anturi napsahtaa paikalleen
- Ilmavirtaus anturin ympärillä
- **Materiaalit:** PLA riittää

**ESP32 + OLED -kotelo:**
- Suojakotelo sisälle tai ulkopuolelle
- Läpinäkyvä kansi OLED:lle (kirkas PETG)
- Tuuletusurat
- **Materiaalit:** PLA runko, PETG kansi

---

### 6. DC-moottoripohjainen ruuvitankomekanismi ⭐ KÄYTÖSSÄ

**Kaksipuolinen symmetrinen kannen nosto**

#### a) Vaihteistot (2 kpl)
**Tarkoitus:** Vähentää moottorin nopeutta ja kasvattaa voimaa  
**Materiaali:** PETG tai ABS (kestää rasituksen)  
**Tulostusaika:** ~3-4h per vaihteisto  
**Infill:** 40-50%

**Osat:**
- Moottorilaippa (kiinnitys moottoriin)
- Hammaspyörät: 10T → 30T → 60T (3:1 → 2:1 = 6:1 kokonaisvälitys)
- La8keripesät akseleille
- Kotelo (suojaa pölyltä)

**Suunnittelu:** Käytä moduuli 1.0 hammastusta, lisää 0.2mm välyä  
**Säästö:** ~€35-50 (vs. kaksi lineaaritoimilaitetta)

#### b) Pähkinäkiinnikkeet kanteen (2 kpl)
**Tarkoitus:** Pitää M8 mutteri paikallaan kannessa  
**Materiaali:** PETG  
**Tulostusaika:** ~1h per kpl  

**Rakenne:** Heksasokkelo M8 mutterille + M4 kiinnitysreiät

#### c) Ylälaakerikiinnikkeet (2 kpl)
**Tarkoitus:** Tukee kierretangon yläpäätä  
**Materiaali:** PETG/PLA  
**Tulostusaika:** ~1h per kpl

**Sisältää:** 608-laakeripesä + kiinnitys kattoon

#### d) Pohjan moottorikotelo (2 kpl)
**Tarkoitus:** Yhdistelmä - moottori + vaihteisto + alalaakeri  
**Materiaali:** PETG  
**Tulostusaika:** ~2h per kpl

**Katso tarkemmat ohjeet:** [Ruuvitankomekanismi.md](Ruuvitankomekanismi.md)

---

### 8. Manuaalisen UI-paneelin kotelo (Irrallinen)

**Käyttötarkoitus:** OLED-näyttö + painikkeet + potentiometri **irrallisena laitteena**  
**Materiaali:** PLA  
**Tulostusaika:** ~3-4h (kotelo + kiinnike/jalusta)

**Paneelin kotelo sisältää:**
- OLED 128x64 -näytön kehys (press-fit tai ruuvikiinnitys)
- 4x painikereikä (12mm halkaisija, tact switch:lle)
- Potentiometrin reikä (7mm halkaisija)
- Kaapeliläpivienti takaosaan (M12-kierteellä)
- Sisäinen tila elektroniikalle (OLED + piirilevykkeelle)

**Asennusvaihtoehdot (tulosta yksi):**

#### a) Seinäkiinnike
- 2× M4 ruuvireiät (50mm jaolla)
- Kiinnitys suoraan seinään tai kotelon viereen
- Tulostusaika: +30min

#### b) Pöytäjalusta
- Kallistettava tukijalka (15-45°)
- Liukuestematto pohjan (tai tulosta teksturoidulla pohjalla)
- Tulostusaika: +1h

#### c) Magneettilevey
- 2-4× neodyymimagneetti (20×3mm)
- Kiinnitys suoraan kotelon metallirunkoon
- Tulostusaika: +20min
- Magneetit: ~€3

#### d) Ripustuslenkki
- Silmukka yläosaan
- Ripusta koukusta tai kotelon sivusta
- Tulostusaika: +10min

**Kaapelinhallinnan yksityiskohdat:**
- Kaapelin suojaputki (joustava tai 3D-tulostettu)
- Kaapeliläpivienti koteloon: M12 kierrenippa + O-rengas
- Kaapelin pituus: 50-100 cm (suositus: 75 cm)
- Valinnainen: JST-liitin keskelle (nopea irrotus)

**Katso:** [Kayttoliittymat.md](Kayttoliittymat.md)

**Piirilevy-vinkki:**  
Voit suunnitella pienen piirilevyn (5×7 cm) jossa:  
- OLED-pistoke  
- 4× painikkeen pull-down-vastukset (10kΩ)  
- Potentiometri suoraan  
- 6-pin liitin kaapelille  
→ Siisti lopputulos ilman löysiä johtoja!

---

### 9. Gearbox-kotelot (ulkoasennus)

**Käyttötarkoitus:** Suojaa moottorit + vaihteistot kotelon ulkopuolella  
**Materiaali:** PETG (kestää ympäristöä)  
**Tulostusaika:** ~4h per kotelo

**Sisältää:**
- Suljettu kotelo vaihteiston ympärille
- Tuuletusreiät (verkolla suojattu)
- Kiinnitysjalat takaseinään (M6-ruuvit)
- Akselin läpivienti laakeroidulla männällä

**Säästö:** ~€20-30 per kotelo (vs. valmis teollisuuskotelo)

---

### 10. Läpivientikiinnikkeet kierretangoille

**Käyttötarkoitus:** Tiivis läpivienti kierretangolle kotelon läpi  
**Materiaali:** PETG  
**Tulostusaika:** ~1.5h per kpl

**Sisältää:**
- 608-laakeripesä
- Tiivistys-ura O-rengasta varten
- Kiinnitys koteloon M4-ruuveilla

**Vaatii lisäksi:**
- M16 läpivientinippa (~€5)
- O-rengas 12×2mm NBR (~€1)

---

### 7. Pumppukiinnikkeet

**Kiinnitysbraketit:**
- Toimilaite runkoon
- Varsi kanteen
- Mahdollisesti nivelliike (printattava nivel)
- **Materiaalit:** PETG tai ABS (kestävyys)
- **Säästö:** 10-20 €

**Huom:** Itse toimilaite täytyy ostaa (~€25-40), mutta kiinnikkeet tulostettuna!

---

### 7. Pumppukiinnikkeet

**Pumpun kiristimet:**
- Klamppaustyyli
- Tärinänvaimennustyynyt (TPU)
- **Materiaalit:** PETG + TPU

---

### 9. Relekotelo ja DIN-kiinnike

**Elektroniikkakotelo:**
- Rele, virtalähde, buck-muuntimet
- Tuuletus
- Kaapelointireitit
- DIN-kiinnike (jos haluat teollisuustyylisen asennuksen)
- **Materiaalit:** PLA tai PETG

---

### 9. Filamenttitelineet kotelon sisälle

**Rullateline:**
- Pyörivä akseli kuulalaakerilla (esim. 608-kuulalaakeri)
- Useampi rulla vierekkäin
- Kiinnitys kotelon seiniin
- **Materiaalit:** PETG (PLA saattaa taipua)
- **Säästö:** 20-50 € (vs. metalliteline)

**Esimerkki:**
```
     Akseli (M8 kierretanko, ~2 €)
        │
   ┌────┴────┐
   │ Rulla 1 │  ← 3D-printattu laakerikotelo
   └─────────┘
   ┌─────────┐
   │ Rulla 2 │
   └─────────┘
```

---

### 10. Pumpun äänenvaimennusputki

**Äänenvaimennus:**
- Putki jossa sisällä vaimennusmateriaali (esim. vaahtomuovi)
- Vähentää pumppumelua
- **Materiaalit:** PLA tai PETG
- **Säästö:** 10-15 €

---

### 11. Sähköventtiili-adapteri

**Letkuadapterit:**
- Pneumatiikkapikaliittimet (6mm, 8mm)
- Sovite venttiiliin
- **Materiaalit:** PETG (joustavuus)
- **Säästö:** 3-5 € per sovitin

---

### 12. Jalat ja tukijalat

**Kotelolla jalat:**
- Vaimentavat (TPU)
- Säädettävät (kierteet)
- **Materiaalit:** PLA runko, TPU pehmusteen

---

## ⚠️ OSITTAIN TULOSTETTAVA

### 1. Tiivisterakenteet

**Mitä voi tulostaa:**
- Tiivisteen ura (jos ei jyrsitä suoraan)
- Tiivistelistan runko
- Tiivisterengas pidike

**Mitä EI voi tulostaa:**
- Tiiviste itsessään → Osta silikoninauha (1-3 €/metri)

**TPU-tiiviste (vaihtoehto):**
- TPU:lla voi tulostaa "tiivisteen"
- Shore 95A tai pehmeämpi
- Ei yhtä hyvä kuin silikoni, mutta toimii

---

### 2. Saranakiinnikkeet

**Mitä voi tulostaa:**
- Saranakiinnikkeet runkoon ja kanteen
- "Living hinge" -tyyppiset nivelsaranat (TPU)

**Mitä kannattaa ostaa:**
- Metalliset saranat (kestävämpi, sileämpi liike)
- **Hinta:** 5-10 € per pari

**Hybridi:**
- Metalliset saranat + 3D-printatut kiinnikkeet

---

## ❌ EI KANNATA TULOSTAA (Osta!)

### 1. Paineanturi (BME280/BMP280)

**Miksi ei:**
- Vaatii tarkkaa kalibrointia
- Elektroniikkaa ei voi tulostaa
- **Hinta:** 5-10 € (halvempi ostaa kuin yrittää DIY)

---

### 2. Vakuumipumppu

**Miksi ei:**
- Mekaanisesti monimutkainen
- Vaatii tiivisteet ja männät
- Sähkömoottori tarvitaan
- **Hinta:** 30-60 € (ostettuna toimii luotettavasti)

---

### 3. ESP32-kortti

**Miksi ei:**
- Elektroniikka ja mikrokontrolleri
- **Hinta:** 8-15 €
- **Voi tulostaa:** Suojakotelon sille

---

### 4. Sähköventtiili (solenoid)

**Miksi ei:**
- Kelat, magneetit, tiivisteet
- Vaatii tarkkaa valmistusta
- **Hinta:** 10-20 € (ostettuna luotettava)
- **Voi tulostaa:** Kiinnikkeet ja adapterit

---

### 5. Lineaaritoimilaite

**Miksi ei:**
- Moottori, hammaspyörät, ruuvi
- Vaatii tarkkuutta ja voimaa
- **Hinta:** 30-80 € (ostettuna toimii pitkään)
- **Voi tulostaa:** Kiinnikkeet ja braketit

---

### 6. Rele ja motor driver

**Miksi ei:**
- Elektroniikkaa
- **Hinta:** 5-15 € per moduuli
- **Voi tulostaa:** Kiinnityskotelo

---

### 7. Kuulalaakerit

**Miksi ei:**
- Vaatii tarkkaa valmistusta ja terästä
- **Hinta:** 0.50-2 € per laakeri (608)
- **Voi tulostaa:** Laakerikotelo akseleille

---

### 8. Virtalähde

**Miksi ei:**
- Elektroniikkaa ja turvallisuus
- **Hinta:** 10-20 €

---

## 💰 Säästölaskelma

| Komponentti | Ostettuna | Printattuna | Säästö |
|------------|-----------|-------------|--------|
| Venttiilikiinnikkeet (3x) | 15-30 € | ~1 € filamentti | **~20 €** |
| Magneettikytkimien kotelot | 10 € | ~0.50 € | **~9 €** |
| LED-profiilit | 15 € | ~2 € | **~13 €** |
| Filamenttiteline | 40 € | ~5 € + laakerit 4 € | **~31 €** |
| Anturikiinnikkeet | 10 € | ~0.50 € | **~9 €** |
| Toimilaittee kiinnikkeet | 20 € | ~2 € | **~18 €** |
| Elektroniikkakotelo | 15 € | ~2 € | **~13 €** |
| **YHTEENSÄ** | **~125 €** | **~13 €** | **~113 €** |

**Filamenttimäärä:** ~500-800 g (10-16 € filamenttia)

---

## 🛠️ Tulostusvinkit

### Materiaalit:

**PLA:**
- Helppo tulostaa
- Riittävä useimpiin kiinnikkeisiin
- Ei kosteutta kestävä

**PETG:**
- Kestävämpi kuin PLA
- Parempi säänkestävyys
- Joustavampi → hyvä tiivisterakenteisiin
- **SUOSITUS** tälle projektille

**ABS:**
- Kestävä ja jäykkä
- Vaikeampi tulostaa (warping)
- Hyvä suurille kuormille

**TPU (joustavat osat):**
- Tiivisteet (jos ei käytä silikonia)
- Tärinänvaimennus
- Jalkojen pehmusteet

---

### Asetukset (PETG):

```
Nozzle: 230-250°C
Bed: 70-85°C
Infill: 30-50% (riippuu osasta)
Perimeters: 3-4
Layer height: 0.2 mm
Supports: Tarpeen mukaan
```

**Funktionaaliset osat:**
- Enemmän perimetreja (4-5)
- Korkea infill (50-100%)
- Hidas nopeus (40-50 mm/s)

---

## 📐 Suunnittelutips

1. **Toleranssit:**
   - O-renkaille: -0.2 mm uraan
   - Kierteet: +0.2 mm aukkoon
   - Liikkuvat osat: +0.3 mm välys

2. **Tiivisteet:**
   - Urat: pyöreä pohja parempi kuin kulma
   - O-rengas puristuu ~30%

3. **Kiinnikkeet:**
   - Reikä ruuveille: +0.5 mm (esim. M3 → 3.5 mm)
   - Upotuspaikat muttereille

4. **Tuuletus:**
   - Elektroniikkakoteloon aina tuuletusrakoja
   - Ø 3-5 mm reiät riittävät

5. **Vahvistus:**
   - Filletit kulmiin
   - Ripoitukset ohuiden osien alle
   - Suunta: printtaa niin että kerrokset eivät halkea rasitussuunnassa

---

## 🎯 Mitä tulostaa ensin?

**Prioriteetti:**

1. **Venttiilikiinnike** → Tarvitaan heti tiiveystestaukseen
2. **Anturikiinnikkeet** → BME280/ESP32 paikalleen
3. **Filamenttiteline** → Sisällön järjestely
4. **LED-profiilit** → Valaistus
5. **Magneettikytkimien kotelot** → Automaatio
6. **Elektroniikkakotelo** → Siisti lopputulos

---

## 📦 Valmis 3D-mallit (suositus)

**Thingiverse / Printables / GitHub:**
- Etsi: "vacuum chamber seal", "filament dry box", "linear actuator mount"
- Modifioi omiin mittoihisi

**Oma suunnittelu:**
- Fusion 360 (ilmainen hobbylle)
- FreeCAD (ilmainen, open source)
- Tinkercad (yksinkertainen, selaimessa)

---

## 💡 Yhteenveto

**Tulosta:**
✅ Kiinnikkeet, adapterit, kotelot
✅ Filamenttieline ja telineet sisällä
✅ LED-profiilit ja diffuusorit
✅ Kaapeliläpiviennit

**Osta:**
❌ Elektroniikka (ESP32, BME280, rele)
❌ Moottorit ja toimilaitteet
❌ Sähköventtiili
❌ Pumppu
❌ Metalliset saranat ja laakerit

**Säästö yhteensä:** ~100-150 € kun tulostat mahdollisimman paljon itse!
