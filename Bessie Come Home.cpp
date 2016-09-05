/*
 ID: RaresC
 LANG: C++
 TASK: comehome
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <iomanip>
using namespace std;
typedef long long ll;
#define MAX 52
#define INF 1000000

bool start_cow[MAX];
int dist[MAX][MAX];
int P, ans=INF;

int convert(char c) {
    if (c >= 'A' && c <= 'Z')
        return  c-'A';
    else
        return c-'a'+26;
}

int main() {
    
    ifstream fin ("comehome.in");
    ofstream fout ("comehome.out");
    
    for (int i = 0; i < MAX; i++)
        for (int k = 0; k < MAX; k++)
            if (i != k)
                dist[i][k] = INF;
            else dist[i][k] = 0;
    
    fin >> P;
    for (int i = 0; i < P; i++) {
        char a, b; int d;
        fin >> a >> b >> d;
        int x = convert(a);
        int y = convert(b);
        
        if (a >= 'A' && a < 'Z')
            start_cow[x] = true;
        if (b >= 'A' && b < 'Z')
            start_cow[y] = true;
        
        if (dist[x][y] > d)
            dist[x][y] = dist[y][x] = d;
    }
    
    // shortest path, Floyd-Warshall algorithm
    for (int k = 0; k < MAX; k++)
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[j][i] = dist[i][k] + dist[k][j];
    
    
    // find path closest to 'Z';
    char c = 'Z';
    for (int i = 0; i < MAX; i++)
        if (ans > dist[i]['Z'-'A'] && start_cow[i]) {
            ans = dist[i]['Z'-'A'];
            c = (char) i+'A';
        }
    
    fout << c << " " << ans << "\n";
    
    return 0;
}

