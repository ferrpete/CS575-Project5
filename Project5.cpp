#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <omp.h>

float A[NUMS];
float C[NUMS];
float LOW = 0.;
float HIGH = 1000.;
int NUMTRIES = 20;

float Ranf( float low, float high, unsigned int* seed );

int main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
		fprintf( stderr, "OpenMP is not available\n" );
		return 1;
#endif

	unsigned int seed = omp_get_wtime( );
	
	for( int i = 0; i < NUMS; i++ )
	{
		
		A[i] = Ranf( LOW, HIGH, &seed );
		
	}
	
	omp_set_num_threads( NUMT );
	fprintf( stderr, "Using %d threads\n", NUMT );
	
	double peakPerformance = 0.;
	double performanceSum = 0.;
	
	for( int t = 0; t < NUMTRIES; t++ )
	{
	
		double time0 = omp_get_wtime( );
		
		#pragma omp parallel for simd
		for( int i = 0; i < NUMS; i++ )
		{
			
			C[i] = sqrt( A[i] );
			
		}
		
		double time1 = omp_get_wtime( );
		double performance = (double) NUMS / (time1 - time0) / 1000000;
		performanceSum += performance;
			
		if( performance > peakPerformance )
		{
			peakPerformance = performance;
		}
		
	}
		
		double averagePerformance = performanceSum / (double)NUMTRIES;
		printf( "Peak Performance : %8.2lf MegaRoots/sec\n", peakPerformance );
		printf( "Average Performance : %8.2lf MegaRoots/sec\n", averagePerformance );
		
		std::ofstream dataFile("NoVectorizeData.txt", std::ofstream::out | std::ofstream::app);
		dataFile << NUMT << ", " << NUMS << ", " << peakPerformance << ", " << averagePerformance << "\n";
	
	return 0;
	
}

float Ranf( float low, float high, unsigned int* seed )
{
	
	float r = (float)rand_r(seed);    // 0 - RAND_MAX
	return( low + r * ( high - low ) / (float)RAND_MAX );
	
}