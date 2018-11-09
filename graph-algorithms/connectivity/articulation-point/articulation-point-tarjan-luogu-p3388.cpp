#include <bits/stdc++.h>
using namespace std;

//{{{
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
//}}}

const int N = 100010, E = N << 1;
int n, m, e0[N], e1[E], dst[E], dfn[N], low[N], disc = 0;
bool ap[N], vis[N];

void tarjan(int u, int fa) {
    low[u] = dfn[u] = ++disc;
    vis[u] = true;
    int ccnt = 0;
    for (int i = e0[u]; i; i = e1[i]) {
        int v = dst[i];
        if (v == fa) continue;  // IMPORTANT: skip the parent node
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (fa && low[v] >= dfn[u])
                ap[u] = 1;
            else if (!fa)
                ++ccnt;
        } else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    vis[u] = false;
    if (!fa && ccnt > 1) ap[u] = true;  // IMPORTANT: the root node is an articulation point if it has a least two children
}

int main() {
    n = geti();
    m = geti();
    for (int i = 1; i <= m; ++i) {
        int x = geti(), y = geti();
        e1[(i << 1) - 1] = e0[x];
        e1[i << 1] = e0[y];
        e0[x] = (i << 1) - 1;
        e0[y] = i << 1;
        dst[(i << 1) - 1] = y;
        dst[i << 1] = x;
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i, 0);
    putln(accumulate(ap + 1, ap + 1 + n, 0));
    for (int i = 1; i <= n; ++i)
        if (ap[i]) putsp(i);
    putchar('\n');
    return 0;
}
