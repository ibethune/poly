#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "check.h"

uint32_t ispoly(uint32_t *n, uint32_t *a, uint32_t b)
{
   uint32_t i, d;
   // Trial divide each number
   // Always divisible by 1
   for (i = 1; i < b-1; i++)
   {
      d = ispartpoly(n,a,b,i+1); 
      if (d != 0) return i+1; // Not polydivisible because failed to divide sub-sequence of length i+1
   }

   return 0; // Zero indicates success
}

uint32_t ispartpoly(uint32_t *n, uint32_t *a, uint32_t b, uint32_t l)
{

   if (l == 0) return 0;

   // l is the number to trial divide (and also the number of digits to use)
   uint32_t i, j, r;

   // Copy of the digits so we can carry
   for (j = 0; j < l; j++)
   {
      a[j] = n[j];
   }

   // divide digits n[0] ... n[l-1] by l
   r = a[0] % l;
   for (j = 1; j < l; j++)
   {
      // Carry into next digit
      a[j] += b * r;
      // Remainder
      r = a[j] % l;
   }

   return r; // Non-zero => failed to trial divide 
}
