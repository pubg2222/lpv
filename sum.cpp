#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;
int main()
{
	double stop, start_p, stop_p;
	start_p=omp_get_wtime();
  	omp_set_num_threads(4);
  	double sum=0.0;
  	int i, n;
  	cout<<"Enter no. elements : ";
  	cin>>n;
        double a[n];
        for(int i= 0; i<n; i++){
  		a[i]=rand()%1000;
  	}

	#pragma omp parallel for reduction(+ : sum)
	for( i=0;i<n; i++){
     	   printf("thread id = %d and i = %d\n", omp_get_thread_num(), i);
 	   sum += a[i];
     	
  	}
	stop_p=omp_get_wtime();
  	cout<<"\nsum = "<< sum;
	cout << "\n Time Estimated= " << stop_p-start_p;
}


