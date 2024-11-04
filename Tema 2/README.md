## TypeRacer Game

### Cerinte

Circuitul simuleaza un joc Typeracer folosind un dictionar cu siruri de caractere si citind prin portul serial datele scrise de catre utilizator. Un LED RGB este folosit pentru a marca daca ultimul cuvant a fost sau nu corect sau daca jocul a inceput sau nu. Doua butoane sunt folosite, unul pentru a schimba dificultatea (intervalul la care apar cuvintele noi) intre trei nivele (usor, mediu, dificil) si alt buton este folosit pentru pornirea sau oprirea jocului.

Butoanele folosesc variabile de 32 de biti si functia `millis`, atasate la interrupt-urile aferente pinilor 2 si 3 pentru a inregistra apasarile acestora fara debouncing.
Dictionarul, impreuna cu unele constante definite sub forma de macro-uri folosite in fisierul principal, se afla in fisierul `Dictionary.h`.

Cuvintele sunt alese aleator folosind functia `random`, initializata cu `randomSeed` primind datele dintr-un pin analogic care nu este conectat la nimic (astfel, folosind zgomotul drept seed).

Validarea inputului este facuta caracter cu caracter, folosind un indice pentru ultimul caracter corect scris si indicele caracterului curent. Acest lucru ne permite sa nu trebuiasca sa tinem minte toate caracterele precedente tastate de catre utilizator, si ii permite acestuia sa apese backspace de cate ori vrea, chiar si daca inputul sau initial ar depasi lungimea cuvantului sau daca ar suprascrie si partile tastate corect de la bun inceput.

### Componente utilizate

Componenta|Cantitate
---|---
LED RGB|1
Rezistor 330 $\Omega$|3
Rezistor 2k $\Omega$|2
Push buttons|2
Breadboard|1
Arduino UNO|1

### Poze ale setup-ului fizic

### Video cu functionalitatea montajului fizic

### Schema electrica