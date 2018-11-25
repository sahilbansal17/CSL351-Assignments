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
    /* Mathematical */
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
    const int MAX = 11;
/* Templates */
template<class T> T abs(T x) { re x > 0 ? x : -x; }
template<typename T> T gcd(T a, T b){ if(b == 0) return a; return gcd(b, a % b); }
template<typename T> T power(T x, T y, ll m = MOD){T ans = 1; x %= m; while(y > 0){ if(y & 1LL) ans = (ans * x)%m; y >>= 1LL; x = (x*x)%m; } return ans%m; }

char mat[MAX][MAX];
int count_row[MAX][MAX] = {{0}}, count_col[MAX][MAX] = {{0}};
vs words;

int total_words = 0;
bool fillWords(int word_id) {

    // if all words have been filled, return 1
    if (word_id == total_words) {
        return 1;
    }

    string word = words[word_id];
    int word_len = slen(word);

    /* PRINT THE MATRIX
    rep1 (i, 11) {
        rep1 (j, 11) {
            cerr << mat[i][j];
        }
        cerr << endl;
    }
    cerr << endl;
    //*/

    // find if there is any possiblity to fill the current word in a column

    // i: column_index, j: row_index
    rep1 (i, 11) {
        fl (j, word_len, 11) {
            if (count_col[j][i] == word_len) {
                // this is a possible position since there are (-) with count equal to word_len ending at this position in the column

                // check if there is any conflict in this position
                int pos = 0;
                bool conflict = false;
                fl (k, j - word_len + 1, j + 1) {
                    if (mat[k][i] == '-' || mat[k][i] == word[pos]) {
                        pos ++;
                        continue;
                    }
                    else {
                        conflict = true;
                        break;
                    }
                }

                // if there is no conflict, fit the word in this place and recurse to fill the remaining words
                if (!conflict) {
                    // fit the word
                    pos = 0;

                    // store the original word in case this combination failed
                    string original_word; 
                    fl (k, j - word_len + 1, j + 1) {
                        original_word += mat[k][i];
                        mat[k][i] = word[pos];
                        pos ++;
                    }

                    // recurse and check if all words filled 
                    if (fillWords (word_id + 1) == 1) {
                        return 1;
                    }
                    else {
                        // take back this word filled, i.e. restore the original word in this place 
                        pos = 0;
                        fl (k, j - word_len + 1, j + 1) {
                            mat[k][i] = original_word[pos];
                            pos ++;
                        }
                    }
                }
            }
        }
    }


    // find if there is any possiblity to fill the current word in a row

    // i: row_index, j: column_index
    rep1 (i, 11) {
        fl (j, word_len, 11) {
            if (count_row[i][j] == word_len) {
                // this is a possible position since there are (-) with count equal to word_len ending at this position in the row

                // check if there is any conflict in this position
                int pos = 0;
                bool conflict = false;
                fl (k, j - word_len + 1, j + 1) {
                    if (mat[i][k] == '-' || mat[i][k] == word[pos]) {
                        pos ++;
                        continue;
                    }
                    else {
                        conflict = true;
                        break;
                    }
                }

                // if there is no conflict, fit the word in this place and recurse to fill the remaining words
                if (!conflict) {
                    // fit the word
                    pos = 0;

                    // store the original word in case this combination failed
                    string original_word; 
                    fl (k, j - word_len + 1, j + 1) {
                        original_word += mat[i][k];
                        mat[i][k] = word[pos];
                        pos ++;
                    }

                    // recurse and check if all words filled 
                    if (fillWords (word_id + 1) == 1) {
                        return 1;
                    }
                    else {
                        // take back this word filled, i.e. restore the original word in this place 
                        pos = 0;
                        fl (k, j - word_len + 1, j + 1) {
                            mat[i][k] = original_word[pos];
                            pos ++;
                        }
                    }
                }
            }
        }
    }
    // if no possible combination worked out, return 0
    return 0;
}
int main(){

    //*/
    #ifndef ONLINE_JUDGE
    freopen("/Users/sahilbansal/Desktop/input.txt","r",stdin);
    freopen("/Users/sahilbansal/Desktop/output.txt","w",stdout);
    freopen("/Users/sahilbansal/Desktop/error.txt","w",stderr);
    #endif
    //*/
    
    FAST_IO;

    // input the 10x10 character matrix
    rep1 (i, 11) {
        rep1 (j, 11) {
            cin >> mat[i][j];
        }
    }

    /* PRINT THE MATRIX
    rep1 (i, 11) {
        rep1 (j, 11) {
            cerr << mat[i][j];
        }
        cerr << endl;
    }
    cerr << endl;
    //*/

    // preprocess the no. of -ve signs in the matrix in the rows and columns ending at a particular position 

    // count_row[i][j] denotes the count of (-) till from j-th position in i-th row

    // count_col[i][j] denotes the count of (-) ending at i-th position in j-th column


    rep1 (i, 11) {
        rep1 (j, 11) {
            if (mat[i][j] == '-') {
                count_row[i][j] = count_row[i][j - 1] + 1;
            }
            else {
                count_row[i][j] = 0;
            }

            if (mat[j][i] == '-') {
                count_col[j][i] = count_col[j - 1][i] + 1;
            }
            else {
                count_col[j][i] = 0;
            }
        }
    }

    /* PRINT THE count_row matrix
    rep1 (i, 11) {
        rep1 (j, 11) {
            cerr << count_row[i][j] << " ";
        }
        cerr << endl;
    }
    cerr << endl;
    //*/

    /* PRINT THE count_col matrix
    rep1 (i, 11) {
        rep1 (j, 11) {
            cerr << count_col[i][j] << " ";
        }
        cerr << endl;
    }
    cerr << endl;
    //*/

    // take the words as input
    string word_line;
    cin >> word_line;

    string word;
    int line_idx = 0;
    while (line_idx < slen(word_line)) {
        if (word_line[line_idx] == ';') {
            words.pb(word);
            word.clear();
            total_words ++;
        }
        else {
            word += word_line[line_idx];
        }
        line_idx ++;
    }
    // take care of the last word
    words.pb(word);
    word.clear();
    total_words ++;

    /*/ PRINT THE WORDS 
    rep (i, sz(words)) {
        cerr << words[i] << endl;
    }
    //*/

    // call the main function to fill the words 
    if (fillWords(0) == 1) {
        rep1 (i, 11) {
            rep1 (j, 11) {
                cout << mat[i][j];
            }
            cout << endl;
        }
        cout << endl;    
    }
    else {
        cout << "Error";
    }

    return 0;
}