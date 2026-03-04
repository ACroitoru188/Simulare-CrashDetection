#include <stdio.h>
#include <stdlib.h>

#define CRASH_THRESHOLD  -6.0f
#define MIN_DURATION_MS  3
#define SAMPLE_TIME_MS   1

int main(void)
{
    FILE *file = fopen("crash_data.csv", "r");
    if (file == NULL) {
        printf("Err: fisierul crash_data.csv nu se deschide\n");
        return 1;
    }

    char line[128];
    int time_ms;
    float accel;
    int impact_time = 0;
    int airbag_deployed = 0;

    // sarim peste header
    fgets(line, sizeof(line), file);

    while (fscanf(file, "%d,%f", &time_ms, &accel) == 2) {
        printf("t=%d ms | accel=%.2f g\n", time_ms, accel);

        if (!airbag_deployed) {
            if (accel < CRASH_THRESHOLD) {
                impact_time += SAMPLE_TIME_MS;
            } else {
                impact_time = 0;
            }

            if (impact_time >= MIN_DURATION_MS) {
                airbag_deployed = 1;
                printf("\n AIRBAG DECLANSAT la t=%d ms\n", time_ms);
            }
        }
    }

    if (!airbag_deployed) {
        printf("\nNu a fost detectat impact.\n");
    }

    fclose(file);

    printf("\nApasa pentru a iesi");
    getchar();

    return 0;
}// modificare test