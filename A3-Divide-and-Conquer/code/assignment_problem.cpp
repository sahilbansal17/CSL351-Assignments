#include <bits/stdc++.h>
using namespace std;

int cost[4][4] = {{15, 12, 6, 3}, {9, 9, 5, 5}, {5, 8, 11, 8}, {3, 6, 9, 14}};
int min_cost = INT_MAX;
int n;
bool done[4] = {false};

void assign (int i, int c) {
    if (i == n) {
        if (c < min_cost) {
            // cout << c << endl;
            min_cost = c;
        }
        return ;
    }
    for (int j = 0; j < n; j ++) {
        if (!done[j]) {
            done[j] = true;
            assign (i + 1, c + cost[i][j]);
            done[j] = false;
        }
    }
}

int main() {
    n = 4;
    assign (0, 0);
    cout << "The minimum assignment cost is: " << min_cost << endl;
    return 0;
}