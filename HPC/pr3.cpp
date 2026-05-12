#include<iostream>
#include<omp.h>
using namespace std;
int main(){
    int a[]={1,2,3,4,5};
    int n=5;
    int min=a[0], max=a[0], sum=0;
    float avg;
    #pragma omp parallel for reduction(min:min)
    for(int i=0;i<n;i++)
        if(a[i]<min) 
            min=a[i];
    #pragma omp parallel for reduction(max:max)
    for(int i=0;i<n;i++)
        if(a[i]>max) 
            max=a[i];
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++)
        sum+=a[i];
    avg=(float)sum/n;
    
    cout<<"Minimum = "<<min<<endl;
    cout<<"Maximum = "<<max<<endl;
    cout<<"Sum = "<<sum<<endl;
    cout<<"Average = "<<avg;
    return 0;
}