#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;
// Parallel Bubble Sort
void bubbleSort(vector<int>& a,int n){
    for(int i=0;i<n;i++){
        #pragma omp parallel for
        for(int j=0;j<n-1;j+=2)
            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
        #pragma omp parallel for
        for(int j=1;j<n-1;j+=2)
            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
    }
}

// Merge Function
void merge(vector<int>& a,int l,int m,int r){
    vector<int> temp;
    int i=l,j=m+1;

    while(i<=m && j<=r){
        if(a[i]<a[j]) temp.push_back(a[i++]);
        else temp.push_back(a[j++]);
    }

    while(i<=m) temp.push_back(a[i++]);
    while(j<=r) temp.push_back(a[j++]);

    for(int k=l;k<=r;k++)
        a[k]=temp[k-l];
}

// Parallel Merge Sort
void mergeSort(vector<int>& a,int l,int r){
    if(l>=r) return;

    int m=(l+r)/2;

    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSort(a,l,m);

        #pragma omp section
        mergeSort(a,m+1,r);
    }

    merge(a,l,m,r);
}

int main(){
    vector<int> a={9,5,1,4,3};

    vector<int> b=a;

    bubbleSort(a,a.size());

    cout<<"Bubble Sort:\n";
    for(int x:a) cout<<x<<" ";

    mergeSort(b,0,b.size()-1);

    cout<<"\nMerge Sort:\n";
    for(int x:b) cout<<x<<" ";

    return 0;
}