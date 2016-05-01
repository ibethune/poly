#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "check.h"

int main(int argc, char **argv)
{

   if (argc < 3)
   {
      printf("Usage: ./poly base d0 d1 d2 d3 ...\n");
      exit(1);
   }

   uint32_t b = atoi(argv[1]);

   if (argc != b + 1)
   {
      printf("Usage: ./poly base d0 d1 d2 d3 ...\n");
      exit(1);
   }

   int32_t i, j;

   printf("A program for checking numbers for polydivisibity\n");
   printf("By Iain Bethune\n\n");
   printf("Checking base %u ...\n",b);
   
   uint32_t *a = (uint32_t *)malloc((b-1)*sizeof(uint32_t));
   uint32_t *n = (uint32_t *)malloc((b-1)*sizeof(uint32_t));

   // Set up the digits

   for (i = 0; i < b-1; i++)
   {
      n[i] = atoi(argv[2+i]);
      if (n[i] > b-1)
      {
         printf("Illegal value: %u > %u!\n",n[i],b-1);
         free(a); free(n);
         exit(1);
      }
      for (j = 0; j < i; j++)
      {
         if (n[i] == n[j])
         {
            printf("Illegal value: %u was used twice!\n",n[i]);
            free(a); free(n);
            exit(1);
         }
      }
   }

   printf("Checking candidate ");
   for (i = 0; i < b-1; i++)
   {
      printf("%u ",n[i]);
   }
   printf("\n");

   uint32_t r = ispoly(n,a,b);

   if (r == 0) 
   {
      printf("Polydivisible number in base %u!!!\n",b);
   }
   else
   {
      printf("Not polydivisible in base %u because:\n",b);
      printf("%u does not divide ",r);
      for (i = 0; i < r; i++)
      {
         printf("%u ",n[i]);
      }
      printf("\n");
   }
   free(a); free(n);

   printf("Done!\n");
   return 0;
}
