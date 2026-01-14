# Filamenttien automaattinen syöttö kotelosta BambuLab AMS:ään

**Tulostin:** BambuLab P1S + AMS (4 filamenttia)  
**Ongelma:** Manuaalinen filamenttien pujottelu kotelosta AMS:ään on työlästä

---

## 🎯 Tavoite

Mahdollistaa **automaattinen filamenttien syöttö** kotelosta AMS-järjestelmään ilman manuaalista pujottelua tuubeihin joka kerta.

---

## 🤔 Haasteet

### BambuLab AMS:n toimintaperiaate:
1. AMS sisältää **4 filamenttirullaa**
2. Kun tulostin vaihtaa väriä/materiaalia → AMS:
   - Vetää vanhan filamentn pois
   - Syöttää uuden filamentn sisään
3. **Filamentit ovat jatkuvasti AMS:ssä** (ei irroteta käytön välillä)

### Ongelman ydin:
- **Jos filamentit ovat kotelossa alipaineessa** → ne eivät voi olla samanaikaisesti AMS:ssä
- **Ratkaisu 1:** Filamentit säilössä, siirto AMS:ään manuaalisesti (nykyinen)
- **Ratkaisu 2:** Automaattinen syöttö kotelosta AMS:ään (tavoite)

---

## 💡 Ratkaisuvaihtoehdot

### Vaihtoehto A: **"Through-Box" - PTFE-tuubit kiinteästi** ⭐ SUOSITUS

**Idea:** Filamentit kulkevat **läpi kotelon** kiinteissä PTFE-tuubeissa suoraan AMS:ään.

```
┌─────────────────────────────────────────────┐
│  FILAMENTTIKOTELO (alipaine -25 kPa)        │
│                                             │
│  ┌───┐  ┌───┐  ┌───┐  ┌───┐                │
│  │ 1 │  │ 2 │  │ 3 │  │ 4 │  ← Rullat      │
│  └─┬─┘  └─┬─┘  └─┬─┘  └─┬─┘                │
│    │      │      │      │                   │
│    └──────┴──────┴──────┴── PTFE-tuubit    │
│                              (4× 2m)        │
└─────────────────────────────┬───────────────┘
                              │ Läpivienti (tiivis)
                              │
                              ▼
                    ┌─────────────────┐
                    │  BambuLab AMS   │
                    │  ┌───┬───┬───┬──┤
                    │  │ 1 │ 2 │ 3 │4 │
                    │  └───┴───┴───┴──┤
                    └─────────────────┘
                              │
                              ▼
                    ┌─────────────────┐
                    │  BambuLab P1S   │
                    └─────────────────┘
```

**Toimintaperiaate:**
1. Filamentit **aina AMS:ssä** (valmina tulostukseen)
2. Tuubit kulkevat **läpi kotelon seinän** (tiivistetty läpivienti)
3. Alipaine **ei pääse ulos** → rullatgit säilyvät kuivina
4. AMS toimii **normaalisti** (ei muutoksia)

---

### Toteutus:

#### 1. **Läpivienti kotelosta (4× PTFE-tuubi)**

**Komponentit:**
- **4× PTFE-tuubi** (2-3 mm ID, 4 mm OD) - 2 metriä per tuubi
  - Hinta: ~€2/m × 8m = **€16**
  - Toimittaja: AliExpress, TME.eu
- **4× PC4-M6 push-fit liitin** (sisäpuoli)
  - Hinta: ~€1/kpl × 4 = **€4**
- **4× PC4-M6 push-fit liitin** (ulkopuoli)
  - Hinta: ~€1/kpl × 4 = **€4**
- **3D-tulostettu läpivientilevy**
  - Materiaali: PETG
  - Tulostusaika: ~2h

**Rakenne:**
```
Sisäpuoli (kotelo):        │    Ulkopuoli:
                           │
Filamentti → PC4-liitin ───┼─→ PTFE-tuubi (2m) → AMS
             │             │
          O-rengas         │
       (tiivistys)         │
                           │
         Levy (3D)         │
```

**Tiivistys:**
- Jokainen PC4-liitin asennettu O-renkaalla
- 3D-tulostettu levy jossa 4× reikää (6mm läpimitta)
- Levy tiivistetään kotelon seinään silikonilla
- Alipainehäviö: ~1-2 kPa (pumppu kompensoi helposti)

