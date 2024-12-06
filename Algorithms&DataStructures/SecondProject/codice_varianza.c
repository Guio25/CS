#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>

#include "funzioni.h"

void clear(Node *x) {

     if (x!=NULL) {

         clear(x->left);
         clear(x->right);
         free(x);
     }
}

void initialize(void) {

 //    if (bst!=NULL)
	clear(bst);

 //    if (rbt!=NULL)
	clear(rbt);

 //    if (avl!=NULL)
	clear(avl);

     bst=NULL;
     rbt=NULL;
     avl=NULL;
}

int find(Node *x, int k) {

     while (x!=NULL && x->key!=k) {
        if (k > x->key)
           x = x->right;
        else
           x = x->left;
     }

     if (x!=NULL)
        return 1;
     else
	return 0;
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

    bst=NULL;
    rbt=NULL;
    avl=NULL;

    struct timespec startBST;
    struct timespec endBST;
    struct timespec startRBT;
    struct timespec endRBT;
    struct timespec startAVL;
    struct timespec endAVL;

    char bufferBST[50];
    char bufferRBT[50];
    char bufferAVL[50];
    char buffer[60];

    long Nmin = 1000;
    long Nmax = 100000;
    long indiceMAX = 99;

    long R = getMediaResolution();
    double Emax = 0.01;
    long tmin = ((R/Emax) + R);

    int iterations[100];
    long long iters = 10;
    int key;

    long long sumBST;
    long long sumRBT;
    long long sumAVL;

    long long varianceBST[100];
    long long varianceRBT[100];
    long long varianceAVL[100];

    long long mediaBST[100];
    long long mediaRBT[100];
    long long mediaAVL[100];

    long long timesBST[iters][100];
    long long timesRBT[iters][100];
    long long timesAVL[iters][100];

    for (int n=0; n < 100; n++)
    {
        double A = Nmin;
        double B = exp( (log(Nmax) - log(A)) / indiceMAX );
        iterations[n] = round( A * pow(B,n) );
    }

    FILE *fileBST = fopen("./logBST.txt", "w");
    FILE *fileRBT = fopen("./logRBT.txt", "w");
    FILE *fileAVL = fopen("./logAVL.txt", "w");
    FILE *file = fopen("./log.txt", "w");

    sprintf(buffer, "input  medBST  sqmBST  medRBT  sqmRBT  medAVL  sqmAVL\n");
    fwrite(buffer, sizeof(char), strlen(buffer), file);

    Node *nodo;
   
  for (int m=0; m<iters; m++) {                //prima colonna: input 1000
     printf("%d\n", m); 

    for (int n=0; n < 100; n++) {

        initialize();                 //ripulisce gli alberi

	//misuraBST
	clock_gettime(CLOCK_MONOTONIC, &startBST);
        int k = 0;
	key=rand()%10000;

        do {

	   for (int i=0; i<iterations[n]; i++) {

	       key += rand()%1000;

               if (!find(bst, key))
		   insertBST(key);
               
            }
	    clock_gettime(CLOCK_MONOTONIC, &endBST);
            k = k + 1;

	} while (difftimespec_ns(startBST, endBST) < tmin);

        long count = (long) k;
        long long res = (difftimespec_ns(startBST, endBST)) / count;
	timesBST[m][n] = res / iterations[n];

        //misuraRBT
	clock_gettime(CLOCK_MONOTONIC, &startRBT);
        k = 0;
	key=rand()%10000;

        do {

	   for (int i=0; i<iterations[n]; i++) {

	       key += rand()%1000;

               if (!find(rbt, key))
		   insertRBT(key);
               
            }
	    clock_gettime(CLOCK_MONOTONIC, &endRBT);
            k = k + 1;

	} while (difftimespec_ns(startRBT, endRBT) < tmin);

        count = (long) k;
        res = (difftimespec_ns(startRBT, endRBT)) / count;
	timesRBT[m][n] = res / iterations[n];

	//misuraAVL
	clock_gettime(CLOCK_MONOTONIC, &startAVL);
        k = 0;
	key=rand()%10000;

        do {

	   for (int i=0; i<iterations[n]; i++) {

	       key += rand()%1000;

               if (!find(avl, key)) {
		   nodo = create(key);
		   avl = insertAVL(avl, nodo);
	       }
               
            }
	    clock_gettime(CLOCK_MONOTONIC, &endAVL);
            k = k + 1;

	} while (difftimespec_ns(startAVL, endAVL) < tmin);

        count = (long) k;
        res = (difftimespec_ns(startAVL, endAVL)) / count;
	timesAVL[m][n] = res / iterations[n];

    }//n

  }//m

    for (int n=0; n<100; n++) {

        sumBST = 0;
        sumRBT = 0;
	sumAVL = 0;

        for (int m=0; m<iters; m++) {

            sumBST += timesBST[m][n];
            sumRBT += timesRBT[m][n];
	    sumAVL += timesAVL[m][n];
        }

        mediaBST[n] = round(sumBST/iters);
        mediaRBT[n] = round(sumRBT/iters);
	mediaAVL[n] = round(sumAVL/iters);
    }

    for (int n=0; n<100; n++) {

        sumBST = 0;
        sumRBT = 0;
	sumAVL = 0;

        for (int m=0; m<iters; m++) {

	    sumBST = sumBST+pow(timesBST[m][n]-mediaBST[n], 2);
            sumRBT = sumRBT+pow(timesRBT[m][n]-mediaRBT[n], 2);
	    sumAVL = sumAVL+pow(timesAVL[m][n]-mediaAVL[n], 2);
        }

        varianceBST[n] = round(sqrt(sumBST/(iters-1)));
        varianceRBT[n] = round(sqrt(sumRBT/(iters-1)));
	varianceAVL[n] = round(sqrt(sumAVL/(iters-1)));

        sprintf(buffer, "%d.....%lld.....%lld.....%lld.....%lld.....%lld.....%lld\n", iterations[n], mediaBST[n], varianceBST[n], mediaRBT[n], varianceRBT[n], mediaAVL[n], varianceAVL[n]);   
        fwrite(buffer, sizeof(char), strlen(buffer), file);

        sprintf(bufferBST, "%d     %lld     %lld\n", iterations[n], mediaBST[n], varianceBST[n]);   
        fwrite(bufferBST, sizeof(char), strlen(bufferBST), fileBST);
        sprintf(bufferRBT, "%d     %lld     %lld\n", iterations[n], mediaRBT[n], varianceRBT[n]);
        fwrite(bufferRBT, sizeof(char), strlen(bufferRBT), fileRBT);
	sprintf(bufferAVL, "%d     %lld     %lld\n", iterations[n], mediaAVL[n], varianceAVL[n]);
        fwrite(bufferAVL, sizeof(char), strlen(bufferAVL), fileAVL);
    }

    fclose(fileBST);
    fclose(fileRBT);
    fclose(fileAVL);
    fclose(file);

    return 0;

} //main