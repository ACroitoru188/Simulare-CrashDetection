Airbag Crash Detection Simulator

Acest proiect personal are ca scop simularea detectiei unui impact auto si a mecanismului de declansare a airbag-urilor.

Functionarea programului:

1. citirea datelor de accelerație dintr-un fișier CSV
2. analizarea valorilor pentru detectarea unui posibil impact
3. declanșarea airbag-ului atunci când accelerația depășește un prag pentru o anumită durată(accel < CRASH_THRESHOLD si impact_time >= MIN_DURATION_MS)
4. clasificarea impactului în minor, moderat sau sever(accel < SEVERE_THRESHOLD fiind sever, accel < CRASH_THRESHOLD fiind moderat si altfel minor)
5. pornirea unui temporizator de 5 secunde pentru apelul automat către serviciile de urgență
6. posibilitatea de anulare a apelului SOS prin apăsarea tastei S de la tastatură
7. simularea apelului automat la 112 dacă apelul nu este anulat(in cele 5 secunde)
8. salvarea informațiilor despre accident într-un fișier de tip crash log

Crash log-ul conține informații precum:

momentul detectării impactului

valoarea accelerației în momentul impactului

severitatea impactului

locația GPS simulată

data și ora producerii evenimentului


Posibile îmbunătățiri

Control prin comandă vocală

Pe lângă anularea apelului prin tastatură, sistemul ar putea include și comenzi vocale prin care ocupanții vehiculului să confirme sau să anuleze apelul către serviciile de urgență.

Integrarea mai multor senzori

Într-un realitate, detectarea impactului se bazează pe mai mulți senzori. Proiectul ar putea simula și:

senzori de rotație

senzori de impact lateral

senzori suplimentari de accelerație
