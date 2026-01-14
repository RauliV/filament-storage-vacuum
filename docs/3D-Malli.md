# 3D-Mallin dokumentaatio – Filamenttiteline.3mf

---

## 📦 Yleistiedot

**Tiedosto:** `3d-models/Filamenttiteline.3mf`  
**Alkuperäinen nimi:** sivuv5  
**Koko:** 6.9 MB  
**Komponenttien määrä:** 45 osaa  
**Kompleksisuus:** 245,869 verteksiä, 493,651 kolmiota  
**Värit:** Vaalea (#FBFAF5, #F5F5F6)

---

## 🏗️ Rakenne ja komponentit

Malli sisältää **täydellisen modulaarisen kotelorakenteen** joka on suunniteltu CNC- tai laserleikattavaksi.

### 1. Päälevyt

| Osa | Kuvaus | Huomiot |
|-----|--------|---------|
| `Pohjalevy` | Kotelon pohja | Kantava rakenne |
| `Pohjalevyn_jatke` | Pohjan jatke-osa | Mahdollisesti laajennettavuutta varten |
| `Kattolevy` | Kansi/yläosa | Avattava saranoilla |
| `Takalevy` | Takaseinä | Kiinteä |
| `SivuPeiliO` | Sivulevy oikea | Peilattu versio |
| `SivuPeiliV` | Sivulevy vasen | Peilattu versio |
| `Pinta1` | Pintaelementti 1 | Mahdollisesti etu/sisäosa |
| `Pinta2` | Pintaelementti 2 | Mahdollisesti etu/sisäosa |

**Arvioitu levypaksuus:** ~3 mm (tyypillistä vanerille/akryylille)  
**Materiaalisuositus:** Vaneri, MDF tai akryyli

---

### 2. Kulmapalat (4 kpl)

Vahvistavat kotelon kulmat ja pitävät levyt paikallaan.

| Osa | Sijainti |
|-----|----------|
| `KulmapalaOA` | Oikea alhaalla |
| `KulmapalaOY` | Oikea ylhäällä |
| `KulmapalaVA` | Vasen alhaalla |
| `KulmapalaVY` | Vasen ylhäällä |

**Huomio:** Symmetriset parit (O/V peilattu)

---

### 3. Kulmalistat ja vahvikelistat

Lisäävät jäykkyyttä ja mahdollisesti tiivisteiden kiinnitysurat.

#### Kulmalistat (peilatut):
- `KulmalistaPeiliOA` – Oikea alhaalla
- `KulmalistaPeiliOY` – Oikea ylhäällä
- `KulmalistaPeiliVA` – Vasen alhaalla
- `KulmalistaPeiliVY` – Vasen ylhäällä

#### Takakulman listat:
- `TakakulmalistaA` – Alhaalla
- `TakakulmalistaO` – Oikealla
- `TakakulmalistaV` – Vasemmalla
- `TakakulmalistaY` – Ylhäällä

#### Muut listat:
- `E-lista_profiili` – E-profiililista (mahdollisesti tiivistettä varten)

---

### 4. Reunalistat

**Rungon listat:**
- `Lista_Runko1`
- `Lista_Runko2`
- `Lista_Runko3`

**Kannen listat:**
- `ListaKansi1`
- `ListaKansi2`
- `Listakansi3`
- `ProfiiliKansiLista`

**Käyttötarkoitus:** 
- Tiivistysurat silikoninauhoille
- Kannen ja rungon kohtaamispinnat
- Lisäjäykistys

---

### 5. Saranat (kotelo on avattava!)

| Osa | Kuvaus |
|-----|--------|
| `Sarana_KansiO` | Kannen sarana oikea |
| `Sarana_KansiV` | Kannen sarana vasen |
| `Sarana_runko_Jungfrau` | Rungon sarana 1 |
| `Sarana_RunkoDrago` | Rungon sarana 2 |
| `SaranapuuO` | Saranapuu oikea |
| `SaranaPuuV` | Saranapuu vasen |

**Huomio:** Mahdollisesti 3D-printattavat tai CNC-jyrsittävät saranakiinnikkeet

---

### 6. Muut komponentit

- `Body85`, `Body87` – Mahdollisesti liitokset tai vahvikkeet
- `Body119`, `Body121` – Lisäosat
- `Body319`, `Body320` – Lisäosat

**Huomio:** Näiden tarkoitus selviää tarkemmasta analyysistä tai alkuperäisistä suunnitelmista

---

## 📐 Mitat (arvioitu)

Mallin verteksien perusteella:

- **Leveys (X):** ~237-240 mm
- **Korkeus (Z):** ~425 mm
- **Syvyys (Y):** Vaihtelee osittain, levyt ~1.5-3 mm

**Huomio:** Nämä ovat esimerkkimittoja yhdestä komponentista. Koko kotelon mitat selviävät tarkemmasta analyysistä.

---

## 🔧 Valmistus

### Suositeltu valmistustapa:

**1. CNC-jyrsintä:**
- Paksummat osat (kulmapalat, saranakiinnikkeet)
- Tarkemmat urat ja profiilit

**2. Laserleikkaus:**
- Levyt (pohja, kansi, sivut)
- Listat ja vahvikkeet
- Nopea ja tarkka

**3. 3D-printaus:**
- Saranakiinnikkeet (joustavuutta)
- Venttiilikiinnikkeet
- Erikoisosat

---

## 🔨 Kokoonpano-järjestys (ehdotus)

1. **Pohja ja kulmapalat**
   - Kiinnitä kulmapalat pohjaan
   
2. **Sivulevyt ja takalevy**
   - Asenna sivut ja taka kulmapaloihin
   
3. **Listat ja vahvikkeet**
   - Kiinnitä reunalistat
   - Lisää kulmalistat
   
4. **Saranat**
   - Asenna saranakiinnikkeet runkoon
   
5. **Kansi**
   - Liitä kansi saranoihin
   - Asenna kannen listat
   
6. **Tiivisteet ja elektroniikka**
   - Silikoninauhat listojen uriin
   - Venttiili ja anturit
   - ESP32 ja pumppujärjestelmä

---

## 🎨 Materiaalivaihtoehdot

### ✅ KÄYTÖSSÄ TÄSSÄ PROJEKTISSA:

**Tukirunko:**
- **Hitsattu teräsrunko** (ei 3D-mallissa vielä)
- Kantava rakenne joka tukee levyjä
- Jäykkä ja kestävä

**Runkolevyt (sivut, pohja, taka):**
- **3 mm peilaava muovi** (todennäköisesti akryyli tai polystyreeni)
- Heijastava pinta, ei täysin läpinäkyvä
- Suojaa valolta ja näyttää siistiltä

**Kansilevyt:**
- **3 mm läpinäkyvä polykarbonaatti**
- Iskunkestävä ja kestävä
- Läpinäkyvyys → näkee filamentit sisällä

---

### Muut vaihtoehdot (vertailua varten):

### Vaneri
- **Edut:** Halpa, helppo työstää, kestävä
- **Haitat:** Ei läpinäkyvä, vaatii pintakäsittelyn
- **Paksuus:** 3-6 mm
- **Hinta:** ~20-40 € levylle

### MDF
- **Edut:** Tasainen pinta, halpa
- **Haitat:** Ei vedenpitävä, pölisee leikatessa
- **Paksuus:** 3-6 mm
- **Hinta:** ~15-30 € levylle

### Akryyli (PMMA) - Kirkas tai peilaava
- **Edut:** Läpinäkyvä/peilaava, näyttää siistiltä, tiivis
- **Haitat:** Kalliimpi, halkeileva
- **Paksuus:** 3-5 mm
- **Hinta:** ~60-100 € levylle (riippuen koosta)

### Polykarbonaatti
- **Edut:** Iskunkestävä, läpinäkyvä, kestävä
- **Haitat:** Kallis, vaikeampi työstää
- **Paksuus:** 3-5 mm
- **Hinta:** ~80-120 € levylle

---

## 📊 Seuraavat askeleet

- [ ] Pura malli osiin ja generoi valmistuskuvat (DXF)
- [ ] Mittaa tarkat mitat jokaisesta osasta
- [ ] Määritä materiaalit ja paksuudet
- [ ] Laske materiaalimenekki ja kustannukset
- [ ] Suunnittele tiivistysurat tarkemmin
- [ ] Testaa prototyyppi (esim. kartongista)
- [ ] CNC/laserleikkaus valmistus

---

## 💡 Huomioita

- Malli on **valmis valmistettavaksi** – ei tarvitse suunnitella alusta!
- Modulaarinen rakenne → helppo modifioida
- Saranat integroitu → avattava kansi valmiina
- Listat → tiivistysurat todennäköisesti jo suunniteltu
- 45 osaa → vaatii huolellisen kokoonpanon

---

## 🖼️ Visualisointi

**Esikatselukuva:** `~/Desktop/Filamenttiteline_preview.png`  
(Kopioin 3MF-tiedoston thumbnail-kuvan työpöydälle)

Voit avata mallin esim:
- FreeCAD
- Fusion 360
- PrusaSlicer / OrcaSlicer
- Blender (Import 3MF)

---

## 🔗 Liittyvät tiedostot

- `3d-models/Filamenttiteline.3mf` – Täysi malli
- `3d-models/Filamenttiteline.stl` – Yksittäinen osa (26 KB)
- `3d-models/Autotalli.stl` – Visualisointi tilankäyttöön
- `docs/Rakenne.md` – Kokoonpano-ohjeet
- `docs/Komponentit.md` – Komponentit ja hinnat
