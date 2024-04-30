#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    int n;
    // int element;
    cout<< "enter total number of elements: ";
    cin>> n;
    
    int arr[n];
    cout<<"enter the elements: ";
    for( int i = 0; i < n ; i++) {
        //element = rand()%10;
        //arr[i] = element;
        cin >> arr[i];
    }
    
    int sum = 0;
    int min_val = arr[0];
    int max_val = arr[0];
    //////////////////////////////////////////////////////////////////////////
    high_resolution_clock::time_point start_time_sum, end_time_sum;
    nanoseconds duration_sum;
    
    start_time_sum = high_resolution_clock::now();
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0 ; i < n ; i++)
    {
        sum += arr[i];
    }
    end_time_sum = high_resolution_clock::now();
    duration_sum = duration_cast<nanoseconds>(end_time_sum - start_time_sum);
    
    ///////////////////////////////////////////////////////////////////////
    high_resolution_clock::time_point start_time_avg, end_time_avg;
    nanoseconds duration_avg;
    
    start_time_avg = high_resolution_clock::now();
    int avg = sum / static_cast<double>(n);
    end_time_avg = high_resolution_clock::now();
    duration_avg = duration_cast<nanoseconds>(end_time_avg - start_time_avg);
    
    ///////////////////////////////////////////////////////////////////////
    high_resolution_clock::time_point start_time_minmax, end_time_minmax;
    nanoseconds duration_minmax;
    
    start_time_minmax = high_resolution_clock::now();
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val)
    for(int i = 0 ; i < n ; i++)
    {
        if(min_val > arr[i]) min_val = arr[i];
        if(max_val < arr[i]) max_val = arr[i];
    }
    end_time_minmax = high_resolution_clock::now();
    duration_minmax = duration_cast<nanoseconds>(end_time_minmax - start_time_minmax);
   ////////////////////////////////////////////////////////////// 
   
    int sum1 = 0;
    int min_val1 = arr[0];
    int max_val1 = arr[0];
    
    
    high_resolution_clock::time_point start_time_sum1, end_time_sum1;
    nanoseconds duration_sum1;
    
    start_time_sum1 = high_resolution_clock::now();
    for(int i = 0 ; i < n ; i++)
    {
        sum1 += arr[i];
    }
    end_time_sum1 = high_resolution_clock::now();
    duration_sum1 = duration_cast<nanoseconds>(end_time_sum1 - start_time_sum1);
    
    //////////////////////////////////////////////////////////////////////////
    
    high_resolution_clock::time_point start_time_avg1, end_time_avg1;
    nanoseconds duration_avg1;
    
    start_time_avg1 = high_resolution_clock::now();
    int avg1 = sum1 / static_cast<double>(n);
    end_time_avg1 = high_resolution_clock::now();
    duration_avg1 = duration_cast<nanoseconds>(end_time_avg1 - start_time_avg1);
    
    ///////////////////////////////////////////////////////////////////////////
    high_resolution_clock::time_point start_time_minmax1, end_time_minmax1;
    nanoseconds duration_minmax1;
    
    start_time_minmax1 = high_resolution_clock::now();
    for(int i = 0 ; i < n ; i++)
    {
        if(min_val1 > arr[i]) min_val1 = arr[i];
        if(max_val1 < arr[i]) max_val1 = arr[i];
    }
    end_time_minmax1 = high_resolution_clock::now();
    duration_minmax1 = duration_cast<nanoseconds>(end_time_minmax1 - start_time_minmax1);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    cout << "sum: " << sum << endl;
    cout << "Time taken for parallel Sum calculation: " << duration_sum.count() << " Nanoseconds" << endl;
    cout << "Time taken for Sum calculation: " << duration_sum1.count() << " Nanoseconds" << endl;
    
    cout << "avg: " << avg << endl;
    cout << "Time taken for parallel avg calculation: " << duration_avg.count() << " Nanoseconds" << endl;
    cout << "Time taken for avg calculation: " << duration_avg1.count() << " Nanoseconds" << endl;
    
    cout << "min: " << min_val << endl;
    cout << "max: " << max_val << endl;
    cout << "Time taken for parallel min and max calculation: " << duration_minmax.count() << " Nanoseconds" << endl;
    cout << "Time taken for min and max calculation: " << duration_minmax1.count() << " Nanoseconds" << endl;
    
    return 0;
}