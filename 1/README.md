# 1. Redukce barevného prostoru

## Prerekvizita
- Přednáška č. 2 - Redukce barevneho prostoru, barevný a monochromatický obraz

## Bodované úkoly
- Implementací funkcí pro čtení a zápis do frame bufferu (0.5 bodu)
- Implementace převodu barevného obrazu na šedotónový (0.5 bodu)
- Implementace převodu na černobílý obraz pomocí maticového rozptýlení (1 bod)
- Implementace distribuce chyby metodou Floyd-Steinberg (1 bod)

## Ovládání aplikace
- Levé kliknutí myši
  * Vypíše na konzoli hodnotu daného pixelu
  * Závisí na funkci **getPixel()**
- Klávesa **L**
  * Nahraje testovací obrázek umístěný v /data/image.bmp
  * Závisí na funkci **putPixel()**
- Klávesa **S**
  * Uloží současné okno do souboru /data/out.bmp
  * Závisí na funkci **getPixel()**
- Klávesa **G**
  * Převede obraz do stupňů šedi
  * Závisí na funkci **getPixel()** a **putPixel()**
- Klávesy **1..4**
  * Převedou obraz na černobílý pomocí prahování s prahy (50, 100, 150, 200)
  * Závisí na funkci **getPixel()** a **putPixel()**, případně **greyScale()**
- Klávesa **R**
  * Převede obraz na černobílý pomocí metody náhodného rozptýlení
  * Závisí na funkci **getPixel()**, **putPixel()** a **greyScale()**
- Klávesa **M**
  * Převede obraz na černobílý pomocí maticového rozptýlení
  * Závisí na funkci **getPixel()** a **putPixel()**, případně **greyScale()**
- Klávesa **D**
  * Převede obraz na černobílý pomocí prahování s distribucí chyby
  * Závisí na funkci **getPixel()** a **putPixel()**, případně **greyScale()**
