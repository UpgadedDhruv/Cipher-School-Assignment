import bisect


def nearest_greater_left(heights):
    n = len(heights)
    left = [-1] * n
    stack_index = []

    for i in range(n):
        while stack_index and heights[stack_index[-1]] <= heights[i]:
            stack_index.pop()

        if stack_index:
            left[i] = stack_index[-1]

        stack_index.append(i)

    return left


def nearest_greater_right(heights):
    n = len(heights)
    right = [n] * n
    stack_index = []

    for i in range(n - 1, -1, -1):
        while stack_index and heights[stack_index[-1]] <= heights[i]:
            stack_index.pop()

        if stack_index:
            right[i] = stack_index[-1]

        stack_index.append(i)

    return right


def solve(heights):
    n = len(heights)

    left = nearest_greater_left(heights)
    right = nearest_greater_right(heights)

    intervals = []
    for i in range(n):
        start = left[i] + 1
        end = right[i] - 1
        width = end - start + 1
        weight = heights[i] * width
        intervals.append((end, start, weight))

    intervals.sort()

    ends = [item[0] for item in intervals]
    dp = [0] * (n + 1)

    for i in range(1, n + 1):
        end, start, weight = intervals[i - 1]
        count_non_overlap = bisect.bisect_left(ends, start)
        take_current = dp[count_non_overlap] + weight
        skip_current = dp[i - 1]
        dp[i] = max(skip_current, take_current)

    return dp[n]


def main():
    n = int(input().strip())
    heights = list(map(int, input().split()))
    answer = solve(heights)
    print(answer)


if __name__ == "__main__":
    main()

