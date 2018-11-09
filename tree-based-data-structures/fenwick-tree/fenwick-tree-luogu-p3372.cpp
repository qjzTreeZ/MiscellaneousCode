#include <bits/stdc++.h>
using namespace std;

inline int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long getll() {
    int f = 0;
    long long x;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

template <typename T>
void puti(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

template <typename T>
void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
void putln(T x) {
    puti(x);
    putchar('\n');
}

const int N = 100010;
int n, m;
long long s[N], bit1[N], bit2[N];

inline void add(long long *bit, int k, long long v) {
    while (k <= n) {
        bit[k] += v;
        k += k & -k;
    }
}

inline long long qry(long long *bit, int k) {
    long long ret = 0;
    while (k) {
        ret += bit[k];
        k &= k - 1;
    }
    return ret;
}

int main() {
    n = geti();
    m = geti();
    long long sum = 0;
    for (int i = 1; i <= n; ++i) s[i] = sum += getll();
    while (m--) {
        int o = geti(), x = geti(), y = geti();
        if (o == 1) {
            long long k = getll();
            add(bit1, x, k);
            add(bit1, y + 1, -k);
            add(bit2, x, k * x);
            add(bit2, y + 1, -k * (y + 1));
        } else
            putln(s[y] + (y + 1) * qry(bit1, y) - qry(bit2, y) - s[x - 1] - x * qry(bit1, x - 1) + qry(bit2, x - 1));
    }
    return 0;
}