/*
 ID: RaresC
 LANG: C++
 TASK: runround
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>

using namespace std;
typedef unsigned long ul;

ul N;
int len;
int digits[30];
bool met[30];

void get_digits(ul n) {
    len = 0;
    int l = log10(n);
    while (n > 0) {
        digits[l-len] = n % 10;
        n /= 10;
        len++;
    }
}

bool unique_digits() {
    for (int i = 0; i < len; i++)
        for (int k = i+1; k < len; k++)
            if (digits[k] == 0 || digits[i] == digits[k])
                return false;
    return true;
}

int main() {
    
    ifstream fin ("runround.in");
    ofstream fout ("runround.out");
    
    fin >> N;
    N++;
    while (true) {
        memset(digits, 0, sizeof(digits));
        memset(met, false, sizeof(met));
        get_digits(N);
        
        if (!unique_digits())
        { N ++ ; continue; }
        
        int i = 0, indexN = 0;
        met[0] = true;
        while (i < len) {
            indexN = (indexN + digits[indexN]) % len;
            if (met[indexN]) {
                i++; break;
            }
            met[indexN] = true;
            i++;
        }
        if (i == len && indexN == 0)
            break;
        N++;
    }
    
    fout << N << "\n";
    
    return 0;
}