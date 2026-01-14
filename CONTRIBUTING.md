# Osallistuminen projektiin / Contributing

Kiitos kiinnostuksestasi projektia kohtaan! Kaikki osallistuminen on tervetullutta – olipa kyse sitten bugien raportoinnista, uusista ominaisuuksista, dokumentaation parantamisesta tai koodin kirjoittamisesta.

---

## 🐛 Bugien raportointi

Jos löydät bugin tai ongelman:

1. **Tarkista ensin** onko ongelma jo raportoitu [Issues](../../issues)-osiossa
2. **Luo uusi Issue** jos ei löydy
3. **Sisällytä seuraavat tiedot:**
   - Selkeä kuvaus ongelmasta
   - Mitä odotit tapahtuvan vs. mitä tapahtui
   - Vaiheet ongelman toistamiseksi
   - Käyttämäsi komponentit (ESP32-malli, anturit jne.)
   - Koodin versio tai commit-hash
   - Kuvakaappaukset tai videot (jos mahdollista)
   - Serial Monitor -output (ESP32-koodi)

**Esimerkki hyvästä bug-raportista:**
```
Otsikko: Pumppu ei sammuu kun tavoitepaine saavutettu

Kuvaus:
- ESP32 DevKit V1, BME280, 12V vakuumipumppu
- Koodi versio: commit abc1234
- Tavoitepaine asetettu -25 kPa
- Pumppu käynnistyy OK, mutta ei sammu vaikka paine on -27 kPa
- Serial output näyttää: "Paine: -27.5 kPa | Pumppu: ON"

Odotettu toiminta: Pumpun pitäisi sammua kun paine < -28 kPa
```

---

## 💡 Uusien ominaisuuksien ehdottaminen

Ideat ovat tervetulleita!

1. **Avaa Issue** otsikolla "Feature: [ominaisuuden nimi]"
2. **Kuvaile:**
   - Mitä ominaisuutta ehdotat
   - Miksi se olisi hyödyllinen
   - Miten se toimisi (jos sinulla on visio)
   - Mahdolliset komponentit tai teknologiat
3. **Keskustele** – muut voivat antaa palautetta

**Esimerkkejä hyvistä ehdotuksista:**
- "Feature: MQTT-integraatio Home Assistantiin"
- "Feature: Akustinen hälytys kun kosteus > 70%"
- "Feature: Mobiilisovellus (Bluetooth)"

---

## 📝 Dokumentaation parantaminen

Dokumentaatio on tärkeä osa projektia!

**Voit auttaa:**
- Korjaamalla kirjoitusvirheitä tai epäselviä kohtia
- Lisäämällä puuttuvia ohjeita
- Parantamalla selityksiä
- Lisäämällä kuvia tai kaavioita
- Kääntämällä dokumentteja englanniksi (tai muille kielille)

**Pull Request -prosessi:**
1. Forkkaa repo
2. Tee muutokset
3. Lähetä PR selkeällä kuvauksella mitä muutit ja miksi

---

## 🔧 Koodin osallistuminen

### Ennen kuin aloitat:

1. **Keskustele** – avaa Issue ennen isoja muutoksia
2. **Testaa** – varmista että koodi toimii ESP32:lla
3. **Dokumentoi** – päivitä dokumentaatio tarvittaessa

---

### Koodityyli (ESP32 Arduino-koodi)

**Nimeämiskäytännöt:**
```cpp
// Vakiot: ISOT_KIRJAIMET
const int LED_PIN = 13;
const float PRESSURE_TARGET = -25.0;

// Muuttujat: camelCase
float currentPressure = 0;
bool pumpState = false;

// Funktiot: camelCase
void readSensors() { }
void updateDisplay() { }

// Kommentit: suomi tai englanti, selkeät
// Lue paineanturi ja päivitä historia
readSensors();
```

**Kommentointi:**
- Selitä **MIKSI**, ei mitä koodi tekee (se näkyy koodista)
- Dokumentoi monimutkaiset algoritmit
- Lisää kommentit pinneille ja vakioille

**Esimerkki:**
```cpp
// Hystereesin leveys estää pumppua käymästä jatkuvasti
// kun paine heiluu tavoitteen ympärillä
const float PRESSURE_HYSTERESIS = 3.0;
```

