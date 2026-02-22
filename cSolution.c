#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int start;
    int end;
    ll weight;
} Interval;

int cmpInterval(const void *a, const void *b) {
    Interval x = *(const Interval *)a;
    Interval y = *(const Interval *)b;
    if (x.end != y.end) return x.end - y.end;
    return x.start - y.start;
}

int lowerBoundInt(const int *arr, int n, int target) {
    int left = 0;
    int right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

void nearestGreaterLeft(const ll *heights, int n, int *left) {
    int *stackIndex = (int *)malloc(sizeof(int) * n);
    int top = -1;

    for (int i = 0; i < n; i++) {
        while (top >= 0 && heights[stackIndex[top]] <= heights[i]) {
            top--;
        }

        if (top >= 0) {
            left[i] = stackIndex[top];
        } else {
            left[i] = -1;
        }

        stackIndex[++top] = i;
    }

    free(stackIndex);
}

void nearestGreaterRight(const ll *heights, int n, int *right) {
    int *stackIndex = (int *)malloc(sizeof(int) * n);
    int top = -1;

    for (int i = n - 1; i >= 0; i--) {
        while (top >= 0 && heights[stackIndex[top]] <= heights[i]) {
            top--;
        }

        if (top >= 0) {
            right[i] = stackIndex[top];
        } else {
            right[i] = n;
        }

        stackIndex[++top] = i;
    }

    free(stackIndex);
}

ll solve(const ll *heights, int n) {
    int *left = (int *)malloc(sizeof(int) * n);
    int *right = (int *)malloc(sizeof(int) * n);

    nearestGreaterLeft(heights, n, left);
    nearestGreaterRight(heights, n, right);

    Interval *intervals = (Interval *)malloc(sizeof(Interval) * n);
    for (int i = 0; i < n; i++) {
        int start = left[i] + 1;
        int end = right[i] - 1;
        ll width = (ll)(end - start + 1);
        ll weight = heights[i] * width;

        intervals[i].start = start;
        intervals[i].end = end;
        intervals[i].weight = weight;
    }

    qsort(intervals, n, sizeof(Interval), cmpInterval);

    int *ends = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        ends[i] = intervals[i].end;
    }

    ll *dp = (ll *)calloc(n + 1, sizeof(ll));

    for (int i = 1; i <= n; i++) {
        int start = intervals[i - 1].start;
        ll weight = intervals[i - 1].weight;

        int countNonOverlap = lowerBoundInt(ends, n, start);

        ll takeCurrent = dp[countNonOverlap] + weight;
        ll skipCurrent = dp[i - 1];
        dp[i] = (skipCurrent > takeCurrent) ? skipCurrent : takeCurrent;
    }

    ll answer = dp[n];

    free(left);
    free(right);
    free(intervals);
    free(ends);
    free(dp);

    return answer;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    ll *heights = (ll *)malloc(sizeof(ll) * n);
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &heights[i]) != 1) {
            free(heights);
            return 0;
        }
    }

    ll answer = solve(heights, n);
    printf("%lld\n", answer);

    free(heights);
    return 0;
}
