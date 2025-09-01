#include <stdio.h>
#include <stdlib.h>
#include <io_utils.h>

int main() {
  int array[2][3] = {0, 1, 2, 3, 4, 5};
  // 0 1 2
  // 3 4 5
  PRINT_INT(array[0][1]);
  PRINT_INT(array[1][1]);
  
  int *p = array;
  PRINT_INT(p[1]);
  PRINT_INT(*(p + 1));
  PRINT_INT(p[4]);
    
  PRINT_INT(sizeof(array));
//  
//  int **pp = malloc(sizeof(int *) * 4);
//  for(int i = 0; i < 4; i++) {
// 请注意一定要释放内存
//    *(pp + i) = malloc(sizeof(int) * (i + 1));
//    for(int j = 0; j < i + 1; j++) {
//      int *q = *(pp + i);
//      *(q + j) = j * j;
//    }
//  }
//  
//  free(pp);
  
  return 0;
}
