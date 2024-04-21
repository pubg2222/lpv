#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int *, int);

void swap(int &, int &);
double start,stop,start_p,stop_p;

void bubble_seq(int *a, int n)
{
  start=omp_get_wtime();
  for(int i=0;i<n;i++) 
  {       
    int first = i % 2;
    
    for(int j=first;j<n-1;j+=2)
    { 
      if(a[j]>a[j+1])
      {       
  	swap(a[j],a[j+1]);
      }        
    }      
     
  }
  stop=omp_get_wtime();
}

void bubble(int *a, int n)
{
  start_p=omp_get_wtime();
  for(int i=0;i<n;i++) 
  {       
    int first = i % 2;
          
    #pragma omp parallel for shared(a,first)
    for(int j=first;j<n-1;j+=2)
    { 
      if(a[j]>a[j+1])
      {       
  	swap(a[j],a[j+1]);
      }        
    }      
     
  }
  stop_p=omp_get_wtime();
}



void swap(int &a, int &b)
{
  int test;
  test=a;
  a=b;
  b=test;
}

int main()
{
  int *a,n;
  cout<<"Enter total no of Elements = ";
  cin>>n;
  
  a=new int[n];
  for(int i= 0; i<n; i++)
  {
  a[i]=rand()%1000;
  }
  
  bubble(a,n);
  cout<<"Parallely sorted array is\n";
  for(int i=0;i<n;i++)
  {
    cout<<a[i]<<" ";
  }
  
  bubble_seq(a,n);
  cout<<"\nSequential sorted array is\n";
  for(int i=0;i<n;i++)
  {
    cout<<a[i]<<" ";
  }
  
  cout << "\nTime Sequentials = " << stop-start;
  cout << "\nTime Parallel = " << stop_p-start_p<<endl;
  

  return 0;
}

