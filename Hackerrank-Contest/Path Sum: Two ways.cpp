#include <bits/stdc++.h>
using namespace std;

// Recursive Dynamic Programming with Memoization technique used, Top Down approach

int size_of_matrix;
vector < vector <long long> > matrix(1005, vector <long long> (1005));
// min_sum[i][j] denotes the minimum sum to reach the cell (i, j) from (0, 0)
vector < vector <long long> > min_sum(1005, vector <long long> (1005, -1));

// i, j is the location for which answer is required
long long solve (int i, int j) {
    // value already memoized
    if (min_sum[i][j] != -1) {
        return min_sum[i][j];
    }
    // base case
    if (i == 0 && j == 0) {
        return min_sum[i][j] = matrix[i][j];
    }
    // any cell not in first row or first column
    if (i - 1 >= 0 && j - 1 >= 0) {
        return min_sum[i][j] = matrix[i][j] + min(solve(i - 1, j), solve(i, j - 1));
    }
    // for cells in the first column, j = 0
    if (i - 1 >= 0) {
        return min_sum[i][j] = matrix[i][j] + solve(i - 1, j);
    }
    // for cells in the first row, i = 0
    if (j - 1 >= 0) {
        return min_sum[i][j] = matrix[i][j] + solve(i, j - 1);
    }
    return min_sum[i][j];
} 
int main () {
    
    scanf("%d", &size_of_matrix);
    
    for (int row_idx = 0; row_idx < size_of_matrix; row_idx ++) {
        for (int col_idx = 0; col_idx < size_of_matrix; col_idx ++) {
            scanf("%lld", &matrix[row_idx][col_idx]);
        }
    }
    
    // the recurrence relation to solve this problem is: 
    // min_sum[i][j] = matrix[i][j] + min (min_sum[i - 1][j], min_sum[i][j - 1])
    
    printf("%lld\n", solve(size_of_matrix - 1, size_of_matrix - 1));
    
    // To UNCOMMENT AND PRINT THE MIN_SUM 2D TABLE, SIMPLY PUT A FORWARD SLASH '/' IN THE STARTING OF THE NEXT LINE
    /*/
    for (int row_idx = 0; row_idx < size_of_matrix; row_idx ++) {
        for (int col_idx = 0; col_idx < size_of_matrix; col_idx ++) {
            printf("%lld ", min_sum[row_idx][col_idx]);
        }
        printf("\n");
    }
    //*/
    return 0;
}