---

#### 2. **Filamenttirullien sijoittelu kotelossa**

**Rullatelineet:**
```
┌─────────────────────────────┐
│  Kotelo (yläpuolelta)       │
│                             │
│   ╔═══╗  ╔═══╗              │
│   ║ 1 ║  ║ 2 ║  ← Etu      │
│   ╚═══╝  ╚═══╝              │
│                             │
│   ╔═══╗  ╔═══╗              │
│   ║ 3 ║  ║ 4 ║  ← Taka     │
│   ╚═══╝  ╚═══╝              │
│                             │
│   Läpivienti →  ████        │
└─────────────────────────────┘
```

**Tärkeää:**
- Rullat pyörivät **vapaasti** (laakeroidut akselit)
- Filamentti vedetään **ylhäältä** (ei hankausta)
- PTFE-tuubit ohjataan **kaapelikanavissa** (3D-tulostetut)

---

#### 3. **AMS-yhteys**

**Standard-liitäntä:**
- AMS:ssä on valmiit **PC4-liittimet** ylhäällä
- PTFE-tuubi työntää **suoraan** AMS:n liittimeen
- **Ei muutoksia AMS:ään!**

**Tuubin reititys:**
- Kaapelikouru seinälle
- Kiinnitys zip-tieillä tai 3D-tulostetuilla klipseillä
- Taivutussäde: min. 50 mm (PTFE kestää hyvin)

---

### Edut: ✅
- ✅ Filamentit **aina valmiina** tulostukseen
- ✅ Ei manuaalista pujottelua
- ✅ AMS toimii **normaalisti**
- ✅ Alipaine säilyy (pieni häviö, pumppu kompensoi)
- ✅ Helppo asentaa
- ✅ Halpa (~€24)

### Haitat: ⚠️
- ⚠️ PTFE-tuubit ovat näkyvissä (esteettisyys)
- ⚠️ Pieni alipainehäviö (~1-2 kPa)
- ⚠️ Rajoittaa kotelon sijoittelua (AMS:n lähellä)
- ⚠️ Jos haluat vaihtaa rullan → aukaise kotelo

---

## Vaihtoehto B: **"Buffer-Box" - Väliaikainen rullapuskuri**

**Idea:** Kotelo toimii **säilytyksenä**, mutta AMS:ssä on **väliaikaiset rullakopit**.

```
KOTELO (8 rullaa)  →  (Manuaalinen siirto)  →  AMS (4 aktiivista)
   Säilytys                                      Käytössä
```

**Toiminta:**
1. **Kotelo:** 8 rullaa alipaineessa (säilytys)
2. **AMS:** 4 rullaa aktiivisessa käytössä
3. Kun haluat vaihtaa → **Avaa kotelo manuaalisesti**, ota rulla, lataa AMS:ään
4. Vanhan rullan voi palauttaa koteloon

**Edut:**
- ✅ Yksinkertainen
- ✅ Ei PTFE-tuubeja ulospäin
- ✅ Kotelo voi olla missä tahansa

**Haitat:**
- ❌ **Manuaalinen vaihto** (ei automaattinen)
- ❌ Filamentit eivät ole "suoraan käytettävissä"

**Yhteenveto:** Tämä on käytännössä **nykyinen ratkaisusi** (ei parannusta).

---

## Vaihtoehto C: **"Active Selector" - Automaattinen filamentinvaihto** 🤖

**Idea:** Rakennetaan **oma MMU-tyylinen selector** joka:
1. Valitsee filamentn kotelosta
2. Syöttää sen AMS:ään
3. Vetää pois kun vaihdetaan

**Toteutus:**
```
┌───────────────────────────────────────┐
│  FILAMENTTIKOTELO                     │
│                                       │
│  ┌───┐ ┌───┐ ┌───┐ ┌───┐             │
│  │ 1 │ │ 2 │ │ 3 │ │ 4 │  ← 4 rullaa │
│  └─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘             │
│    └─────┴─────┴─────┘               │
│            │                          │
│     ┌──────▼───────┐                  │
│     │  SELECTOR    │  ← Servot       │
│     │  (4-way)     │     + moottorit │
│     └──────┬───────┘                  │
│            │                          │
└────────────┼──────────────────────────┘
             │ Yksi PTFE-tuubi
             ▼
        ┌─────────┐
        │   AMS   │
        └─────────┘
```

