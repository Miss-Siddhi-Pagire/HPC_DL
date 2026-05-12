#include<iostream>
#include<cuda_runtime.h>
using namespace std;

// Vector Addition
__global__ void add(int *A,int *B,int *C){
    int i=threadIdx.x;
    C[i]=A[i]+B[i];
}

// Matrix Multiplication
__global__ void mul(int *A,int *B,int *C){
    int r=threadIdx.y;
    int c=threadIdx.x;

    C[r*2+c]=A[r*2]*B[c] + A[r*2+1]*B[2+c];
}

int main(){
    // Vector Addition
    int A[]={1,2,3,4}, B[]={5,6,7,8}, C[4];
    int *X,*Y,*Z;
    cudaMalloc(&X,16);
    cudaMalloc(&Y,16);
    cudaMalloc(&Z,16);
    cudaMemcpy(X,A,16,cudaMemcpyHostToDevice);
    cudaMemcpy(Y,B,16,cudaMemcpyHostToDevice);
    add<<<1,4>>>(X,Y,Z);
    cudaMemcpy(C,Z,16,cudaMemcpyDeviceToHost);
    cout<<"Vector Add:\n";
    for(int i=0;i<4;i++)
        cout<<C[i]<<" ";

    // Matrix Multiplication
    int M1[]={1,2,3,4}, M2[]={5,6,7,8}, M3[4];
    cudaMemcpy(X,M1,16,cudaMemcpyHostToDevice);
    cudaMemcpy(Y,M2,16,cudaMemcpyHostToDevice);
    dim3 t(2,2);
    mul<<<1,t>>>(X,Y,Z);
    cudaMemcpy(M3,Z,16,cudaMemcpyDeviceToHost);
    cout<<"\n\nMatrix Multiplication:\n";
    for(int i=0;i<4;i++){
        cout<<M3[i]<<" ";
        if(i%2==1) cout<<endl;
    }
    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);
    return 0;
}