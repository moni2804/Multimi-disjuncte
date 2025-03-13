## Implementare și Analiză: Algoritmul lui Kruskal cu Mulțimi Disjuncte

### Descriere
Această temă presupune implementarea și analizarea operațiilor de bază pe mulțimi disjuncte, utilizate în algoritmul lui Kruskal pentru găsirea arborelui de acoperire minimă. Se utilizează o pădure de arbori pentru reprezentarea mulțimilor disjuncte, fiecare arbore având un câmp `rank` pentru optimizare.

### Implementare
Sunt implementate următoarele operații fundamentale pe mulțimi disjuncte:
- **MAKE_SET(x)** – Creează o mulțime nouă ce conține elementul `x`.
- **UNION(x, y)** – Realizează reuniunea dintre mulțimile ce conțin `x` și `y`, utilizând euristica *union by rank*.
- **FIND_SET(x)** – Determină mulțimea în care se află `x`, utilizând euristica *path compression*.

De asemenea, se va implementa **algoritmul lui Kruskal** pentru determinarea arborelui de acoperire minimă al unui graf.

Datele de intrare: un graf conex, neorientat, ponderat.
Datele de ieșire: muchiile ce compun arborele de acoperire minimă.

### Analiză și Comparare
#### 1. Analiza Complexității
Se vor măsura numărul de comparații și atribuiri pentru fiecare operație:
- **MAKE_SET:** O(1)
- **FIND_SET cu path compression:** O(α(n)), unde α(n) este funcția inversă a lui Ackermann (aproximativ O(1) pentru valori practice de `n`).
- **UNION cu union by rank:** O(α(n))
- **Algoritmul lui Kruskal:** O(m log m) pentru sortarea muchiilor și O(m α(n)) pentru operațiile pe mulțimi disjuncte.

#### 2. Evaluarea Performanței
- Se vor testa operațiile pe mulțimi disjuncte în cadrul algoritmului lui Kruskal.
- Se vor varia dimensiunile grafului între 100 și 10.000 noduri, cu un pas de 100.
- Se vor măsura și compara numărul de operații pentru **MAKE_SET**, **UNION** și **FIND_SET**.
- Se vor genera grafice cu trei serii pentru fiecare operație.

### Cum să Rulezi Proiectul
   - Compilează codul sursă cu un compilator C++.
   - Rulează executabilul.

### Resurse
- Cormen, Thomas H. et al. - *Introduction to Algorithms* (Capitolele 21.3 și 23.2)
- Notițele de curs despre structuri de date și algoritmi pentru grafuri

