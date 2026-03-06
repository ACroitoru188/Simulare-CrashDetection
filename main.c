#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

// Praguri impact
#define CRASH_THRESHOLD -6.0f
#define SEVERE_THRESHOLD -9.0f

// Durata minima impact
#define MIN_DURATION_MS 3

// Sample time
#define SAMPLE_TIME_MS 1

// Timer SOS
#define SOS_DELAY 5


// Functie simulare GPS
void get_gps_location(float *lat, float *lon)
{
    *lat = 45.6580;
    *lon = 25.6012;
}


// Functie severitate impact
char* crash_severity(float accel)
{
    if (accel < SEVERE_THRESHOLD)
        return "SEVER";
    else if (accel < CRASH_THRESHOLD)
        return "MODERAT";
    else
        return "MINOR";
}


// Functie log accident
void log_crash(int time_ms, float accel)
{
    FILE *log = fopen("crash_log.txt", "a");

    if (log == NULL)
        return;

    float lat, lon;
    get_gps_location(&lat, &lon);

    time_t now = time(NULL);

    fprintf(log, "\nACCIDENT DETECTAT\n");
    fprintf(log, "Timp impact: %d ms\n", time_ms);
    fprintf(log, "Acceleratie: %.2f g\n", accel);
    fprintf(log, "Severitate: %s\n", crash_severity(accel));
    fprintf(log, "GPS: %.4f , %.4f\n", lat, lon);
    fprintf(log, "Timestamp: %s", ctime(&now));

    fclose(log);
}


// Timer SOS
int sos_timer()
{
    printf("\nSistem activat.\n");
    printf("Apasa 'S' pentru a anula apelul SOS.\n\n");

    for(int i = SOS_DELAY; i > 0; i--)
    {
        printf("Apel automat in %d secunde...\n", i);

        time_t start = time(NULL);

        while(difftime(time(NULL), start) < 1)
        {
            if(kbhit())
            {
                char key = getch();

                if(key == 'S' || key == 's')
                {
                    printf("\nApel SOS anulat de ocupant.\n");
                    return 1;
                }
            }
        }
    }

    return 0;
}


int main(void)
{
    FILE *file = fopen("crash_data.csv", "r");

    if(file == NULL)
    {
        printf("Err: fisierul crash_data.csv nu se deschide\n");
        return 1;
    }

    char line[128];
    int time_ms;
    float accel;

    int impact_time = 0;
    int airbag_deployed = 0;

    fgets(line, sizeof(line), file);

    printf("\nSISTEM DETECTIE IMPACT PORNIT\n\n");

    while(fscanf(file,"%d,%f",&time_ms,&accel) == 2)
    {
        printf("t=%d ms | accel=%.2f g\n",time_ms,accel);

        if(!airbag_deployed)
        {
            if(accel < CRASH_THRESHOLD)
                impact_time += SAMPLE_TIME_MS;
            else
                impact_time = 0;

            if(impact_time >= MIN_DURATION_MS)
            {
                airbag_deployed = 1;

                printf("\n !IMPACT DETECTAT!\n");
                printf("Severitate: %s\n", crash_severity(accel));

                printf("\nAIRBAG DECLANSAT la t=%d ms\n",time_ms);

                log_crash(time_ms, accel);

                if(!sos_timer())
                {
                    float lat, lon;
                    get_gps_location(&lat, &lon);

                    printf("\n APEL AUTOMAT 112\n");
                    printf("Transmitere date accident...\n");

                    printf("Locatie GPS: %.4f , %.4f\n", lat, lon);
                    printf("Severitate impact: %s\n", crash_severity(accel));
                    printf("Airbag: ACTIVAT\n");
                }
            }
        }
    }



    if(!airbag_deployed)
    {
        printf("\nNu a fost detectat impact.\n");
    }

    fclose(file);

    printf("\nProgram terminat.\n");
    printf("Apasa Enter pentru iesire...");
    getchar();
    getchar();


    return 0;
}