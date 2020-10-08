#include <stdio.h>
#include <stdlib.h>

/*
TEMPO SEQUENCIAL:

real    3m30.117s
user    1m15.715s
sys     0m0.127s

TEMPO PARALELO MULTICORE:

real    1m29.670s
user    1m14.390s
sys     0m0.269s

TEMPO PARALELO DISTRIBUTE PARALLEL FOR:

real    2m58.611s
user    0m38.440s
sys     0m9.928s

TEMPO PARALELO GPU SIMD:

real    0m22.656s
user    0m5.845s
sys     0m1.807s

*/

void mm(double* a, double* b, double* c, int width) 
{
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      double sum = 0;
      for (int k = 0; k < width; k++) {
	double x = a[i * width + k];
	double y = b[k * width + j];
	sum += x * y;
      }
      c[i * width + j] = sum;
    }
  }
}

int main()
{
  int width = 2000;
  double *a = (double*) malloc (width * width * sizeof(double));
  double *b = (double*) malloc (width * width * sizeof(double));
  double *c = (double*) malloc (width * width * sizeof(double));

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      a[i*width+j] = i;
      b[i*width+j] = j;
      c[i*width+j] = 0;
    }
  }

  mm(a,b,c,width);

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      printf("%f\n",c[i*width+j]);
    }
  }

}
