#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <omp.h>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819

double small_monte()
{
    int i, in=0;
    double x, y;
    unsigned seed;
    srand(getpid());

    double nparts=10000;

    for (i=0; i<nparts; i++) {
	x = (double)rand_r(&seed)/(double)RAND_MAX;
	y = (double)rand_r(&seed)/(double)RAND_MAX;

	if (x*x + y*y < 1.0) {
	    in++;
	}
    }

    return in/(double)nparts * 4.0;
}

double med_monte()
{
    int i, in=0;
    double x, y;
    unsigned seed;
    srand(getpid());

    double nparts=1000000;

    for (i=0; i<nparts; i++) {
	x = (double)rand_r(&seed)/(double)RAND_MAX;
	y = (double)rand_r(&seed)/(double)RAND_MAX;

	if (x*x + y*y < 1.0) {
	    in++;
	}
    }

    return in/(double)nparts * 4.0;
}

double large_monte()
{
    int i, in=0;
    double x, y;
    unsigned seed;
    srand(getpid());

    double nparts=100000000;

    for (i=0; i<nparts; i++) {
	x = (double)rand_r(&seed)/(double)RAND_MAX;
	y = (double)rand_r(&seed)/(double)RAND_MAX;

	if (x*x + y*y < 1.0) {
	    in++;
	}
    }

    return in/(double)nparts * 4.0;
}
int main(int argc, char **argv)
{
    for (int i=1; i<100000; i++) {
        small_monte();
        med_monte();
        large_monte();
    }
}
