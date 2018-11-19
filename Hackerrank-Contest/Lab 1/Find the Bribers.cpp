#include <bits/stdc++.h>
using namespace std;

pair <int, vector <int> > mergeCount(vector <int> a, vector <int> b) {
    
    int m = a.size(), n = b.size();
    vector <int> c(m + n);
    // current positions in A, B, C and inversion count
    int i = 0, j = 0, k = 0, count = 0;

    while (i < m && j < n) {
        // Case 1: move head of A into C, no inversions
        if (a[i] <= b[j]) {
            c[k] = a[i]; i ++; k ++;
        }
        // Case 2: move head of B into C, update count
        if (a[i] > b[j]) {
            c[k] = b[j]; j ++; k ++;
            count += (m - i);
        }
    }
    while (i < m) {
        c[k] = a[i]; i ++; k ++;
    }
    while (j < n) {
        c[k] = b[j]; j ++; k ++;
    }
    return {count, c};
}

pair < int, vector <int> > countInversions(vector <int> a) {
    
    if (a.size() == 1) {
        return {0, a};
    }
    
    vector <int> l, r;
    int i = 0, n, mid;
    n = a.size();
    mid = n/2;
    while (i < n) {
        if (i < mid) {
            l.push_back(a[i]);
        }
        else {
            r.push_back(a[i]);
        }
        i ++;
    }
    pair < int, vector <int> > left, right, merged;
    left = countInversions(l);
    right = countInversions(r);
    merged = mergeCount(left.second, right.second);
    int left_count = left.first;
    int right_count = right.first;
    int merge_count = merged.first;
    
    /*/
    printf("left:\n");
    for (int i = 0; i < l.size(); i ++) {
        printf("%d ", l[i]);
    }
    printf("\nright:\n");
    for (int i = 0; i < r.size(); i ++) {
        printf("%d ", r[i]);
    }
    printf("\n");
    printf("left:%d right:%d merged:%d\n", left_count, right_count, merge_count);
    
    printf("\n\n");
    //*/
    
    return {left_count + right_count + merge_count, merged.second};
}

int main () {
    
    int no_of_cases, no_of_people;
    scanf("%d", &no_of_cases);
    
    for (int case_no = 0; case_no < no_of_cases; case_no ++) {
        scanf("%d", &no_of_people);
        
        vector <int> final_state_of_queue(no_of_people), final_pos(no_of_people + 1);
        for (int pos = 0; pos < no_of_people; pos ++) {
            scanf("%d", &final_state_of_queue[pos]);
            // final_pos[i] denotes the index at which i-th person is in final state
            final_pos[final_state_of_queue[pos]] = pos + 1; // 1-indexed
        }
        
        // the problem can be reduced to the counting inversions problem
        // where we need to count the pair of indices (i, j)
        // such that i < j and a[i] > a[j]
        // this is because whenever a person bribes another person standing
        // ahead of him in the queue, a smaller value comes after a larger value 
        // Now, since each person can bribe atmost two other people
        // we find the no of elements smaller than a particular element 
        // which come after it, if they are more than two, then this is "Too Chaotic"
        // otherwise we increment the result by the no of smaller elements after it
        
        // O(n^2) approach used for subtask - 1 =>
        
        /*/
        int total_min_bribes = 0;
        
        for (int idx1 = 0; idx1 < no_of_people; idx1 ++) {
            
            int current_bribe = 0;
            
            for (int idx2 = idx1 + 1; idx2 < no_of_people; idx2 ++) {
                if (final_state_of_queue[idx2] < final_state_of_queue[idx1]) {
                    current_bribe ++;
                }
                if (current_bribe > 2) {
                    total_min_bribes = -1;
                    break;
                }
            }
            
            if (total_min_bribes == -1) {
                break;
            }
            total_min_bribes += current_bribe;
        }    
        //*/
        
        // O(nlogn) approach to count inversions using divide and conquer
        
        // first check whether possible
        bool possible = 1;
        for (int person = 1; person <= no_of_people; person ++) {
            if (person - final_pos[person] > 2) {
                possible = 0;
                break;
            }
        }
        
        if(!possible) {
            printf("Too chaotic\n");
            continue;
        }   
        
        int total_min_bribes = countInversions(final_state_of_queue).first;
        printf("%d\n", total_min_bribes);
    }
    
    return 0;
}