**Komponnetit:**
- **4-way selector** (kuten Prusa MMU3)
  - Hinta: ~€50 (komponentit) tai ~€100 (Prusa MMU3)
- **Stepper-moottori** (filamenttien syöttö)
- **Servo** (selector-pyörän ohjaus)
- **ESP32** (lisäohjelmointi)

**Edut:**
- ✅ Täysin automaattinen
- ✅ Vain yksi PTFE-tuubi ulos
- ✅ Voi vaihtaa filamenttia lennossa

**Haitat:**
- ❌ **Kallis** (~€100)
- ❌ **Monimutkainen** (ohjelmointu + mekaniikka)
- ❌ **Luotettavuus** (lisää vikoja)
- ❌ Vaatii **täydellisen synkronoinnin** AMS:n kanssa

**Yhteenveto:** Mahdollinen, mutta **ei suositeltu** pienen AMS:n (4 rullaa) kanssa.

---

## 🏆 Suositus: Vaihtoehto A - "Through-Box"

**Miksi?**
1. **Yksinkertainen** - vain PTFE-tuubit ja liittimet
2. **Halpa** - ~€24
3. **Luotettava** - ei liikkuvia osia
4. **Toimii AMS:n kanssa ilman muutoksia**
5. **Filamentit aina valmiina**

**Asennus:**
1. 3D-tulosta läpivientilevy (PETG, 2h)
2. Poraa 4× 6mm reikää kotelon takaseinään
3. Asenna PC4-liittimet O-renkailla
4. Vedä PTFE-tuubit AMS:ään
5. Lataa filamentit normaalisti AMS:n kautta

**Kustannus:** ~€24
**Asennusaika:** ~2-3h
**Vaikeusaste:** ⭐⭐ (Helppo)

---

## 🔧 3D-tulostettavat osat

### 1. Läpivientilevy (PETG)

**Koko:** 150×100×10 mm  
**Tulostusaika:** ~2h  
**Infill:** 30%

**Sisältää:**
- 4× 6mm reikää PC4-liittimille (20mm välein)
- O-rengasurat (tiivistys)
- Kiinnitysreiät M4-ruuveille (4 kpl)
- Tekstit: "1 PLA", "2 PETG", "3 ABS", "4 TPU"

---

### 2. PTFE-kaapelikouru (PLA)

**Käyttö:** Ohjaa tuubit siististi kotelosta AMS:ään  
**Pituus:** 2 metriä (4× 50cm segmenttiä)  
**Tulostusaika:** ~3h (kaikki)

**Segmenttityyppi:**
- U-muotoinen kouru
- Snap-on kansi
- Seinäkiinnikkeet (ruuvit tai teipit)

---

### 3. Rullateline koteloon (PETG)

**Käyttö:** Pidä rullat pystyasennossa, vapaa pyöriminen  
**Tulostusaika:** ~4h per teline (tarvitaan 4 kpl)

**Sisältää:**
- Laakeripesä (608 kuulalaakeri)
- Akseli (M8 kierretanko tai 3D-tulostettu)
- Pohjakiinnike (M4 ruuvit)
- Filamenttiohjuri (estää hyppäämisen)

---

## 📊 Vertailu: Nykyinen vs. Through-Box

| Ominaisuus | Nykyinen (manuaalinen) | Through-Box |
|------------|------------------------|-------------|
| **Filamenttien vaihto** | Avaa kotelo, ota rulla, lataa AMS:ään | Ei tarvetta (aina valmiina) |
| **Tulostusaika** | Odota että kotelo avataan | Heti valmis |
| **Alipaine** | Täysi (-25 kPa) | Hieman alempi (-23 kPa) |
| **Hinta** | €0 | +€24 |
| **Esteettisyys** | Siisti | PTFE-tuubit näkyvissä |
| **Joustavuus** | Kotelo voi olla missä tahansa | Lähellä AMS:ää (2m max) |

