#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chrono;

void bubble_Sort(int arr[], int n)
{
    bool swapped;
    for(int i = 0 ; i < n - 1; i++)
    {
        swapped = false;
        #pragma omp parallel for shared(arr,swapped)
        for(int j = 0 ; j < n - i - 1; j++ )
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}

void bubbleSort(int arr[], int n)
{
   
    for(int i = 0 ; i < n - 1; i++)
    {
        for(int j = 0 ; j < n - i - 1; j++ )
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void merge(int arr[], int l,int m, int r)
{
    int n1 = m-l+1;
    int n2 = r-m;
    int L[n1], R[n2];
    
    for(int i = 0 ; i < n1; i++)
       L[i] = arr[l+i];
    for(int j = 0 ; j < n2; j++)
       R[j] = arr[m+1+j];
       
    int i = 0 , j = 0 , k=l;
    while(i<n1 && j < n2)
    {
        if(L[i]<=R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while(i<n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
      while(j<n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_Sort(int arr[],int l,int r)
{
    if(l<r)
    {
        int m = l + (r-l) /2;
        #pragma omp parallel sections
        {
            #pragma omp sections
            merge_Sort(arr,l,m);
            #pragma omp sections
            merge_Sort(arr,m+1,r);
        }
         merge(arr, l,m,r);
    }
}

void mergeSort(int arr[],int l,int r)
{
    if(l<r)
    {
        int m = l + (r-l) /2;
        
            
            merge_Sort(arr,l,m);
            
            merge_Sort(arr,m+1,r);
        
         merge(arr, l,m,r);
    }
}

int main(){
 /* int arr_size;
    int element;
    cout<<"Enter size of the array: ";
    cin>>arr_size;
    
    int arr_original[arr_size];
    int arr_bubble[arr_size];
    int arr_merge[arr_size];
    //cout<<"Enter array elements: ";
    for(int i=0; i<arr_size; ++i)
    {
        element = rand()%10;
        arr_original[i] = element;
        arr_bubble[i] = arr_original[i];
        arr_merge[i] = arr_bubble[i];
    } */
 
 ////////////   
    int arr_size;
    cout << "Enter size of the array: ";
    cin >> arr_size;
    
    int arr_bubble[arr_size];
    int arr_merge[arr_size];
    cout << "Enter array elements: ";
    for(int i = 0 ; i < arr_size; i++)
    {
        cin >> arr_bubble[i];
        arr_merge[i] = arr_bubble[i];
    }
////////////

    auto start_time = high_resolution_clock::now();
    bubbleSort(arr_bubble, arr_size);
    auto end_time = high_resolution_clock::now();
    auto duration1 = duration_cast<nanoseconds>(end_time - start_time);
    cout << "\nSequential Bubble Sort executed in " << duration1.count() << " nanoseconds." << endl;
    
    start_time = high_resolution_clock::now();
    bubble_Sort(arr_bubble, arr_size);
    end_time = high_resolution_clock::now();
    duration1 = duration_cast<nanoseconds>(end_time - start_time);
    cout<<"The bubble sorted array: ";
    for(int i=0; i<arr_size; ++i){
        cout<<arr_bubble[i]<<" ";
    }
    cout << "\nParallel Bubble Sort executed in " << duration1.count() << " nanoseconds." << endl;

    start_time = high_resolution_clock::now();
    mergeSort(arr_merge, 0, arr_size);
    end_time = high_resolution_clock::now();
    duration1 = duration_cast<nanoseconds>(end_time - start_time);
    cout << "\nSequential merge Sort executed in " << duration1.count() << " nanoseconds." << endl;

    start_time = high_resolution_clock::now();
    merge_Sort(arr_merge, 0, arr_size-1);
    end_time = high_resolution_clock::now();
    duration1 = duration_cast<nanoseconds>(end_time - start_time);
    cout<<"The merge sorted array: ";
    for(int i=0; i<arr_size; ++i){
        cout<<arr_merge[i]<<" ";
    }
    cout << "\nParallel Merge Sort executed in " << duration1.count() << " nanoseconds." << endl;
    return 0;
}