/*
 ID: RaresC
 LANG: C++
 TASK: cowtour
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <iomanip>
using namespace std;
typedef long long ll;
#define MAX 151
#define INF 10000000000000

struct Points {
    double x, y;
    int index;
};
Points point[MAX];
double diameter[MAX];
double dist[MAX][MAX];
double longest_path[MAX];
int N;

double distance_to_p(int i, int k) {
    double x = point[i].x - point[k].x;
    double y = point[i].y - point[k].y;
    return pow(x*x + y*y, 0.5);
}

int main() {
    
    ifstream fin ("cowtour.in");
    ofstream fout ("cowtour.out");
    
    fin >> N;
    for (int i = 0; i < N; i++) {
        int x, y;
        fin >> x >> y;
        point[i].x = x;
        point[i].y = y;
    }
    for (int i = 0; i < N; i++) {
        string s; fin >> s;
        for (int k = 0; k < N; k++) {
            if (i == k)
            { dist[i][k] = 0; continue; }
            
            char c = s[k];
            if (c == '0')
                dist[i][k] = dist[k][i] = INF;
            else
                dist[i][k] = dist[k][i] = distance_to_p(i, k);
        }
    }
    
    // floyd - warshall : get distances from all points i, to all points k.
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < N; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    dist[j][i] = dist[i][j];
                }
    
    // mark all the pastures.
    int t = 1;
    for (int i = 0; i < N; i++) {
        if (point[i].index) continue;
        point[i].index = t;
        for (int k = 0; k < N; k++) {
            if (dist[i][k] != INF)
                point[k].index = t;
        }
        t++;
    }
    
    // longest distance from one point within a pasture
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            if (dist[i][k] == INF)
                continue;
            if (dist[i][k] > longest_path[i])
                longest_path[i] = dist[i][k];
            
            if (longest_path[i] > diameter[point[i].index-1])
                diameter[point[i].index-1] = longest_path[i];
        }
    }
    
    
    // connect point i to point k if they're from different pastures.
    double best_diam = INF;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            if (point[i].index == point[k].index) continue;
            double diam=0.0;
            diam = longest_path[i] + longest_path[k] + distance_to_p(i, k);
            if (diam < diameter[point[i].index-1])
                diam = diameter[point[i].index-1];
            if (diam < diameter[point[k].index-1])
                diam = diameter[point[k].index-1];
            
            if (diam < best_diam)
                best_diam = diam;
        }
    }
    
    fout << fixed << setprecision(6);
    fout << best_diam << "\n";
    
    return 0;
}
