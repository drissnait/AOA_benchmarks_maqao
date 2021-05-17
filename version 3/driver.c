#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
//#include "rdtsc.c"
//#include "baseline.c"

#define NB_METAS 31

extern uint64_t rdtsc ();

extern void baseline ( unsigned n , float a [ n ] , float b [ n ] , float c [ n ]);

//affciher un tableau 
void print_array (int n, float a[n]) {
	int i;

   for (i=0; i<n; i++)
         printf ("%f\n", a[i]);
}

//génerer le tableau aleatoirement 
void generator(int N,float tab[N]){
	//srand(time(NULL));
	int i;
    for(i = 0; i<N; i++)
       tab[i] = (float) rand() / RAND_MAX;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[])
{	
	
	/* check command line arguments */
   if (argc != 4) {
      fprintf (stderr, "Usage: %s <size> <nb warmup repets> <nb measure repets>\n", argv[0]);
      abort();
   }

   int i, m;
   float Tab[NB_METAS];

   /* get command line arguments */
   int size = atoi (argv[1]); /* taille du tableau */
   int repw = atoi (argv[2]); /* nombre de repetition */
   int repm = atoi (argv[3]); /* nombre de repetition */

   //float sum = 0.0 ; 
   for (m=0; m<NB_METAS; m++) {

      /* allocation mémoire des tableaux */

      float *a = malloc (size * sizeof(float));
      float *b = malloc (size * sizeof(float));
      float *c = malloc (size * sizeof(float));
      
      //generation des tableau aleatoires
      srand(0);
      generator(size,a);
	   generator(size,b);

      /* warmup (repw repetitions in first meta, 1 repet in next metas) */
      if (m == 0) {
         for (i=0; i<repw; i++)
            baseline (size ,a,b,c);
      } 
      else {
         baseline (size ,a,b,c);
      }

      /* measure repm repetitions */
      uint64_t t1 = rdtsc();
      for (i=0; i<repm; i++)
         baseline (size ,a,b,c);
      uint64_t t2 = rdtsc();

      //sum = sum + ((t2 - t1) / ((float) size * repm ));
      Tab[m] = (t2 - t1) / ((float) size * repm ) ;
      /* print performance */
     printf ("%.2f cycles/element\n", (t2 - t1) / ((float) size * repm ));


      /* free arrays */
      free (a);
      free (b);
      free (c);
      
  }
   //printf ("%.2f moyenne :cycles/element\n", (sum / (float) NB_METAS));
   printf("************************************");
   qsort(Tab,NB_METAS, sizeof(float), cmpfunc);
   //print_array (31,Tab);
   printf ("%.2f mediane :cycles/element\n", Tab[15]);
   printf ("(mediane-mnimum)/minimum = %.2f %% ", ((Tab[15]-Tab[0])*100)/Tab[0]);
   printf("\n");

	return 0;
}


