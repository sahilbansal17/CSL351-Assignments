#include <bits/stdc++.h>
using namespace std;

int prisoners_required(int check, vector <int> a) {
    int current_acc_diff = 0, required = 1;
    for (int i = 1; i < a.size(); i ++) {
        int diff = a[i] - a[i - 1];
        current_acc_diff += diff;
        if (current_acc_diff >= check) {
            required ++;
            current_acc_diff = 0;
        }
    }
    return required;
}

int main () {
    
    int no_of_cases, no_of_cells, no_of_inmates;
    scanf("%d", &no_of_cases);
    
    for (int case_no = 0; case_no < no_of_cases; case_no ++) {
        scanf("%d %d", &no_of_cells, &no_of_inmates);
        
        vector <int> stall_locations(no_of_cells);
        for (int loc = 0; loc < no_of_cells; loc ++) {
            scanf("%d", &stall_locations[loc]);
        }
        
        // sort the positions
        sort(stall_locations.begin(), stall_locations.end());
        
        // perform binary search the answer on the largest minimum distance required (answer)
        
        int smallest_min_distance = 0, largest_min_distance = 1000000000, answer, check;
        while (smallest_min_distance <= largest_min_distance) {
            check = (smallest_min_distance + largest_min_distance)/2;
            if (prisoners_required(check, stall_locations) < no_of_inmates) {
                // we must decrease the largest_min_distance
                largest_min_distance = check - 1;
            }
            else {
                answer = check;
                // we can improve our answer 
                smallest_min_distance = check + 1;
            }
            // printf("mid: %d, required: %d\n", check, prisoners_required(check, stall_locations));
        }
        printf("%d\n", answer);
     }
    
    return 0;
}