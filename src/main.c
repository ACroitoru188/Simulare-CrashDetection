/*
Crash Detection Simulator

This program simulates the logic of an automotive crash detection system.
It processes vehicle sensor data (accelerometer, gyroscope, speed)
to detect collisions and trigger an emergency response.

Main features:
- Real-time vehicle sensor dashboard
- Crash detection algorithm
- Crash severity classification
- Crash type detection
- Emergency SOS simulation
- GPS location reporting
- Crash logging and CSV export
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define SAMPLE_TIME_MS 1
#define MIN_DURATION_MS 3
#define DASHBOARD 1


/* Configuration parameters loaded from file */
typedef struct
{
    float crash_threshold;
    float severe_threshold;
    float jerk_threshold;
    int sos_delay;
} Config;


/* Structure containing one sensor sample */
typedef struct
{
    int time_ms;
    float accel;
    float gyro;
    float speed;
} SensorData;


/* Runtime statistics */
typedef struct
{
    int total_samples;
    int crashes;
    int severe_crashes;
} Statistics;



/* Load detection parameters from config file */
void load_config(Config *cfg)
{
    FILE *file = fopen("config/config.txt","r");

    if(file == NULL)
    {
        printf("Config missing, using defaults\n");

        cfg->crash_threshold = -6;
        cfg->severe_threshold = -9;
        cfg->jerk_threshold = -4;
        cfg->sos_delay = 5;

        return;
    }

    fscanf(file,"CRASH_THRESHOLD=%f\n",&cfg->crash_threshold);
    fscanf(file,"SEVERE_THRESHOLD=%f\n",&cfg->severe_threshold);
    fscanf(file,"JERK_THRESHOLD=%f\n",&cfg->jerk_threshold);
    fscanf(file,"SOS_DELAY=%d",&cfg->sos_delay);

    fclose(file);
}


/* Simulated GPS location */
void get_gps_location(float *lat, float *lon)
{
    *lat = 45.6580;
    *lon = 25.6012;
}


/* Moving average filter to remove sensor noise */
float filter_accel(float new_val)
{
    static float buffer[5] = {0};
    static int index = 0;

    buffer[index] = new_val;
    index = (index + 1) % 5;

    float sum = 0;

    for(int i=0;i<5;i++)
        sum += buffer[i];

    return sum / 5.0f;
}


/* Determine crash severity based on acceleration */
const char* crash_severity(float accel, Config cfg)
{
    if(accel < cfg.severe_threshold)
        return "SEVERE";

    if(accel < cfg.crash_threshold)
        return "MODERATE";

    return "MINOR";
}


/* Classify crash type using acceleration and gyroscope */
const char* crash_type(float accel, float gyro)
{
    if(accel < -8)
        return "FRONTAL";

    if(gyro > 8)
        return "ROLLOVER";

    if(gyro > 5)
        return "LATERAL";

    if(accel < -5 && gyro > 3)
        return "OFFSET";

    return "UNKNOWN";
}


/* Crash detection score using multiple sensor inputs */
float crash_score(float accel, float gyro, float speed)
{
    float score = 0;

    if(accel < -5)
        score += 0.6;

    if(gyro > 3)
        score += 0.3;

    if(speed > 20)
        score += 0.2;

    return score;
}


/* Save crash information to log file */
void log_crash(int time_ms, float accel, float jerk, float lat, float lon, const char *severity, const char *type)
{
    FILE *log = fopen("output/crash_log.txt","a");

    if(log == NULL)
    {
        printf("ERROR: Could not open crash_log.txt\n");
        return;
    }

    printf("Writing crash to log...\n");   // DEBUG MESSAGE

    time_t now = time(NULL);

    fprintf(log,"\nCRASH DETECTED\n");
    fprintf(log,"Time: %d ms\n",time_ms);
    fprintf(log,"Acceleration: %.2f g\n",accel);
    fprintf(log,"Jerk: %.2f\n",jerk);
    fprintf(log,"Impact type: %s\n",type);
    fprintf(log,"Severity: %s\n",severity);
    fprintf(log,"GPS: %.4f %.4f\n",lat,lon);
    fprintf(log,"Timestamp: %s",ctime(&now));

    fclose(log);
}


