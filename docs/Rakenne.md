# Kotelon rakenne ja kokoonpano-ohjeet

---

## 📐 "Räjäytyskuva" – Mitä tulee minnekin

**HUOM:** Kotelon 3D-malli on jo valmiina! Katso tarkemmat tiedot [3D-Malli.md](3D-Malli.md).

```
┌─────────────────────────────────────┐
│  KATTOLEVY (avattava)               │ ← Saranat (3D-mallissa valmiina)
│  - Kannen listat 1,2,3              │
│  - ProfiiliKansiLista               │
│  - Tiivisteuran paikka              │
└─────────────────────────────────────┘
         ║ TIIVISTE (silikoninauha listoihin)
┌─────────────────────────────────────┐
│  KOTELON RUNKO (modulaarinen)       │
│  - Sivulevyt (SivuPeiliO/V)        │ ← CNC/laserleikattu
│  - Takalevy                         │
│  - Kulmapalat 4x (vahvistavat)     │
│                                     │
│  ┌─────────┐  ┌─────────┐         │ ← Filamentit
│  │ Rulla 1 │  │ Rulla 2 │         │
│  └─────────┘  └─────────┘         │
│                                     │
│  [Paineanturi]  [ESP32 + OLED]     │ ← Elektroniikka sisällä
│                                     │
│  - Pohjalevy + jatke                │
│  - Lista_Runko 1,2,3                │
└─────────────────────────────────────┘
         │                    │
   [Venttiili]          [Läpivienti] (valinnainen)
         │                    │
    Käsipumppu           PTFE-putki
    tai 12V pumppu       tulostimeen

```

**3D-malli sisältää 45 osaa:**
- Levyt: pohja, kansi, sivut, taka
- Kulmapalat ja listat
- Saranakiinnikkeet (integroitu!)
- Katso täydellinen lista: [3D-Malli.md](3D-Malli.md)

---

## 🔨 Rakennusvaiheet

### Vaihe 1: Valitse kotelo

**Vaihtoehto A: 3D-mallin mukainen CNC/laserleikattu rakenne (SUOSITUS!)**
- ✅ **3D-malli on jo valmiina!** ([3D-Malli.md](3D-Malli.md))
- 45 komponenttia modulaarisessa rakenteessa
- Saranat integroitu malliin
- Tiivistyslistat valmiina
- Materiaalit: Vaneri (3-6 mm) / Akryyli (3-5 mm)
- **Edut:** Professionaalinen, tarkka, räätälöity
- **Haitat:** Vaatii CNC/laserleikatuksen

**Vaihtoehto B: Valmis muovilaatikko (yksinkertainen)**
- IKEA SAMLA 22–45 L
- Tarkista: kansi tiukasti kiinni, tasainen reuna, tukeva rakenne
- **Edut:** Nopea, halpa, helppo
- **Haitat:** Ei räätälöity, geneerinen

**Vaihtoehto C: 3D-printattu kotelo**
- Paksut seinät (4–5 perimetriä)
- Korkea infill (> 60 %)
- Suuri printtivolyymi (voi vaatia useita osia)
- Materiaalit: PETG (vedenpitävämpi kuin PLA)

**Vaihtoehto D: Puulaatikko + muovipinnoite**
- Vanerilaatikko, sisällä muovikalvo / epoksipinnoite
- Tiivis, mutta työlääs

---

### Vaihe 2: Tiiviste

**Tiivisteen asennus:**

1. **Mittaa kehä:**
   - Mittaa kotelon reunan kehä + 5 cm ylimääräistä
   - Esim. 50 × 40 cm laatikko → kehä ~180 cm

2. **Tee ura (jos mahdollista):**
   - **Syvyys:** 0.5–0.7 mm (1 mm nauhalle)
   - **Leveys:** hieman suurempi kuin nauha (esim. 1.2 mm)
   - **Työkalu:** Dremel + jyrsinterä tai pieni veitsisaha
   - **Sijainti:** Joko kannen reunassa TAI rungon yläreunassa

3. **Asenna silikoninauha:**
   - **Ilman uraa:** Liimaa tiivisteliimalla (paikoin, ei jatkuvasti)
   - **Uralla:** Paina ura täyteen, tiiviste jää puristuksella paikalleen
   - **Jatkos:** Viistä päät 45° kulmaan, liimaa yhteen (silikonitiivisteliima)

4. **Testaa puristuma:**
   - Sulje kansi
   - Nauha puristuu noin 30 % (esim. 1 mm → 0.7 mm)
   - Pinnat eivät saa koskettaa, vain tiiviste kantaa

**Vinkki:** Jos ura ei onnistu, käytä **kaksi nauraa päällekkäin** → parempi tiivistys

---

### Vaihe 3: Alipaineventtiili

**Asennus kotelon seinään:**

1. **Valitse sijainti:**
   - Kylki tai kansi (ei pohja)
   - Riittävän ylhäällä, ettei filamentti osu
   - Helppo ylettyä pumpulla

2. **Poraa reikä:**
   - **Schrader:** Ø 8 mm
   - **Pikaliitin:** Ø 10–12 mm (liitin mallista riippuen)
   - Poraa hitaasti, älä halkeile muovia

3. **Asenna venttiili:**
   - **Schrader:** Ruuvaa läpi + mutteri molemmille puolille
   - **Pikaliitin:** Bulkhead-malli tai O-rengas + mutteri
   - **3D-printattu:** Printaa kiinnike + O-rengas tiivistämään

