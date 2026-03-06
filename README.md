Acest proiect personal are ca scop simularea detectiei unui impact auto si a mecanismului de declansare a airbag-urilor.

Functionarea programului:

1. citirea datelor de acceleratie dintr-un fisier CSV
2. analizarea valorilor pentru detectarea unui posibil impact
3. declansarea airbag-ului atunci cand acceleratia depaseste un prag pentru o anumita durata(accel < CRASH_THRESHOLD si impact_time >= MIN_DURATION_MS)
4. clasificarea impactului in minor, moderat sau sever(accel < SEVERE_THRESHOLD fiind sever, accel < CRASH_THRESHOLD fiind moderat, altfel minor)
5. pornirea unui temporizator de 5 secunde pentru apelul automat catre serviciile de urgenta
6. posibilitatea de anulare a apelului SOS prin apasarea tastei S de la tastatura
7. simularea apelului automat la 112 daca apelul nu este anulat in intervalul de 5 secunde
8. salvarea informatiilor despre accident intr-un fisier de tip crash log

Programul salveaza informatii despre impact intr-un fisier numit crash_log.txt.
Acest fisier contine:

-momentul detectarii impactului

-valoarea acceleratiei in momentul impactului

-severitatea impactului

-locatia GPS simulata

-data si ora producerii evenimentului


Exemplu de output

SISTEM DETECTIE IMPACT PORNIT

t=0 ms | accel=0.00 g
t=1 ms | accel=0.10 g
t=2 ms | accel=-0.20 g
t=3 ms | accel=-0.30 g
t=4 ms | accel=-1.80 g
t=5 ms | accel=-7.50 g
t=6 ms | accel=-8.10 g
t=7 ms | accel=-7.00 g

 !IMPACT DETECTAT!
Severitate: MODERAT

AIRBAG DECLANSAT la t=7 ms

Sistem activat.
Apasa 'S' pentru a anula apelul SOS.

Apel automat in 5 secunde...
Apel automat in 4 secunde...
Apel automat in 3 secunde...
Apel automat in 2 secunde...
Apel automat in 1 secunde...

Apel SOS anulat de ocupant.
t=8 ms | accel=-3.00 g
t=9 ms | accel=-1.00 g

Program terminat.
Apasa Enter pentru iesire...


Posibile imbunatatiri

Control prin comanda vocala
Pe langa anularea apelului prin tastatura, sistemul ar putea include si comenzi vocale prin care ocupantii vehiculului sa confirme sau sa anuleze apelul catre serviciile de urgenta.

Integrarea mai multor senzori

In realitate, detectarea impactului se bazeaza pe mai multi senzori. Proiectul ar putea fi extins pentru a simula si:

-senzori de rotatie

-senzori de impct lateral

-senzori suplimentari de acceleratie
