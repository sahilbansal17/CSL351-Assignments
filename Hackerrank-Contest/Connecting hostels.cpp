#include <bits/stdc++.h>
using namespace std;

// Union Find Disjoint Sets library written in OOP manner using both
// path compression and union by rank heuristics 
class UnionFind {
private: 
    vector <int> parent; // parent[i] is the parent of item i 
    vector <int> rank; // rank[i] is the upper bound on the height of tree rooted at item i
public:
    /* Constructor Function */
    UnionFind(int no_of_sets) {
        for (int set_idx = 0; set_idx < no_of_sets; set_idx ++) {
            parent.push_back(set_idx); // initially, parent[i] = i
            rank.push_back(0); // initially, height of each disjoint set = 0
        }
    }
    /* Find Operation: Finds the representative item of a set */ 
    int findSet(int val) {
        if (parent[val] == val) {
            return val;
        }
        // using the path compression heuristic, update the parent so that 
        // next time, the entire node->root path need not be taken
        return parent[val] = findSet(parent[val]);
    }
    /* isSameSet operation: Check whether two items are in the same set */
    bool isSameSet(int val1, int val2) {
        return findSet(val1) == findSet(val2);
    }
    /* Union Operation: joins two disjoint sets */
    void unionSet(int val1, int val2) {
        int set1 = findSet(val1), set2 = findSet(val2);
        if (rank[set1] > rank[set2]) {
            // the parent of smaller tree's root set to root of larger tree
            parent[set2] = set1; 
        }
        else if (rank[set1] < rank[set2]) {
            parent[set1] = set2;
        }
        else {
            // arbitratily set anyone's root to other's root
            parent[set1] = set2;
            // increase the rank of larger tree by one as both had same rank before union
            rank[set2] ++;
        }
    }
};

bool sortFunct(pair < pair <int, int>, int> p1, pair < pair <int, int>, int> p2) {
    // return the pair with smaller edge weight
    return p1.second <= p2.second;
}

int main () {
    
    int no_of_hostels, no_of_roads_planned, no_of_roads_to_construct;
    scanf("%d %d %d", &no_of_hostels, &no_of_roads_planned, &no_of_roads_to_construct);

    // edge list is a pair of ((from_hostel, to_hostel), cost_of_road)
    vector < pair < pair <int, int>, int> > edge_list; 
    
    int from_hostel, to_hostel, cost_of_road;
    for (int road_idx = 0; road_idx < no_of_roads_planned; road_idx ++) {
        scanf("%d %d %d", &from_hostel, &to_hostel, &cost_of_road);
        // using 0-indexing for hostels
        from_hostel --;
        to_hostel --;
        edge_list.push_back(make_pair(make_pair(from_hostel, to_hostel), cost_of_road));
    }
    
    // sort the edges (roads) based on their weights, i.e. the cost of the roads
    sort(edge_list.begin(), edge_list.end(), sortFunct);
    
    // Apply Kruskal's algorithm to find the minimum cost to connect hostels 
    // by building k roads such that n-k clusters are formed 
    // after k roads are built, build remaining q = (n-1)-k roads
    // to finally build a MST 
    
    long long cost_planned = 0, cost_future = 0;
    int roads_built = 0;
    
    UnionFind hostels(no_of_hostels);
    
    for (int edge_idx = 0; edge_idx < no_of_roads_planned; edge_idx ++) {
        from_hostel = edge_list[edge_idx].first.first;
        to_hostel = edge_list[edge_idx].first.second;
        cost_of_road = edge_list[edge_idx].second;
        
        // if the to hostels on the road are already connected, skip this edge 
        // otherwise perform a union operation on them and add to the appropriate 
        // cost, either cost_planned (for building k roads)
        // or cost_future (for building q roads)
        if (!hostels.isSameSet(from_hostel, to_hostel)) {
            hostels.unionSet(from_hostel, to_hostel);
            roads_built ++;
            if (roads_built >= no_of_roads_to_construct) {
                cost_future += cost_of_road;
            }
            else {
                cost_planned += cost_of_road;
            }
        }
    } 
    
    printf("%lld %lld", cost_planned, cost_future);
    return 0;
}