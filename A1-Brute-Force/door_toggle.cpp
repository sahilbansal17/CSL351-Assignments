#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = 100;
    vector <bool> sw(n + 1, 0);
    
    for (int start = 1; start <= n; start ++) {
        for (int current = start; current <= n; current += start) {
            sw[current] = !sw[current];
        }
    }
    
    // print the open doors 
    for (int door = 1; door <= n; door ++) {
        if (sw[door] == 1) {
            cout << door << " ";
        }
    }
    
    // conclusion: only those doors are open that have number which
    // is a perfect square
    return 0;
}