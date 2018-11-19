#include <bits/stdc++.h>

using namespace std;

/* Template file for Online Algorithmic Competitions */
/* Typedefs */
    /* Basic types */
    typedef long long           ll;
    typedef long double         ld;
    typedef unsigned long long ull;
    /* STL containers */
    typedef vector <int>    vi;
    typedef vector <ll>     vll;
    typedef pair <int, int> pii;
    typedef pair <ll, ll>   pll;
    typedef vector < pii >  vpii;
    typedef vector < pll >  vpll;
    typedef vector <string> vs;
    typedef vector < vi >   vvi;
    typedef vector < vll >  vvll;
    typedef vector < vpii > vvpii;
    typedef set <int>       si;
/* Macros */
    /* Loops */
    #define fl(i, a, b)     for(int i(a); i < (b); i ++)
    #define rep(i, n)       fl(i, 0, n)
    #define rep1(i, n)      fl(i, 1, n)
    #define rfl(i, a, b)    for(int i(a); i >= (b); i --)
    /* Algorithmic functions */
    #define srt(v)          sort((v).begin(), (v).end())
    /* STL container methods */
    #define pb              push_back
    #define mp              make_pair
    #define eb              emplace_back
    /* String methods */
    #define dig(i)          (s[i] - '0')
    #define slen(s)         s.length()
    /* Shorthand notations */
    #define F               first
    #define S               second
    #define re              return 
    #define sz(x)           ((int) (x).size())
    #define all(x)          (x).begin(), (x).end()
    #define sqr(x)          ((x) * (x))
    #define fill(x, y)      memset(x, y, sizeof(x))
    #define endl            '\n'
    /* distance_and_coordinatehedistance_and_coordinateical */
    #define IINF            0x3f3f3f3f
    #define oo              1000111000111000111LL
    #define PI              3.14159265358979323
    /* Debugging purpose */
    #define trace1(x)                cerr << #x << ": " << x << endl
    #define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl
    #define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl
    #define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl
    #define trace5(a, b, c, d, e)    cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl
    #define trace6(a, b, c, d, e, f) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl
    /* Fast Input Output */
    #define FAST_IO                  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
/* Constants */
    const ll MOD = 1000000007LL;
    const int MAX = 710;
/* Templates */
template<class T> T abs(T x) { re x > 0 ? x : -x; }
template<typename T> T gcd(T a, T b){ if(b == 0) return a; return gcd(b, a % b); }
template<typename T> T power(T x, T y, ll m = MOD){T ans = 1; x %= m; while(y > 0){ if(y & 1LL) ans = (ans * x)%m; y >>= 1LL; x = (x*x)%m; } return ans%m; }
 

vvll mat (MAX, vll (MAX, 0));
vvll shortest_dist (MAX, vll (MAX, oo));

class HeapOfDistanceAndCoordinates {
private:
    int size; 
    vector < pair <ll, pii> > distance_and_coordinate;

    int leftChild(int i) {
        int left = 2 * i + 1;
        if (left >= size) {
            return -1;
        }
        return left;
    }

    int rightChild(int i) {
        int right = 2 * i + 2;
        if (right >= size) {
            return -1;
        }
        return right;
    }

    void heapify(int loc) {
        pair <ll, pii> temp;
        int l, r, min;
        l = leftChild(loc);
        r = rightChild(loc);
        if (l != -1 && distance_and_coordinate[l].F < distance_and_coordinate[loc].F) {
            min = l;
        } else {
            min = loc;
        }
        if (r != -1 && distance_and_coordinate[r].F < distance_and_coordinate[min].F) {
            min = r;
        }
        if (min != loc) {
            //swap the distance_and_coordinate[min] with distance_and_coordinate[loc]
            temp = distance_and_coordinate[min];
            distance_and_coordinate[min] = distance_and_coordinate[loc];
            distance_and_coordinate[loc] = temp;
            heapify(min);
        }
        return;
    }
public:
    HeapOfDistanceAndCoordinates() {
        size = 0; //since there are no distance_and_coordinate initially
    }

