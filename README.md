# Alipaineellinen Filamenttikotelo

![Status](https://img.shields.io/badge/status-in--progress-yellow?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-ESP32-green?style=flat-square)
![Language](https://img.shields.io/badge/language-Finnish-red?style=flat-square)

**Projekti aloitettu:** 14.1.2026  
**Tavoite:** Toimiva, kuiva ja puhdas filamenttisäilytys alipaineella

🇫🇮 Dokumentaatio suomeksi | 🇬🇧 English version coming soon

---

## 🎯 Tavoitteet

- Pitää filamentti **kuivana ja puhtaana** – ei enää poppingia tai tukoksia
- **Alipaine** estää kosteuden pääsyn koteloon
- **Helppo käyttö**: kansi auki → rulla vaihtoon → kansi kiinni → alipaine päälle
- **Automaattinen seuranta**: ESP32 + paineanturi näyttää, pitääkö kotelo

---

## 📋 Pääkomponentit

1. **Tiivis laatikko**
   - Silikoninauha tiivisteenä (1 mm pyöreä, Shore A 40-60)
   - Ura 0.5-0.7 mm syvä, nauha nousee 0.3-0.4 mm
   
2. **Alipainejärjestelmä**
   - Alipaineventtiili (Schrader / pikaliitin)
   - Käsipumppu tai 12V vakuumipumppu
   - Tavoite: -20...-50 kPa
   
3. **Automaatio (valinnainen)**
   - ESP32 + paineanturi (BMP280 / MPX5100)
   - Web UI paineen seurantaan
   - Automaattinen pumppuohjaus

4. **Filamentin läpivienti (valinnainen)**
   - PTFE-putki + O-rengas
   - Bulkhead-liitin tai 3D-printattu ratkaisu

---

## 📁 Projektin rakenne

```
Filament Storage/
├── README.md              # Tämä tiedosto - projektin yleiskuvaus
├── docs/
│   ├── Komponentit.md     # Tarkat komponentit, hinnat, toimittajat
│   ├── Rakenne.md         # Kokoonpano-ohjeet ja "räjäytyskuva"
│   ├── 3D-Malli.md        # Olemassa olevan 3D-mallin dokumentaatio
│   ├── Lisaominaisuudet.md # Automaatio, valaistus, efektit
│   └── Muistiinpanot.md   # Matkan varrelta opitut asiat
├── code/
│   ├── esp32_paineanturi/ # ESP32-koodi paineen mittaukseen
│   └── web_ui/            # Web-käyttöliittymä
├── 3d-models/             # CAD-mallit
│   ├── Filamenttiteline.3mf  # Koko kotelorakenne (45 osaa!)
│   ├── Autotalli.stl      # Visualisointi tilankäyttöön
│   └── Filamenttiteline.stl
├── komponentit/           # Datasheetit, tekniset tiedot
└── kuvat/                 # Valokuvat, mittapiirustukset, prototyypit
```

---

## 🚀 Kehitysvaiheet

### Vaihe 0: Olemassa oleva 3D-malli ✓
- [x] Kotelon 3D-malli on jo valmiina (Filamenttiteline.3mf)
- [x] 45 komponenttia: levyt, kulmapalat, saranat, listat
- [x] Modulaarinen CNC/laserleikattu rakenne
- [x] Mallin analysointi ja mittaus

### Vaihe 1: Valmistus ✓ (käynnissä)
- [x] **Hitsattu metallinen tukirunko** (teräs)
- [x] **Levyt jyrsitty:**
  - Runkolevyt: 3 mm peilaava muovi
  - Kansilevyt: 3 mm läpinäkyvä polykarbonaatti
- [x] Komponenttilista ja toimittajat
- [ ] **Tukirungon piirtäminen 3D-malliin** (tehty fyysisesti, ei mallissa vielä)
- [ ] Kokoonpano mekaanisesti

### Vaihe 2: Tiivistys ja testaus (seuraavana)
- [ ] Tiivisteratkaisun suunnittelu listoihin
- [ ] Saranat asennettu
- [ ] Alipaineen pitävyys testattu
- [ ] Venttiili ja pumppujärjestelmä
- [ ] ESP32-koodi paineen lukemiseen

### Vaihe 3: Lopullinen versio
- [ ] Tiivisteet asennettu ja testattu
- [ ] Elektroniikka integroitu
- [ ] Automaattinen pumppuohjaus toimii
- [ ] Dokumentointi valmiiksi

---

## 💡 Keskeiset oivallukset

1. **Tiiveys on kaikki kaikessa** – ei kannata investoida pumppuihin, jos kotelo vuotaa
2. **Alipainetta ei tarvitse olla paljoa** – -20 kPa riittää mainiosti
3. **Automaatio on "nice to have"**, mutta käsipumppu + manometri riittää alkuun
4. **Pumppu kotelon ulkopuolelle** – vähemmän lämpöä ja helpompi huoltaa
5. **Hitsattu teräsrunko** – kestävä ja jäykkä, tukee akryyli/

---

## 🤝 Osallistuminen

Projektiin osallistuminen on tervetullutta! Katso [CONTRIBUTING.md](CONTRIBUTING.md) lisätietoja varten.

**Tapoja osallistua:**
- 🐛 Raportoi bugeja
- 💡 Ehdota uusia ominaisuuksia
- 📝 Paranna dokumentaatiota
- 🔧 Kirjoita koodia
- 🎨 Suunnittele 3D-printattavia osia
- 📸 Jaa kuvia toteutuksestasi

---

## 📜 Lisenssi

Tämä projekti on lisensoitu [MIT-lisenssillä](LICENSE) - katso LICENSE-tiedosto lisätietoja varten.

---

## 🌟 Tekijät ja kiitokset

- Projekti: [@raulivirtanen](https://github.com/rauliV
- Yhteisön kontribuutiot tervetulleita!

---

## 📞 Yhteystiedot ja tuki

**Ongelmat ja kysymykset:**
- Avaa [Issue](../../issues) GitHubissa
- Katso [CONTRIBUTING.md](CONTRIBUTING.md) ohjeita varten

**Keskustelu:**
- [Discussions](../../discussions) (jos käytössä)

---

<div align="center">

**⭐ Jos projekti on hyödyllinen, anna tähtinen GitHubissa! ⭐**

Tehty ❤️:llä Suomessa 🇫🇮

</div>polykarbonaattilevyt
6. **Peilaava muovi + läpinäkyvä polykarb** – näyttävä yhdistelmä, näkee filamentit

---

## 📖 Dokumentaatio

**📋 Aloita tästä:** **[Yhteenveto.md](docs/Yhteenveto.md)** - Projektin kokonaiskuva ja rakenne

### Perustiedot:
- **[Komponentit.md](docs/Komponentit.md)** – Ostoslista hintojen ja toimittajien kanssa
- **[Rakenne.md](docs/Rakenne.md)** – Kokoonpano-ohjeet
- **[3D-Malli.md](docs/3D-Malli.md)** – 45-osaisen CAD-mallin dokumentaatio

### Automaatio:
- **[Ruuvitankomekanismi.md](docs/Ruuvitankomekanismi.md)** – DC-moottoripohjainen kannen nosto
- **[4-Moottorin-Koodi.md](docs/4-Moottorin-Koodi.md)** – Lisävoima 3-6V moottoreille
- **[Kayttoliittymat.md](docs/Kayttoliittymat.md)** – Manuaalinen OLED-UI + Web-liittymä (MQTT) 🖥️

### Lisäominaisuudet:
- **[3D-Printattavat-Osat.md](docs/3D-Printattavat-Osat.md)** – Mitä voi tulostaa itse (~€113 säästö)
- **[Aaniefektit-ja-Animaatiot.md](docs/Aaniefektit-ja-Animaatiot.md)** – Äänet ja LED-show 🎵🌈
- **[Filamenttien-Syotto-AMS.md](docs/Filamenttien-Syotto-AMS.md)** – BambuLab AMS-integraatio 🎨
- **[Lisaominaisuudet.md](docs/Lisaominaisuudet.md)** – Muut automaatio-ominaisuudet
- **[Muistiinpanot.md](docs/Muistiinpanot.md)** – Projektipäiväkirja

---

## 🛠️ Käytetyt työkalut

| Työkalu | Malli | Käyttö |
|---------|-------|--------|
| **CNC-jyrsin** | TTC450PRO | Levyjen leikkaus ja urat |
| **3D-tulostin** | BambuLab P1S | Kiinnikkeet, vaihteistot, kotelot |
| **Hitsauslaite** | (käsin) | Teräsrunko |
| **CAD** | Fusion 360 | 3D-mallinnus |

---

## 📖 Lisätiedot

Katso tarkemmat ohjeet ja komponenttilistat `docs/`-kansiosta.