4. **Testaa tiiveys:**
   - Pumpaa alipainetta sisään
   - Tarkista saippualiuoksella → ei saa kuplia

---

### Vaihe 4: Filamentin läpivienti (jos haluat tulostaa suoraan kotelosta)

**Ratkaisu:**

1. **PTFE-putki läpivienti:**
   - Poraa reikä seinään (esim. Ø 6 mm)
   - Työnnä PTFE-putki läpi
   - Tiivistä:
     - **Vaihtoehto A:** O-rengas ulkopuolella + mutteri sisäpuolella
     - **Vaihtoehto B:** Pneumatiikkapikaliitin + bulkhead
     - **Vaihtoehto C:** Silikoni ympärille (ei paras, mutta yksinkertainen)

2. **Valmis bulkhead-liitin PTFE:lle:**
   - Esim. PC4-M10 liitin (pneumatiikasta)
   - Ruuvaa seinään, kiristä mutterilla
   - PTFE napsahtaa paikalleen

**Vinkki:** Jos et tulosta kotelosta, **älä tee läpivientejä** → helpompi tiivistää!

---

### Vaihe 5: Elektroniikka (valinnainen)

**Asennus kotelon sisään:**

1. **Paineanturi (BMP280):**
   - Kiinnitä sisäseinään teipillä / 3D-printatulla telineellä
   - Johda I2C-kaapelit ESP32:lle (4 johtoa: VCC, GND, SCL, SDA)

2. **ESP32 + OLED:**
   - Kiinnitä sisäseinään / kannen sisäpintaan
   - OLED näkyy ikkunan läpi (tai poraa pieni ikkuna koteloon)

3. **Kaapelit ulos (jos pumppu on ulkona):**
   - Poraa pieni reikä + läpivienti kaapelille
   - Tiivistä silikonitiivisteellä

4. **Virtalähde:**
   - 12V virtalähde pumppulle + buck-muunnin (12V → 5V) ESP32:lle
   - Vaihtoehtoisesti akku (vaatii latauspiirin)

---

### Vaihe 6: Pumppujärjestelmä

**Vaihtoehto A: Käsipumppu**
- Liitä pumppu venttiiliin (tarvittaessa sovitin)
- Pumpata kunnes manometri näyttää -20...-50 kPa
- Irrota pumppu (venttiili pitää paineen)

**Vaihtoehto B: 12V vakuumipumppu**
- Asenna pumppu **kotelon ulkopuolelle** (vähemmän lämpöä)
- Liitä pumppu venttiiliin letkulla (esim. 6 mm silikoniletkulla)
- Lisää **takaiskuventtiili** pumpun ja kotelon väliin (estää paineen paluun)
- Ohjaa pumppua releellä (ESP32 → rele → pumppu)

**Logiikka:**
```
Jos paine > -15 kPa:
  → Pumppu päälle
Jos paine < -30 kPa:
  → Pumppu pois
```

---

### Vaihe 7: Testaus

**Tiiveyden testaus:**

1. **Pumpata alipainetta sisään** (-20 kPa)
2. **Odottaa 1 tunti**
3. **Mitata paine uudestaan:**
   - Jos < 10 % muutos → hyvä tiiveys
   - Jos > 20 % muutos → vuotaa, etsi vuotokohdat

**Vuotojen etsiminen:**
- **Saippualiuos** venttiiliin ja saumoihin → kuplii jos vuotaa
- **Veden alla testi** (jos kotelo sopivan pieni)
- **Äänellä:** Kuuluu "psss" jos iso vuoto

**Pitkäaikaistestaus:**
- Jätä kotelo alipaineen alle 1 viikoksi
- Logaa paine ESP32:lla → näet kuvaajan paineen muutoksesta

---

## 🧠 Tärkeät oivallukset ja vinkit

### Tiivistys

- **Pinta ratkaisee:** Tasaisempi pinta = parempi tiiveys
- **Puristuma ei saa olla liikaa:** Jos pinta joustaa, tiiviste painuu sisään eikä tiivistä
- **Jatkuva lenkki parempi kuin pätkät:** Minimoi vuotokohdat

### Alipaine

- **Ei tarvitse olla paljoa:** -20 kPa riittää erinomaisesti
- **Tärkeintä on pitävyys:** Pumppu ei saa käydä jatkuvasti
- **Venttiili oikeaan paikkaan:** Ei liian alas (filamentti ei saa tukkia)

### Käytännön vinkki

- **Helppo avata:** Lisää nuppi / kahva kanteen
- **Läpinäkyvä kotelo:** Näet filamentit ilman avaamista
- **Rullatelineet:** Älä anna rullien liikkua vapaasti → 3D-printaa teline

---

## 🔄 Huoltotoimenpiteet

**Säännöllinen tarkastus:**
- Tarkista tiivisteet 1× / 3 kk → vaihda jos kuluneet
- Puhdista venttiili tarvittaessa
- Tarkista pumpun suodatin (jos sellainen on)

**Pitkäaikainen:**
- Silikoninauha kestää vuosia, mutta aurinko ja öljyt heikentävät
- ESP32 kestää loputtomiin sisätilassa

---

## 📸 Dokumentoi matkan varrella!

Ota kuvia ja tallenna `kuvat/`-kansioon:
- Tiivisteen asennus
- Venttiilikiinnitys
- Valmis kotelo
- Elektroniikan kytkennät

→ Auttaa myöhemmin kun teet version 2.0 tai joku muu haluaa kopioida!
