#include "secret.h"

int prefix[1000][1000], n;

void populate(int L, int R, int A[]) {
    int mid = (L + R) / 2;
    prefix[mid][mid] = A[mid];
    prefix[mid + 1][mid + 1] = A[mid + 1];

    for (int i = mid + 2; i <= R; i++) prefix[mid + 1][i] = Secret(prefix[mid + 1][i - 1], A[i]);
    for (int i = mid - 1; i >= L; i--) prefix[mid][i] = Secret(A[i], prefix[mid][i + 1]);

    if (L < mid) populate(L, mid, A);
    if (mid + 1 < R) populate(mid + 1, R, A);
}

void Init(int N, int A[]) {
    n = N;
    populate(0, N - 1, A);
}

int Query(int L, int R) {
    int a = 0, b = n - 1;

    while (a != b) {
        int mid = (a + b) / 2;
        if (mid >= L && mid < R) return Secret(prefix[mid][L], prefix[mid + 1][R]);
        else if (mid == R) return prefix[mid][L];
        else if (mid < L) a = mid + 1;
        else b = mid;
    }

    return prefix[a][a];
}
