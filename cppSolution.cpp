#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Interval {
    int start;
    int end;
    ll weight;
};

vector<int> nearestGreaterLeft(const vector<ll>& heights) {
    int n = (int)heights.size();
    vector<int> left(n, -1);
    vector<int> stackIndex;

    for (int i = 0; i < n; i++) {
        while (!stackIndex.empty() && heights[stackIndex.back()] <= heights[i]) {
            stackIndex.pop_back();
        }

        if (!stackIndex.empty()) {
            left[i] = stackIndex.back();
        }

        stackIndex.push_back(i);
    }

    return left;
}

vector<int> nearestGreaterRight(const vector<ll>& heights) {
    int n = (int)heights.size();
    vector<int> right(n, n);
    vector<int> stackIndex;

    for (int i = n - 1; i >= 0; i--) {
        while (!stackIndex.empty() && heights[stackIndex.back()] <= heights[i]) {
            stackIndex.pop_back();
        }

        if (!stackIndex.empty()) {
            right[i] = stackIndex.back();
        }

        stackIndex.push_back(i);
    }

    return right;
}

ll solve(const vector<ll>& heights) {
    int n = (int)heights.size();

    vector<int> left = nearestGreaterLeft(heights);
    vector<int> right = nearestGreaterRight(heights);

    vector<Interval> intervals;
    intervals.reserve(n);

    for (int i = 0; i < n; i++) {
        int start = left[i] + 1;
        int end = right[i] - 1;
        ll width = (ll)(end - start + 1);
        ll weight = heights[i] * width;

        Interval current;
        current.start = start;
        current.end = end;
        current.weight = weight;
        intervals.push_back(current);
    }

    sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
        if (a.end != b.end) return a.end < b.end;
        return a.start < b.start;
    });

    int m = (int)intervals.size();
    vector<int> ends(m);
    for (int i = 0; i < m; i++) {
        ends[i] = intervals[i].end;
    }

    vector<ll> dp(m + 1, 0);

    for (int i = 1; i <= m; i++) {
        int start = intervals[i - 1].start;
        ll weight = intervals[i - 1].weight;

        int countNonOverlap = (int)(lower_bound(ends.begin(), ends.end(), start) - ends.begin());

        ll takeCurrent = dp[countNonOverlap] + weight;
        ll skipCurrent = dp[i - 1];

        dp[i] = max(skipCurrent, takeCurrent);
    }

    return dp[m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    ll answer = solve(heights);
    cout << answer << '\n';

    return 0;
}
