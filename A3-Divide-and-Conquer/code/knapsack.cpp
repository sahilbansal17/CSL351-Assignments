#include <bits/stdc++.h>
using namespace std;
int n;
// assume the value of n to be less than 100
int wt[100], c[100];
int cnt[100];
// also assume W (capacity of knapsack) to be less than 100
int solved[102];
int chosen[101];
int knapsack (int W) {
    if (solved[W] != -1) {
        return solved[W];
    }
    int maxcost = -1;
    for (int i = 0; i < n; i ++) {
        if (wt[i] <= W && c[i] + knapsack(W - wt[i]) > maxcost) {
            maxcost = c[i] + knapsack(W - wt[i]);
            chosen[W] = i;
        }
    }
    solved[W] = maxcost;
    return maxcost;
}

void getCounts (int W) {
    while (W > 0) {
        if (chosen[W] == -1) {
            break;
        }
        int item = chosen[W];
        W -= wt[chosen[W]];
        cnt[item] ++;
    }
}
int main() {

    cout << "Please enter the value of n: " ;
    cin >> n;
    
    cout << "Please enter the weights:\n";
    for (int i = 0; i < n; i ++) {
        cin >> wt[i];
    }
    
    cout << "Please enter the costs:\n";
    for (int i = 0; i < n; i ++) {
        cin >> c[i];
    }
    
    int W;
    cout << "Please enter the capacity of the knapsack: ";
    cin >> W;
    
    for (int i = 0; i < 100; i ++) {
        cnt[i] = 0;
        solved[i] = -1;
        chosen[i] = -1;
    }
    
    cout << "The maximum cost possible is: " << knapsack(W);
    
    getCounts(W);
    cout << "\nThe chosen items are:\n";
    cout << "Item index\tCount\n";
    for (int i = 0; i < n; i ++) {
        if (cnt[i] > 0) {
            cout << i << "\t" << cnt[i] << "\n";
        }
    } 
    
    return 0;
}