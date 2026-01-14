# Muistiinpanot ja oivallukset

Projektin aikana opittuja asioita ja hyödyllisiä huomioita.

---

## 📅 14.1.2026 - Projekti aloitettu / Dokumentointi aloitettu

### Nykyinen tilanne:
**Rakenne fyysisesti rakenteilla:**
- ✅ Hitsattu teräsrunko (kantava rakenne)
- ✅ Levyt jyrsitty:
  - Runkolevyt: 3 mm peilaava muovi
  - Kansilevyt: 3 mm läpinäkyvä polykarbonaatti
- ✅ 3D-malli olemassa (Filamenttiteline.3mf, 45 osaa)
- ⏳ Kokoonpano käynnissä
- ❌ Tukirunkoa ei piirretty 3D-malliin (hitsattu ensin, piirretään jälkikäteen)

### Materiaalivalinnat:
- Tukirunko: Hitsattu teräs
- Runko: 3 mm peilaava muovi (akryyli/polystyreeni)
- Kansi: 3 mm läpinäkyvä polykarbonaatti
- Yhdistelmä: Näyttävä ja kestävä

### Päätökset:
- BMP280 paineanturi (halpa ja riittävän tarkka)
- ESP32 + Web UI automaatioon
- Silikoninauha tiivisteenä

### Seuraavat askeleet:
1. ~~Tilaa komponentit~~ → Levyt ja runko jo tehty!
2. Kokoonpano mekaanisesti
3. Suunnittele tiivistysurat listoihin
4. Testaa tiiveys
5. Asenna venttiili ja elektroniikka
6. Rakenna ja testaa!

---

## Hyödyllisiä linkkejä

- [BMP280 Datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmp280-ds001.pdf)
- [ESP32 Pinout](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
- [Adafruit BMP280 Tutorial](https://learn.adafruit.com/adafruit-bmp280-barometric-pressure-plus-temperature-sensor-breakout)

---

## Testaukset

### Tiiveyden testaus
*Täydennä kun testaat:*
- Millä alipainetasolla?
- Kuinka kauan piti?
- Mistä vuosi (jos vuosi)?

### Pumppusuorituskyky
*Täydennä:*
- Kuinka kauan kesti saavuttaa -20 kPa?
- Melutaso?

---

## Kustannukset

*Täydennä kun tilaat:*
- Komponentit yhteensä: ___ €
- Toimitusmaksut: ___ €
- **TOTAL:** ___ €

---

## Ideoita versio 2.0

- [ ] Useampi kotelo sarjaan (jaettu alipaine)
- [ ] Filamenttien RFID-tunnistus
- [ ] Lämmitys + kuivaussilikageel
- [ ] Kotiautomaatio (Home Assistant / MQTT)
