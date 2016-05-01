#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "check.h"

#define HEAP 1
#define RECHEAP 2
#define PRUNEDHEAP 3
#define PERMUTE 4

void checkpoly(uint32_t *n, uint32_t *a, uint32_t b)
{
   uint32_t i;
   if (ispoly(n,a,b) == 0)
   {
      printf("Polydivisible number in base %u!!!: ",b);
      for (i = 0; i < b-1; i++)
      {
         printf("%u ",n[i]);
      }
      printf("\n");
   }
}

void permute(uint32_t l, uint32_t *n, uint32_t *a, uint32_t b)
{
   uint32_t temp, i;
   // l is the length of the (sub)sequence to permute

   if (ispartpoly(n,a,b,b-l-1) != 0)
   {
      return;
   }

   if (l == 1)
   {
      if (ispartpoly(n,a,b,b-1) == 0)
      {
         printf("Polydivisible number in base %u!!!: ",b);
         for (i = 0; i < b-1; i++)
         {
            printf("%u ",n[i]);
         }
         printf("\n");
      }
      return;
   }

   // First permute the remaining digits
   permute(l-1, n, a, b);

   // Try all possible digits not already used
   for (i = 0; i < l-1; i++)
   {
      // swap the current digit with each down the sequence
      temp = n[b-l-1];
      n[b-l-1] = n[b-l+i];
      n[b-l+i] = temp;
      permute(l-1,n,a,b);
      // swap back
      temp = n[b-l-1];
      n[b-l-1] = n[b-l+i];
      n[b-l+i] = temp;
   }
}

void generate(uint32_t l, uint32_t *n, uint32_t *a, uint32_t b)
{
   // l is the length of the (sub)sequence to permute
   uint32_t c, temp, j;
   if (l == 1)
   {
      checkpoly(n,a,b);
      return;
   }

   // Heap's algorithm with array indices inverted
   // So swapping from the end of the array most
   // frequently
   for (c = 0; c < l; c++)
   {
      generate(l-1, n, a, b);
      j = l % 2 ? 0 : c;
      temp = n[b-2-j];
      n[b-2-j] = n[b-l-1];
      n[b-l-1] = temp;
   }
}   

void generateprune(uint32_t l, uint32_t *n, uint32_t *a, uint32_t b)
{
   // l is the length of the (sub)sequence to permute
   uint32_t c, temp, j, i;
   //if (n[1] == 3) return;
   /*if (ispartpoly(n,a,b,b-l) != 0)
   {
      return;
   }
   if (l == 1)
   {
      // If we reach here and just tested for divisibility by b-1 then
      // we've found a polydivisible number
      printf("Polydivisible number in base %u!!!: ",b);
      for (i = 0; i < b-1; i++)
      {
         printf("%u ",n[i]);
      }
      printf("\n");
      return;
   }*/

   if (l == 1)
   {
      for (i = 0; i < b-1; i++)
      {
         printf("%u ",n[i]);
      }
      printf("\n");
      checkpoly(n,a,b);
      return;
   }

   // Heap's algorithm with array indices inverted
   // So swapping from the end of the array most
   // frequently
   for (c = 0; c < l; c++)
   {
      generateprune(l-1, n, a, b);
      j = l % 2 ? 0 : c;
      temp = n[b-2-j];
      n[b-2-j] = n[b-l-1];
      n[b-l-1] = temp;
   }
}

int main(int argc, char **argv)
{

   if (argc != 2 && argc != 3)
   {
      printf("Usage: ./poly base [1=bruteforce|2=heap|3=prunedheap]\n");
      exit(1);
   }

   uint32_t b = atoi(argv[1]);
   int32_t i, j;

   uint32_t alg = PERMUTE;
   if (argc == 3)
   {
      alg = atoi(argv[2]);
   }

   printf("A program for finding polydivisible numbers\n");
   printf("By Iain Bethune\n\n");
   printf("Checking base %u ...\n",b);

   if (b % 2 == 1)
   printf("Odd base => No polydivisible numbers!\n");
   return 0;
   
   uint32_t *a = (uint32_t *)malloc((b-1)*sizeof(uint32_t));
   uint32_t *n = (uint32_t *)malloc((b-1)*sizeof(uint32_t));


   if (alg == HEAP)
   { 
      // Generate all permutations...
   
      uint32_t temp;
   
      uint32_t *p = (uint32_t *)malloc((b-1)*sizeof(uint32_t));
   
      for (i = 0; i < b-1; i++)
      {
         n[i] = i + 1;
         p[i] = 0;
      }
   
      checkpoly(n,a,b);
      i = 1;
      while (i < b-1)
      {
         if (p[i] < i)
         {
            j = i % 2 * p[i];
            temp = n[j];
            n[j] = n[i];
            n[i] = temp;
            checkpoly(n,a,b);
            p[i]++;
            i = 1;
         }
         else
         {
            p[i] = 0;
            i++;
         }
      }
      free(p);
   }
   else if (alg == RECHEAP)
   {
      for (i = 0; i < b-1; i++)
      {
         n[i] = i + 1;
      }

      // permute all b-1 digits
      generate(b-1, n, a, b);
   }
   else if (alg == PRUNEDHEAP)
   {
      printf("Recursive heap not implemented...\n");
      /* 
      for (i = 0; i < b-1; i++)
      {
         n[i] = i + 1;
      }

      // permute all b-1 digits
      generateprune(b-1, n, a, b);
      */
   }
   else if (alg == PERMUTE)
   {
      for (i = 0; i < b-1; i++)
      {
         n[i] = i + 1;
      }

      // permute all b-1 digits
      permute(b-1, n, a, b); 
   }
   else
   {
      printf("Error: algorithm %u not recognised!\n",alg);
   }

   printf("Done!\n");
   free (a); free(n);
   return 0;
}

