/*
 ID: RaresC
 LANG: C++
 TASK: frac1
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

#define MAX 12810
int N;
struct Fraction {
    int numerator;
    int denominator;
}fraction[MAX];

bool cmp (Fraction const& f1, Fraction const& f2) {
    if (f1.numerator*f2.denominator - f2.numerator*f1.denominator < 0) return true;
    return false;
}

bool relative_prime (int num, int denom) {
    for (int i = 2; i <= num; i++)
        if (num % i == 0 && denom % i == 0)
            return false;
    return true;
}

int main() {
    
    ifstream fin ("frac1.in");
    ofstream fout ("frac1.out");
    
    fin >> N;
    int amnt = 0;
    for (int d = 1; d <= N; d++)
        for (int n = 1; n < d; n++)
            if (relative_prime(n, d)) {
                fraction[amnt].numerator = n;
                fraction[amnt].denominator = d;
                amnt++;
            }
    
    sort(fraction, fraction+amnt, cmp);
    
    fout << "0/1\n";
    for (int i = 0; i < amnt; i++)
        fout << fraction[i].numerator << "/" << fraction[i].denominator << "\n";
    fout << "1/1\n";
    
    return 0;
}