    void display() {
        for (int i = 0; i < distance_and_coordinate.size(); i++) {
            cout << distance_and_coordinate[i].F << " " ;
        }
        cout << endl;
    }

    void insert(pair <ll, pii> d_and_c) {
        size++;
        int index = size - 1;
        distance_and_coordinate.pb({oo, {-1, -1}});
        //parent is at (index-1)/2 since starting from 0th index
        while (index > 0 && d_and_c.F < distance_and_coordinate[(index - 1) / 2].F) {
            distance_and_coordinate[index] = distance_and_coordinate[(index - 1) / 2];
            index = (index - 1) / 2;
        }
        distance_and_coordinate[index] = (d_and_c); //right position for this distance and coordinate 
    }

    /*
    vector <pii> top_coordinate() {
        return distance_and_coordinate[0].S;
    } 
    */   

    pii deleteMin() {
        if (size == 0) { //no coordinate can be deleted
            return {-1, -1};
        }
        pii res = distance_and_coordinate[0].S;
        distance_and_coordinate[0] = distance_and_coordinate[size - 1];
        distance_and_coordinate[size - 1].F = oo;
        distance_and_coordinate[size - 1].S = {-1,-1};
        size--;
        //call heapify 
        heapify(0);

        return res;
    }

    bool isEmpty(){
        return size == 0;
    }

};

int main(){

    #ifndef ONLINE_JUDGE
    freopen("/Users/sahilbansal/Desktop/input.txt","r",stdin);
    freopen("/Users/sahilbansal/Desktop/output.txt","w",stdout);
    freopen("/Users/sahilbansal/Desktop/error.txt","w",stderr);
    #endif

    FAST_IO;

    int n;
    cin >> n;

    rep (i, n) {
        rep (j, n) {
            cin >> mat[i][j];
        }
    }

    // Applying standard Dijkstra algorithm to find the shortest path from (0, 0) to (n - 1, n - 1)!

    shortest_dist[0][0] = mat[0][0];
        
    HeapOfDistanceAndCoordinates my_heap;
    my_heap.insert({shortest_dist[0][0], {0, 0}});

    // current coordinate, topmost element from the heap
    pii cur_coordinate;

    int x, y; // short variable names to refer to x and y coordinates
    while (!my_heap.isEmpty()) {

        // get the current coordinate
        cur_coordinate = my_heap.deleteMin();
        x = cur_coordinate.F;
        y = cur_coordinate.S;
        // can move either to the right, left up or down

        // right 
        if (x < n && y + 1 < n && shortest_dist[x][y + 1] > shortest_dist[x][y] + mat[x][y + 1]) {
            shortest_dist[x][y + 1] = shortest_dist[x][y] + mat[x][y + 1];
            my_heap.insert({shortest_dist[x][y + 1], {x, y + 1}});
        }
        // left 
        if (x >= 0 && y - 1 >= 0 && shortest_dist[x][y - 1] > shortest_dist[x][y] + mat[x][y - 1]) {
            shortest_dist[x][y - 1] = shortest_dist[x][y] + mat[x][y - 1];
            my_heap.insert({shortest_dist[x][y - 1], {x, y - 1}});
        }
        // up 
        if (x - 1 >= 0 && y >= 0 && shortest_dist[x - 1][y] > shortest_dist[x][y] + mat[x - 1][y]) {
            shortest_dist[x - 1][y] = shortest_dist[x][y] + mat[x - 1][y];
            my_heap.insert({shortest_dist[x - 1][y], {x - 1, y}});
        }
        // down 
        if (x + 1 < n && y < n && shortest_dist[x + 1][y] > shortest_dist[x][y] + mat[x + 1][y]) {
            shortest_dist[x + 1][y] = shortest_dist[x][y] + mat[x + 1][y];
            my_heap.insert({shortest_dist[x + 1][y], {x + 1, y}});
        }
    }

    /*/
    rep (i, n) {
        rep (j, n) {
            cerr << shortest_dist[i][j] << " ";
        }
        cerr << endl;
    }
    //*/

    cout << shortest_dist[n - 1][n - 1] << endl;
    return 0;
}