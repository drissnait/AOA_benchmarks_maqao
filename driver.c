#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "rdtsc.c"
#include "baseline.c"

#define NB_METAS 31



//affciher un tableau 
void print_array (int n, float a[n]) {
	int i;

   for (i=0; i<n; i++)
         printf ("%f\n", a[i]);
}

//génerer le tableau aleatoirement 
void generator(int N,float tab[N]){
	srand(time(NULL));
	int i;
    for(i = 0; i<N; i++)
       tab[i] = rand() % 10;
}

int main(int argc, char *argv[])
{	
	
	/* check command line arguments */
   if (argc != 4) {
      fprintf (stderr, "Usage: %s <size> <nb warmup repets> <nb measure repets>\n", argv[0]);
      abort();
   }

   int i, m;

   /* get command line arguments */
   int size = atoi (argv[1]); /* taille du tableau */
   int repw = atoi (argv[2]); /* nombre de repetition */
   int repm = atoi (argv[3]); /* nombre de repetition */

   float sum = 0.0 ; 
   for (m=0; m<NB_METAS; m++) {
      /* allocation mémoire des tableaux */
      float *a = malloc (size * sizeof(float));
      float *b = malloc (size * sizeof(float));
      float *c = malloc (size * sizeof(float));
      
      //generation des tableau aleatoires
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

      sum = sum + ((t2 - t1) / ((float) size * repm ));
      /* print performance */
     printf ("%.2f cycles/element\n", (t2 - t1) / ((float) size * repm ));


      /* free arrays */
      free (a);
      free (b);
      free (c);
      
  }
	printf ("%.2f mediane :cycles\n",sum );
   printf ("%.2f mediane :cycles/element\n", (sum / (float) NB_METAS));
	return 0;
}


