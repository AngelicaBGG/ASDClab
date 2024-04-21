# Analiza Algoritmilor de Sortare

Acest document prezintă o analiză cuprinzătoare a diferitor algoritmi de sortare în ceea ce privește complexitatea lor in timp și spatiu, performanța cu diferite aranjamente de date.

## 1. Complexitatea Teoretică

### Sortarea cu Bule și Sortarea prin Inserție
- Complexitatea timp:
  - Cazul Cel Mai Bun: \(O(N)\) (când array-ul este deja sortat)
  - Cazul Mediu și Cel Mai Rău: \(O(N^2)\)
- Complexitatea Spațială: \(O(1)\)

### Quick Sort
- Complexitatea timp:
  - Cazul Cel Mai Bun și Mediu: \(O(N \log N)\)
  - Cazul Cel Mai Rău: \(O(N^2)\) (când array-ul este deja sortat sau toate elementele sunt identice)
- Complexitatea Spațială: \(O(\log N)\) pentru spațiul stivei recursive; \(O(N)\) în cel mai rău caz.

### Merge Sort
- Complexitatea timp: Mereu \(O(N \log N)\)
- Complexitatea Spațială: \(O(N)\) din cauza necesității de array-uri adiționale.

## 2. Complexitatea Practică

### Sortat 1000 rows
- Testing Bubble Sort:
Time: 0ms, Comparisons: 999, Swaps: 0
- Testing Insertion Sort:
Time: 0ms, Comparisons: 0, Swaps: 0
- Testing Quick Sort:
Time: 184ms, Comparisons: 499500, Swaps: 500499
- Testing Merge Sort:
Time: 5ms, Comparisons: 5044, Swaps: 9976

### Inversat 1000 rows
- Testing Bubble Sort:
Time: 210ms, Comparisons: 999000, Swaps: 499500
- Testing Insertion Sort:
Time: 72ms, Comparisons: 499500, Swaps: 500499
- Testing Quick Sort:
Time: 107ms, Comparisons: 499500, Swaps: 250499
- Testing Merge Sort:
Time: 3ms, Comparisons: 4932, Swaps: 9976

### Amesticat 1000 rows
- Testing Bubble Sort:
Time: 110ms, Comparisons: 953046, Swaps: 246106
- Testing Insertion Sort:
Time: 26ms, Comparisons: 246106, Swaps: 247092
- Testing Quick Sort:
Time: 3ms, Comparisons: 10284, Swaps: 5617
- Testing Merge Sort:
Time: 6ms, Comparisons: 8680, Swaps: 9976

----------------------------------------------

### Sortat 100 rows
- Testing Bubble Sort:
Time: 0ms, Comparisons: 99, Swaps: 0
- Testing Insertion Sort:
Time: 0ms, Comparisons: 0, Swaps: 0
- Testing Quick Sort:
Time: 2ms, Comparisons: 4950, Swaps: 5049
- Testing Merge Sort:
Time: 0ms, Comparisons: 356, Swaps: 672

### Inversat 100 rows
- Testing Bubble Sort:
Time: 1ms, Comparisons: 9900, Swaps: 4950
- Testing Insertion Sort:
Time: 0ms, Comparisons: 4950, Swaps: 5049
- Testing Quick Sort:
Time: 1ms, Comparisons: 4950, Swaps: 2549
- Testing Merge Sort:
Time: 0ms, Comparisons: 316, Swaps: 672

### Amesticat 100 rows
- Testing Bubble Sort:
Time: 0ms, Comparisons: 8712, Swaps: 2384
- Testing Insertion Sort:
Time: 0ms, Comparisons: 2384, Swaps: 2476
- Testing Quick Sort:
Time: 0ms, Comparisons: 541, Swaps: 338
- Testing Merge Sort:
Time: 0ms, Comparisons: 557, Swaps: 672


## 3. Impactul Dimensiunii Array-ului și al Aranjamentului Elementelor

- Sortarea cu Bule și Sortarea prin Inserție funcționează bine pe date mici sau pre-sortate, dar performanța lor scade semnificativ pe array-uri mari sau când elementele sunt în ordine inversă.
- Quick Sort arată o performanță excelentă pe seturi de date mari și aleatorii, dar poate degenera la \(O(N^2)\) dacă selecția pivotului este săracă.
- Merge Sort oferă un timp de execuție constant indiferent de ordinea inițială a elementelor, făcându-l fiabil pentru aplicații unde predictibilitatea performanței este critică.

## 4. Compararea Algoritmilor cu \(O(N \log(N))\)

### Quick Sort vs. Merge Sort
- Quick Sort nu necesită memorie adițională pentru operația principală, făcându-l mai potrivit pentru condiții limitate de memorie. Totuși, performanța sa în cel mai rău caz poate scădea semnificativ.
- Merge Sort necesită memorie adițională \(O(N)\), dar oferă un timp de execuție stabil, făcându-l ideal pentru aplicații unde predictibilitatea timpului de execuție este crucială.

## Concluzie

Alegerea unui algoritm de sortare depinde de cerințele specifice și de condițiile de utilizare. De exemplu, dacă memoria nu este un factor limitativ, Merge Sort ar putea fi preferabil pentru seturi de date mari datorită predictibilității sale. Quick Sort este adesea ales pentru eficiența sa medie de performanță și utilizarea memoriei, dar sistemele critice ar putea necesita examinarea unei abordări cu o performanță garantată a celui mai rău caz, cum ar fi Merge Sort.