/* Export crash data for later analysis */
void export_crash_csv(int time_ms, float accel, float jerk)
{
    FILE *f = fopen("output/crashes.csv","a");

    if(f == NULL)
        return;

    if(ftell(f) == 0)
        fprintf(f,"time,accel,jerk\n");

    fprintf(f,"%d,%.2f,%.2f\n",time_ms,accel,jerk);

    fclose(f);
}


/* Emergency countdown allowing user to cancel SOS */
int sos_timer(int delay)
{
    printf("\nPress 'S' to cancel SOS\n");

    for(int i=delay;i>0;i--)
    {
        printf("Emergency call in %d seconds...\n",i);

        time_t start = time(NULL);

        while(difftime(time(NULL),start) < 1)
        {
            if(kbhit())
            {
                char key = getch();

                if(key == 's' || key == 'S')
                {
                    printf("SOS canceled\n");
                    return 1;
                }
            }
        }
    }

    return 0;
}


/* Simple terminal dashboard showing live sensor values */
void draw_dashboard(SensorData data, float accel)
{
    system("cls");

    printf("--------------------------------------\n");
    printf("      VEHICLE SENSOR MONITOR\n");
    printf("--------------------------------------\n\n");

    printf("Time:          %d ms\n", data.time_ms);
    printf("Speed:         %.2f km/h\n", data.speed);
    printf("Acceleration:  %.2f g\n", accel);
    printf("Gyroscope:     %.2f\n", data.gyro);

    printf("\nStatus:        NORMAL\n");
}


int main()
{
    /* Ensure output folder exists for logs */
    system("mkdir output >nul 2>&1");

    Config cfg;
    load_config(&cfg);

    Statistics stats = {0};

    FILE *file = fopen("data/crash_data.csv","r");

    if(file == NULL)
    {
        printf("Cannot open crash_data.csv\n");
        return 1;
    }

    SensorData data;

    char line[128];
    fgets(line,sizeof(line),file);

    float prev_accel = 0;

    int impact_time = 0;
    int airbag_deployed = 0;

    printf("\nCrash Detection System Started\n\n");


    while(fscanf(file,"%d,%f,%f,%f",
    &data.time_ms,
    &data.accel,
    &data.gyro,
    &data.speed) == 4)
    {
        stats.total_samples++;

        /* Apply noise filtering to accelerometer data */
        float accel = filter_accel(data.accel);

        /* Calculate jerk (rate of acceleration change) */
        float jerk = accel - prev_accel;
        prev_accel = accel;

        /* Update dashboard while no crash occurred */
        if(DASHBOARD && !airbag_deployed)
        {
            draw_dashboard(data, accel);
        }

        float score = crash_score(accel, data.gyro, data.speed);

        if(!airbag_deployed)
        {
             if(accel < cfg.crash_threshold)
    impact_time += SAMPLE_TIME_MS;
else
    impact_time = 0;

            /* Crash confirmed after minimum duration */
            if(impact_time >= MIN_DURATION_MS)
            {
                airbag_deployed = 1;

                stats.crashes++;

                if(accel < cfg.severe_threshold)
                    stats.severe_crashes++;

                float lat, lon;
                get_gps_location(&lat,&lon);

                const char *severity = crash_severity(accel,cfg);
                const char *type = crash_type(accel, data.gyro);

                printf("\n\n!!! IMPACT DETECTED !!!\n");
                printf("Impact type: %s\n",type);
                printf("Severity: %s\n",severity);

                log_crash(data.time_ms, accel, jerk, lat, lon, severity, type);
                export_crash_csv(data.time_ms, accel, jerk);

                if(!sos_timer(cfg.sos_delay))
                {
                    printf("\nAUTOMATIC EMERGENCY CALL\n");

                    printf("GPS: %.4f %.4f\n",lat,lon);
                    printf("Impact type: %s\n",type);
                    printf("Severity: %s\n",severity);
                    printf("Airbag: DEPLOYED\n");
                }
            }
        }

        Sleep(50);
    }

    fclose(file);

    printf("\n\nSTATISTICS\n");

    printf("Samples: %d\n",stats.total_samples);
    printf("Crashes: %d\n",stats.crashes);
    printf("Severe crashes: %d\n",stats.severe_crashes);

    printf("\nProgram finished\n");

    getchar();
    getchar();

    return 0;
}