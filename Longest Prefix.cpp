/*
 ID: RaresC
 LANG: C++
 TASK: prefix
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;

#define MAX 200010
typedef unsigned long ul;
string prefixes[201]; int p;
char data[MAX];
bool pref_works[MAX];
int N;

bool cmp_strings (int start, int p) {
    ul i_end = start + prefixes[p].length();
    
    int k = 0;
    for (int i = start; i < i_end; i++) {
        if (data[i] != prefixes[p][k])
            return false;
        k++;
    }
    
    return true;
}

int main() {
    
    ifstream fin ("prefix.in");
    ofstream fout ("prefix.out");
    
    string s; fin >> s;
    while (s != ".") {
        prefixes[p] = s;
        fin >> s;
        p++;
    }
    // read in string, one line at a time.
    string d;
    int len = 0;
    while (fin >> d) {
        int k = 0;
        for (int i = len; i < len + d.length(); i++) {
            data[i] = d[k];
            k++;
        }
        len += d.length();
    }
    
    // d.p.
    ul best = 0;
    for (int i = 0; i < len; i++) {
        if (pref_works[i] || i == 0)
            for (int k = 0; k < p; k++) {
                // check for each prefix if we can add it on
                if (cmp_strings(i, k)) {
                    ul extend = prefixes[k].length();
                    pref_works[i+extend] = true;
                    if (i+k > best) best = i+extend;
                }
            }
    }
    
    fout << best << "\n";
    
    return 0;
}