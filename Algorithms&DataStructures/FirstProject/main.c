#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

//// Calcola il periodo frazionario usando un algoritmo quadratico
//int periodNaive(char *s)
//{
//    int len = strlen(s);
//    for (int p=1; p <= len; p++)
//    {
//        int i;
//        for( i=0; i < len - p; i++)
//        {
//            if (s[i] != s[i+p])
//            {
//                break;
//            }
//        }
//        if ( i == len-p)
//        {
//            return p;
//        }
//    }
//    return len;
//}

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

    struct timespec startN;
    struct timespec endN;
    struct timespec startL;
    struct timespec endL;

    long R = getMediaResolution();
    double Emax = 0.001;
    long tmin = ((R/Emax) + R );

    for (int  n=0; n < 100; n++)    //genero le stringhe che saranno uguali per entrambi gli algoritmi
    {
        double  A = Nmin;
        double  B = exp( (log(Nmax) - log(A)) / indiceMAX );
        stringSize[n] = round( A * pow(B,n) );
        s[n] = malloc(sizeof(char) * stringSize[n] + 1);

        int i;
        for ( i=0; i < stringSize[n]; i++ )
            s[n][i] = rand() % 2 + 'a';

        s[n][i] = '\0';
    }

    char bufferN[50];
    char bufferL[50];

    FILE *fileN = fopen("./logNaive.txt", "w");

    //misuraNaive
    for (int  n=0; n < 100; n++)
    {
        printf("Misura naive %d\n", n);
        clock_gettime(CLOCK_MONOTONIC, &startN);
        int k = 0;
        do
        {
            int period = periodNaive(s[n]);
            clock_gettime(CLOCK_MONOTONIC, &endN);
            k = k + 1;
        }
        while (difftimespec_ns(startN, endN) < tmin);

        long count = (long) k;
        long long res = (difftimespec_ns(startN, endN)) / count;

        sprintf(bufferN, "%ld......%lld\n", stringSize[n], res);   //converto la dimensione dell'input e il risultato in una stringa che memorizzo nel buffer
        fwrite(bufferN, sizeof(char), strlen(bufferN), fileN);    //scrivo il contenuto del buffer nel file di log
    }

    fclose(fileN);

    FILE *fileL = fopen("./logLineare.txt", "w");

    //misuraLineare
    for (int  n=0; n < 100; n++)
    {
        clock_gettime(CLOCK_MONOTONIC, &startL);
        int k = 0;
        do
        {
            int period = periodSmart(s[n]);
            clock_gettime(CLOCK_MONOTONIC, &endL);
            k = k + 1;
        }
        while (difftimespec_ns(startL, endL) < tmin);

        long count = (long) k;
        long long res = (difftimespec_ns(startL, endL)) / count;

        sprintf(bufferL, "%ld......%lld\n", stringSize[n], res);
        fwrite(bufferL, sizeof(char), strlen(bufferL), fileL);
    }


    fclose(fileL);
    return 0;
} //main
