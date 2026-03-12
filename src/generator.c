#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void normal_driving(FILE *f, int *t)
{
    for(int i=0;i<50;i++)
    {
        float accel = ((rand()%20)-10)/100.0;
        float gyro = (rand()%30)/100.0;
        float speed = 60 + (rand()%3);

        fprintf(f,"%d,%.2f,%.2f,%.2f\n",(*t)++,accel,gyro,speed);
    }
}

void hard_braking(FILE *f, int *t)
{
    float accel = -0.5;

    for(int i=0;i<10;i++)
    {
        accel -= 0.5;

        fprintf(f,"%d,%.2f,%.2f,%.2f\n",
        (*t)++,
        accel,
        1.0 + (rand()%10)/10.0,
        60-i*3);
    }
}

void frontal_crash(FILE *f, int *t)
{
    float accel = -5;

    for(int i=0;i<15;i++)
    {
        accel -= 0.7;

        fprintf(f,"%d,%.2f,%.2f,%.2f\n",
        (*t)++,
        accel,
        2.0 + (rand()%20)/10.0,
        40-i*2);
    }
}

void side_crash(FILE *f, int *t)
{
    for(int i=0;i<10;i++)
    {
        fprintf(f,"%d,%.2f,%.2f,%.2f\n",
        (*t)++,
        -3.0 - (rand()%20)/10.0,
        7 + (rand()%40)/10.0,
        30);
    }
}

void post_crash(FILE *f, int *t)
{
    for(int i=0;i<50;i++)
    {
        fprintf(f,"%d,0.00,0.10,0.00\n",(*t)++);
    }
}

int main()
{
    srand((unsigned)time(NULL) ^ (unsigned)clock());

    FILE *f = fopen("data/crash_data.csv","w");

    if(f == NULL)
    {
        printf("Can't create file\n");
        return 1;
    }

    fprintf(f,"time,accel,gyro,speed\n");

    int t = 0;

    normal_driving(f,&t);
    hard_braking(f,&t);
    frontal_crash(f,&t);
    side_crash(f,&t);
    post_crash(f,&t);

    fclose(f);

    printf("crash_data.csv generated\n");

    return 0;
}