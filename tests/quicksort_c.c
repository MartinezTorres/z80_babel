#include <stdint.h>

void quicksort_c(uint16_t *A, uint16_t len) {
    
  if (len < 2) return;
 
  uint16_t pivot = A[len / 2];
 
  uint16_t i, j;
  for (i = 0, j = len - 1; ; i++, j--) {
    while (A[i] < pivot) i++;
    while (A[j] > pivot) j--;
 
    if (i >= j) break;
 
    uint16_t temp = A[i];
    A[i]     = A[j];
    A[j]     = temp;
  }
 
  quicksort_c(A, i);
  quicksort_c(A + i, len - i);
}
 
void quicksort_c_end() {}
