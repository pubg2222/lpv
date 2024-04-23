#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;
int main()
{
  
	double stop, start_p, stop_p;
	start_p=omp_get_wtime();
  	omp_set_num_threads(4);
  	double max_val=1999.0;
  	int i, n;
  	cout<<"Enter no. elements : ";
  	cin>>n;
         double a[n];
         for(int i= 0; i<n; i++)
  	{
  	a[i]=rand()%1000;
  	}

	#pragma omp parallel for reduction(max : max_val)
  
	for( i=0;i<n; i++)
  	{
     	   cout<<" thread id = "<< omp_get_thread_num() <<" and i = " << i; 
     	   //printf("thread id = %d and i = %d\n", omp_get_thread_num(), i);
     		if(a[i] < max_val)
     		{
        		max_val = a[i];
     		}
  	}
	stop_p=omp_get_wtime();
  	cout<<"\nmax_val = "<< max_val;
	cout << "\n Time Estimated= " << stop_p-start_p;
}


