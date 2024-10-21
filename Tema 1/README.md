## Sistem de încărcare a unui vehicul electric

### Cerinte

Circuitul simuleaza o statie de incarcare a unui vehicul electric, folosind un LED RGB pentru a informa utilizatorul ca statia de incarcare este disponibila sau este in folosinta (marcata de culoarea verde sau rosie respectiv). Desi circuitul este o simulare, trebuie sa ia in considerare fenomenul de debouncing la butoane, aceasta verificare fiind facuta in cod.

Progresul incarcarii este transmis prin cele patru LEDuri simple care devin aprinse cand procesul de incarcare atinge pragurile delimitate de 25% din procesul de incarcare. Deoarece acest dispozitiv doar simuleaza procesul de incarcare, pragurile vor fi atinse la intervalul fix de trei secunde. LEDul care semnifica procentul curent de incarcare va fi in starea de clipire. Daca bateria vehiculului simulat este incarcata la maxim, o animatie in care toate cele patru LEDuri simple sunt in stare de clipire va fi afisata.

Butonul din dreapta incepe procesul de incarcare printr-o apasare scurta a acestuia. Apasarea acestuia in timp ce statia deja este in folosinta nu va face nimic. Butonul din stanga, daca este tinut apasat timp de o secunda, va incheia prematur procesul de incarcare si va elibera statia, astfel LED-ul RGB va deveni iar verde. Apasarea butonului de stop (din stanga) va afisa aceeasi animatie ca in momentul in care incarcarea este incheiata, clipind toate LEDurile simple de trei ori.

### Componente utilizate

Componenta|Cantitate
---|---
LED Albastru|4
LED RGB|1
Rezistor 330 $\Omega$|7
Rezsitor 2k $\Omega$|2
Push buttons|2
Breadboard|1
Arduino UNO|1

### Poze ale setup-ului fizic

![image](https://github.com/user-attachments/assets/e9f945df-67fa-478d-9250-2d76df26ae58)
![image](https://github.com/user-attachments/assets/81327dd9-3bbf-45d6-9af4-55a759f80691)


### Video cu functionalitatea montajului fizic


https://github.com/user-attachments/assets/0de3d4f8-aee9-46cc-b237-4a3641755154


### Schema electrica

![image](https://github.com/user-attachments/assets/f9c2d7a3-f556-40bb-9668-6362f2c133b8)