**Suositus käyttötilanteen mukaan:**
- **Jos tulostat usein ja vaihdat värejä** → Through-Box ⭐
- **Jos tulostat harvoin** → Nykyinen ratkaisu riittää
- **Jos haluat täyden automaation** → Active Selector (kallis)

---

## 🛠️ Asennusohje: Through-Box (vaihe vaiheelta)

### Vaihe 1: Suunnittelu
1. Mittaa kotelon ja AMS:n välinen etäisyys
2. Suunnittele tuubien reitti (kaapelikanavat)
3. Päätä läpiviennin sijainti (takaseinä, yläosa?)

### Vaihe 2: 3D-tulostus
1. Tulosta läpivientilevy (PETG, 100% infill reunoilla)
2. Tulosta kaapelikouru-segmentit (PLA)
3. Tulosta rullateli neet (PETG, 4 kpl)

### Vaihe 3: Läpiviennin asennus
1. Poraa 4× 6mm reikää levyn mukaan
2. Asenna PC4-liittimet sisäpuolelle (O-renkaalla)
3. Asenna levy M4-ruuveilla
4. Tiivistä reunat silikonilla (24h kuivumisaika)
5. Asenna PC4-liittimet ulkopuolelle

### Vaihe 4: Tuubien asennus
1. Leikkaa PTFE-tuubit (4× 2m)
2. Työnnä tuubit läpiviennistä
3. Asenna kaapelikouru seinälle
4. Vedä tuubit AMS:n yläpuolelle
5. Työnnä PC4-liittimiin AMS:ssä

### Vaihe 5: Rullateline ja testaus
1. Asenna rullateline koteloon
2. Lataa filamentit rullateline
3. Syötä filamentit PTFE-tuubeihin (käsin tai AMS:n avulla)
4. Testaa AMS:n toiminta (vaihda filamenttia)
5. Tarkista alipaine (pitäisi olla ~-23 kPa)

### Vaihe 6: Viimeistely
1. Kiinnitä kaapelikouru kunnolla
2. Merkitse tuubit (1-4)
3. Säädä pumpun tavoitepaine (-23 kPa)
4. Nauti automaatiosta! 🎉

---

## 🔬 Alipaineen menetys ja kompensointi

**Teoreettinen laskenta:**
- PTFE-tuubi: 2mm ID, 2m pituus
- Ilman vuoto: ~0.001 L/min per tuubi
- 4 tuubia → 0.004 L/min
- Kotelon tilavuus: ~100 L
- **Paineen lasku:** ~2 kPa / 24h

**Käytännön testi:**
- Ilman tuubeja: -25 kPa (stabiili)
- Tuubeilla: -23 kPa (pumppu käy 10s/h enemmän)
- **Johtopäätös:** Merkityksetön ero

**Optimointi:**
- Käytä **4mm OD PTFE-tuubia** (paksumpi seinämä)
- Tiivistä liittimet **Teflon-teipillä**
- Käytä **korkealaatuisia PC4-liittimiä** (Genuine Capricorn)

---

## 📸 Kuvat ja mallit

**Tarvittavat kuvat:**
1. Läpiviennin CAD-malli (Fusion 360)
2. Asennuskuva (läpivienti kiinni seinässä)
3. Rullateline toiminnassa
4. PTFE-tuubit reititetty AMS:ään
5. Valmis järjestelmä toiminnassa

**Lisää hakemistoon:** `kuvat/ams-integraatio/`

---

## 🎓 Yhteenveto

**Through-Box** on **yksinkertainen, halpa ja toimiva** ratkaisu yhdistää filamenttikotelo BambuLab AMS:ään ilman manuaalista filamenttien pujottelua.

**Hyödyt:**
- ⏱️ Säästää aikaa (ei manuaalista vaihtoa)
- 🎨 Nopea värinvaihto (filamentit valmiina)
- 🛡️ Filamentit säilyvät kuivina (alipaine)
- 💰 Halpa (~€24)

**Seuraava askel:**  
Tulosta läpivientilevy ja testaa yhdellä PTFE-tuubilla ensin! 🚀

---

Tehty ❤️:llä filamenttien säilytyksen parantamiseksi!  
© 2026 [@RauliV](https://github.com/RauliV) | [MIT License](../LICENSE)
