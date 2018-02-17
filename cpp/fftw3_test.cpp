// http://digiphd.com/programming-reconstruction-fast-fourier-transform-real-signal-fftw-libraries/
/*
compile with MacPorts:
clang++ -I/opt/local/include -L/opt/local/lib -lfftw3 -lm fftw3_test.cpp -o fftw3_test
*/

#include <fftw3.h>
#include <cstdlib>
#include <cmath>
#include <cstdio>

int main(void)
{
  // Variable Declaration
  double array[] = {0.1, 0.6, 0.1, 0.4, 0.5, 0, 0.8, 0.7, 0.8, 0.6, 0.1,0};
  double *out,*mag,*phase;
  double real,imag;
  int i,j;
  int size = sizeof(array)/sizeof(double);
  fftw_complex *out_cpx, *mod_cpx;
  fftw_plan fft; 
  fftw_plan ifft; 

  //Allocate Memory
  out_cpx = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(size/2+1));
  mod_cpx = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(size/2+1));
  out = (double *) malloc(size*sizeof(double));
  mag = (double *) malloc(size*sizeof(double));
  phase = (double *) malloc(size*sizeof(double));

  fft = fftw_plan_dft_r2c_1d(size, array, out_cpx, FFTW_ESTIMATE);  //Setup fftw plan for fft 1 dimensional, real signal
  ifft = fftw_plan_dft_c2r_1d(size, mod_cpx, out, FFTW_ESTIMATE);   //Setup fftw plan for ifft 1 dimensional, complex signal

  fftw_execute(fft);  //perform fft
  for(j=0;j<size/2+1;j++)
  {
    real = out_cpx[j][0]; //Extract real component
    imag = out_cpx[j][1];   //Extract imaginary component
    mag[j] = sqrt((real*real)+(imag*imag));  // Calculate the Magnitude
    phase[j] = atan2(imag,real); // Calculate the Phase
  }

  /***********MODIFICATION****************************/
  //You can perform frequency domain modification here    
  /***************************************************/ 

  for(j=0;j<size/2+1;j++)
  {
    mod_cpx[j][0] = (mag[j]*cos(phase[j]));  //Construct new real component
    mod_cpx[j][1] = (mag[j]*sin(phase[j]));  //Construct new imaginary  component
  }

  fftw_execute(ifft); //perform ifft

  // Print input and output
  printf("Input:    \tOutput:\n");
  for(i=0;i<size;i++)
  {
    out[i] = out[i]/size; 
    printf("%f\t%f\n",(array[i]),out[i]);
  }

  // Free all memory
  fftw_destroy_plan(fft);
  fftw_destroy_plan(ifft);
  fftw_free(out_cpx);
  fftw_free(mod_cpx);
  free(out);
  free(mag);
  free(phase);
  return 0;
}