---

### Testaus

**Ennen Pull Requestia:**
1. **Käännä koodi** Arduino IDE:ssä → ei virheitä
2. **Lataa ESP32:lle** ja testaa toiminta
3. **Tarkista Serial Monitor** → ei odottamattomia viestejä
4. **Testaa web UI** → toimiiko kaikki painikkeet
5. **Testaa eri tilanteissa:**
   - Kansi auki/kiinni
   - Hälytystilanteet
   - Pumpun ohjaus

**Jos lisäät uuden anturin:**
- Dokumentoi kytkentä [code/README.md](code/README.md)
- Lisää komponentti [docs/Komponentit.md](docs/Komponentit.md)
- Päivitä pääasetukset koodissa

---

### Pull Request -prosessi

1. **Forkkaa** tämä repo
2. **Luo uusi branch:**
   ```bash
   git checkout -b feature/ominaisuuden-nimi
   ```
3. **Tee muutokset** ja committaa:
   ```bash
   git commit -m "Lisää MQTT-tuki paineen lähettämiseen"
   ```
4. **Push** omaan forkkiisi:
   ```bash
   git push origin feature/ominaisuuden-nimi
   ```
5. **Luo Pull Request** GitHubissa
6. **Kuvaile PR:ssä:**
   - Mitä muutit
   - Miksi
   - Miten testasit
   - Mitkä komponentit tarvitaan (jos uusia)

**PR-otsikon muoto:**
- `feat: Lisää MQTT-tuki`
- `fix: Korjaa pumpun sammuminen`
- `docs: Päivitä komponenttilista`
- `refactor: Siisti LED-animaatiot`

---

## 🎨 3D-mallien ja CAD-tiedostojen osallistuminen

Jos suunnittelet 3D-printattavia osia:

1. **Tallenna sekä lähdetiedosto että STL/3MF:**
   - Lähde: `.f3d` (Fusion 360), `.FCStd` (FreeCAD)
   - Export: `.stl` tai `.3mf`
2. **Dokumentoi:**
   - Mitat ja toleranssit
   - Suositellut tulostusasetukset
   - Materiaalit
3. **Lisää [docs/3D-Printattavat-Osat.md](docs/3D-Printattavat-Osat.md)**
4. **Liitä kuvia** onnistuneista printeistä

---

## 📸 Kuvien lisääminen

Kuvat ovat tervetulleita!

**Mihin:**
- `kuvat/rakenne/` – Kokoonpanokuvat
- `kuvat/elektroniikka/` – Kytkennät
- `kuvat/valmis/` – Lopputulos

**Muoto:**
- JPG kuville (pienennetty ~1920px leveä)
- PNG kaavioille ja piirustuksille
- Nimeä kuvaavasti: `esp32_kytkenta.jpg`, `valmis_kotelo_01.jpg`

---

## 🌍 Kieliversiot

Tällä hetkellä dokumentaatio on **suomeksi**, mutta englanninkieliset käännökset ovat tervetulleita!

**Jos haluat kääntää:**
1. Luo uusi kansio: `docs/en/`
2. Käännä dokumentit
3. Lähetä PR
4. Päivitä README.md linkittämään käännöksiin

---

## ❓ Kysymykset ja apu

**Tarvitsetko apua?**
- Avaa [Discussion](../../discussions) (jos käytössä)
- Tai luo Issue otsikolla "Question: [aihe]"
- Yhteisö auttaa mielellään!

---

## 📋 Checklist ennen PR:ää

- [ ] Koodi kääntyy ilman virheitä
- [ ] Testattu ESP32:lla (jos koodimuutos)
- [ ] Dokumentaatio päivitetty
- [ ] Kommentit lisätty (jos tarpeen)
- [ ] Commit-viestit selkeitä
- [ ] PR-kuvaus sisältää kaiken tarvittavan

---

## 🎉 Kiitos osallistumisesta!

Jokainen panos – oli se sitten pieni tai iso – auttaa tekemään projektista paremman. Tervetuloa mukaan! 🚀

---

## 📜 Lisenssi

Osallistumalla projektiin hyväksyt että kontribuutiosi julkaistaan [MIT-lisenssillä](LICENSE).
