#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 

#define oo 1000000000
vector <int> arr;
int brute_force_max_sum (int n) {
    int max_sum = -oo;
    for (int start = 0; start < n; start ++) {
        int end = start;
        int current_sum = 0;
        while (end < n) {
            current_sum = current_sum + arr[end];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
            end = end + 1;
        }
    }
    return max_sum;    
}

int find_max_crossing_subarray (int low, int mid, int high) {
    int left_sum = -oo;
    int sum = 0;
    for (int i = mid; i >= low; i --) {
        sum = sum + arr[i];
        if (sum > left_sum) {
            left_sum = sum;
        }
    }
    int right_sum = -oo;
    sum = 0;
    for (int j = mid + 1; j <= high; j ++) {
        sum = sum + arr[j];
        if (sum > right_sum) {
            right_sum = sum;
        }
    }
    return (left_sum + right_sum);
} 

int divide_n_conquer (int low, int high) {
    if (low == high) {
        return arr[low];
    }
    int mid = (low + high)/2;
    int left_sum = divide_n_conquer (low, mid);
    int right_sum = divide_n_conquer (mid + 1, high);
    int cross_sum = find_max_crossing_subarray (low, mid, high);
    if (left_sum >= right_sum && left_sum >= cross_sum) {
        return left_sum;
    }
    if (right_sum >= left_sum && right_sum >= cross_sum) {
        return right_sum;
    }
    return cross_sum;
}

int n0;
int divide_n_conquer_updated (int low, int high) {
    if (high + 1 < n0) {
        brute_force_max_sum(high + 1);
        return 0;
    }
    if (low == high) {
        return arr[low];
    }
    int mid = (low + high)/2;
    int left_sum = divide_n_conquer (low, mid);
    int right_sum = divide_n_conquer (mid + 1, high);
    int cross_sum = find_max_crossing_subarray (low, mid, high);
    if (left_sum >= right_sum && left_sum >= cross_sum) {
        return left_sum;
    }
    if (right_sum >= left_sum && right_sum >= cross_sum) {
        return right_sum;
    }
    return cross_sum;
}

int main() {
    
    int value;
    srand (time(NULL));
    
    for (int n = 1; n < 50; n ++) {
        int parity = rand() % 2;
        if (parity == 1) {
            value = -1 * (rand() % 1000 + 1);
        }
        else {
            value = rand() % 1000 + 1;
        }
        arr.push_back(value);
        
        auto start = high_resolution_clock::now(); 
        brute_force_max_sum(n);
        auto stop = high_resolution_clock::now(); 
        auto duration1 = duration_cast<microseconds>(stop - start);
        
        start = high_resolution_clock::now();
        divide_n_conquer(0, n - 1);
        stop = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop - start);
        
        if (duration1.count() > duration2.count()) {
            cout << "The value of n at which the recursive algorithm beats the brute force algorithm is: ";
            cout << n << "\n";
            n0 = n;
            break;
        }
    }
    arr.clear();
    for (int n = 1; n < 50; n ++) {
        int parity = rand() % 2;
        if (parity == 1) {
            value = -1 * (rand() % 1000 + 1);
        }
        else {
            value = rand() % 1000 + 1;
        }
        arr.push_back(value);
        
        auto start = high_resolution_clock::now(); 
        brute_force_max_sum(n);
        auto stop = high_resolution_clock::now(); 
        auto duration1 = duration_cast<microseconds>(stop - start);
        
        start = high_resolution_clock::now();
        divide_n_conquer_updated(0, n - 1);
        stop = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop - start);
        
        if (duration1.count() > duration2.count()) {
            cout << "The value of n at which the hybrid recursive algorithm beats the brute force algorithm is: ";
            cout << n << "\n";
            break;
        }
    }
    return 0;
}