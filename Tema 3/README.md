## Quicktime

### Componente utilizate

Componenta|Cantitate
---|---
Arduino UNO|2
Push Buttons|6
Condensator 100 $\mu\text{F}$|1
Servomotor|1
LCD 16x2|1
LED RGB|2
LED Rosu|2
LED Verde|2
LED Albastru|2


### Protocolul de comunicatie

#### Mesajele de la Master

Poll|Player|Unused|Led
---|---|---|---
0|0|0000|00

- Poll - Daca acest bit are valoarea 1, master-ul intreaba arduino-ul slave daca un buton a fost apasat.
- Player - Precizeaza jucatorul activ (0 fiind primul jucator, 1 fiind al doilea jucator).
- Unused - Biti disponibili pentru expansiuni viitoare.
- Led - Precizeaza culoarea LED-ului RGB care sa fie aprinsa:
  - 00 insemnand LED oprit
  - 01 insemnand rosu
  - 10 insemnand verde
  - 11 insemnand albastru


#### Mesajele de la Slave

Unused|Pressed
---|---
000000|00

- Pressed: Precizeaza butonul care a fost apasat:
  - 00 insemnand ca niciun buton nu a fost apasat inca.
  - 01 insemnand ca butonul corespunzator LED-ului rosu a fost apasat.
  - 10 insemnand ca butonul corespunzator LED-ului verde a fost apasat.
  - 11 insemnand ca butonul corespunzator LED-ului albastru a fost apasat.

 
#### Exemplu de comunicare:

```
Master: 00000011 // A inceput o runda noua, este randul primului jucator, LED-ul corect este albastru.
Slave : 00000011 // Raspunde cu acelasi mesaj, sa confirme ca a inteles.
Master: 10000000 // Polling.
Slave : 00000000 // Momentan jucatorul nu a apasat niciun buton.
Master: 10000000 // Polling iar.
Slave : 00000000 // Samd.
// Repetam secventa pana jucatorul apasa pe buton...
Master: 10000000
Slave : 00000011 // Jucatorul a apasat pe butonul corespunzator LED-ului albastru.
Master: 00000000 // Oprim LED-ul, runda s-a terminat.
Slave : 00000000 
// Nimic nu se transmite pana la inceputul rundei urmatoare...
Master: 01000010 // Este randul celui de-al doilea jucator si LED-ul corect este verde.
```

#### Pornirea jocului

Deoarece arduino-ul slave accepta apasari din partea ambilor jucatori cand LED-ul este oprit, dupa ce jocul s-a terminat putem da poll constant pentru a astepta inceperea jocului urmator.

```
Master: 00000000 // Jocul s-a terminat, inchidem LED-urile.
Slave: 00000000 // Looping back.
Master: 10000000 // Polling.
Slave : 00000000
// Repetam pana unul dintre butoane este apasat...
Master: 10000000
Slave: 00000010 // Unul dintre jucatori a apasat butonul corespunzator LED-ului verde. Putem incepe jocul.
// Asteptam inceperea jocului...
Master: 00000001 // A inceput prima runda, este randul primului jucator si LED-ul corect este cel rosu. 
```