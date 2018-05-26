# 5. 3D transformace

## Osnova cvičení
- Použití transformačních matic pro translaci a rotaci
- Perspektivní projekce s využitím tranformační matice
- Princip vykreslení scény (skládání transformací a jejich pořadí)

## Bodované úkoly
- Implementace zahazování odvrácených trojúhelníků před vykreslením (tzv. back-face culling):
  * Soubor **student.cpp**: void **ProjectTriangle**(...); (1 bod)
- Vykreslení druhého objektu souměrně podle modrého "zrcadla" oproti prvnímu objektu, důležité je zrcadlové chování posunů a rotací:
  * Soubor **student.cpp**: void **DrawScene**(...); (2 body)

## Ovládání aplikace
- Při **spuštění** je předán jako první **parametr** soubor obsahující model
  * Vykreslení příslušného modelu jako hlavního objektu (implicitně cylinder.tri)
  * Na výběr: **cylinder.tri**, **sphere.tri**, **bunny.tri** či vlastní model
- **Stisknutí levého tlačítka myši** a současné **tažení kurzorem**
  * Rotace celé scény kolem jejího středu (středu zrcadla)
- **Stisknutí pravého tlačítka myši** a současné **tažení kurzorem**
  * Přibližování či oddalování středu scény (středu zrcadla) od pozorovatele
- **Stisknutí levého tlačítka myši, stisknutí klávesy CTRL** a současné **tažení kurzorem**
  * Rotace objektu kolem svého středu
- **Stisknutí levého tlačítka myši, stisknutí klávesy SHIFT** a současné **tažení kurzorem**
  * Posun středu objektu (a tedy i objektu samotného) ve smyslu původních os X resp. Y (směrem od a k zrcadlu resp. podél zrcadla nahoru a dolů)
- Stisknutí klávesy **Q**, **X** nebo **ESC**
  * Ukončení běžící aplikace
