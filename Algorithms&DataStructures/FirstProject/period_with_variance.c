#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

// Calcola il periodo frazionario usando un algoritmo quadratico
/*
int periodNaive(char *s)
{
    int len = strlen(s);
    for (int p=1; p <= len; p++)
    {
        int i;
        for( i=0; i < len - p; i++)
        {
            if (s[i] != s[i+p])
            {
                break;
            }
        }
        if ( i == len-p)
        {
            return p;
        }
    }
    return len;
}

*/

int periodNaive(char *s)
{
    int len = strlen(s);
    for(int p=1; p<= len; p++)
    {
        int dim = len - p;
        char s1[dim];
        strncpy(s1, s, len - p);
        s1[dim] = '\0';
        char s2[dim];
        strncpy(s2, s+p, len - p);
        s2[dim] = '\0';

        if (strcmp(s1,s2) == 0)
        {

            return p;
        }
    }

    return len;
}

// Calcola il periodo frazionario usando un algoritmo lineare
int periodSmart(char *s)
{
    int n = strlen(s);
    int r[n];
    for (int i=0; i < n; i++)
    {
        r[i] = 0;
    }
    for (int i=1; i < n; i++)
    {
        int z = r[i-1];
        while (s[i] != s[z] && z > 0)
        {
            z = r[z-1];
        }
        if (s[i] == s[z])
        {
            r[i] = z + 1;
        }
        else
        {
            r[i] = 0;
        }
    }
    return n - r[n-1];
}


// Calcola la risoluzione del clock di sistema
long getResolution()
{
    struct timespec start;
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do
    {
        clock_gettime(CLOCK_MONOTONIC, &end);
    }
    while(start.tv_nsec == end.tv_nsec);
    return (end.tv_nsec - start.tv_nsec);
}


// Calcola la risoluzione media
long getMediaResolution()
{
    long v[10000];
    long result;
    for (int i=0; i < 10000; i++)
    {
        v[i] = getResolution();
    }
    for (int j=0; j < 10000; j++)
    {
        result = result + v[j];
    }
    return result/10000;
}

long long difftimespec_ns(const struct timespec start, const struct timespec end)
{
    long long diff = ((end.tv_sec - start.tv_sec) * 1000000000) +
                     (end.tv_nsec - start.tv_nsec);
    return diff;
}

int main()
{
    srand(time(NULL));

    long Nmin = 1000;
    long Nmax = 500000;

    char *s[100];

    long stringSize[100];
    long indiceMAX = 99;

    int iterations = 100; // per la varianza

    struct timespec startN;
    struct timespec endN;
    struct timespec startL;
    struct timespec endL;

    long R = getMediaResolution();
    double Emax = 0.001;
    long tmin = ((R/Emax) + R );

    // Calcolo le lunghezze delle stringhe e riservo la memoria
    for (int  n=0; n < 100; n++)
    {
        double  A = Nmin;
        double  B = exp( (log(Nmax) - log(A)) / indiceMAX );
        stringSize[n] = round( A * pow(B,n) );
        s[n] = malloc(sizeof(char) * stringSize[n] + 1);
    }

    long long timesNaive[iterations][100];
    long long timesSmart[iterations][100];

    // Ciclo per il calcolo dei tempi
    for (int  m=0; m < iterations; m++)
    {
        // Genero le stringhe
        for (int  n=0; n < 100; n++)
        {
            long i;
            long q = (rand() % stringSize[n]) + 1;

            for (i=0; i < q; i++)
                s[n][i] = rand() % 2 + 'a';

            s[n][(q-1)] = 'c';

            for (i=q; i < stringSize[n]; i++)
                s[n][i] = s[n][(i % q)];

            s[n][i] = '\0';
        }

        //misuraNaive
        for (int  n=0; n < 100; n++)
        {
            fprintf(stderr, "Misura naive %d ciclo %d\n", n, m);
            clock_gettime(CLOCK_MONOTONIC, &startN);
            int k = 0;
            int period;
            do
            {
                period = periodNaive(s[n]);
                clock_gettime(CLOCK_MONOTONIC, &endN);
                k = k + 1;
            }
            while (difftimespec_ns(startN, endN) < tmin);

            long count = (long) k;
            long long res = (difftimespec_ns(startN, endN)) / count;

            timesNaive[m][n] = res;
        }

        //misuraLineare
        for (int  n=0; n < 100; n++)
        {
            fprintf(stderr, "Misura smart %d ciclo %d\n", n, m);
            clock_gettime(CLOCK_MONOTONIC, &startL);
            int k = 0;
            int period;
            do
            {
                period = periodSmart(s[n]);
                clock_gettime(CLOCK_MONOTONIC, &endL);
                k = k + 1;
            }
            while (difftimespec_ns(startL, endL) < tmin);

            long count = (long) k;
            long long res = (difftimespec_ns(startL, endL)) / count;

            timesSmart[m][n] = res;

        }
    }//for calcolo dei tempi

    // Calcolo le medie dei tempi degli algoritmi
    long long mediaNaive[100];
    long long mediaSmart[100];

    for (int n=0; n < 100; n++)
    {
        long long sumNaive = 0;
        long long sumSmart = 0;
        for (int m=0; m < iterations; m++)
        {
            sumNaive += timesNaive[m][n];
            sumSmart += timesSmart[m][n];
        }
        mediaNaive[n] = round(sumNaive / iterations);
        mediaSmart[n] = round(sumSmart / iterations);
    }

    // Calcolo le varianze
    long long varianceNaive[100];
    long long varianceSmart[100];

    for (int n=0; n < 100; n++)
    {
        double sumNaive = 0;
        double sumSmart = 0;
        for (int m=0; m < iterations; m++)
        {
            sumNaive += pow((timesNaive[m][n] - mediaNaive[n]), 2);
            sumSmart += pow((timesSmart[m][n] - mediaSmart[n]), 2);
        }
        varianceNaive[n] = (long long) round(sqrt(sumNaive / (iterations - 1)));
        varianceSmart[n] = (long long) round(sqrt(sumSmart / (iterations - 1)));
    }

    // Creo e popolo i files di log
    FILE *fileN = fopen("./logNaive.txt", "w");
    FILE *fileL = fopen("./logLineare.txt", "w");

    char bufferN[50];
    char bufferL[50];

    for (int n=0; n < 100; n++)
    {
        sprintf(bufferN, "%ld...%lld...%lld\n", stringSize[n], mediaNaive[n], varianceNaive[n]);
//        sprintf(bufferN, "%ld...%lld\n", stringSize[n], timesNaive[0][n]);
        fwrite(bufferN, sizeof(char), strlen(bufferN), fileN);
        sprintf(bufferL, "%ld...%lld...%lld\n", stringSize[n], mediaSmart[n], varianceSmart[n]);
//        sprintf(bufferL, "%ld...%lld\n", stringSize[n], timesSmart[0][n]);
        fwrite(bufferL, sizeof(char), strlen(bufferL), fileL);
    }

    fclose(fileN);
    fclose(fileL);

    return 0;
}
