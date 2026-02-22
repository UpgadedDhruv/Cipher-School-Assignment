# Problem: City Watchtowers 

Aurum is a coastal city planning to place watchtowers on top of selected skyline buildings.

Each building has a height. If you place a watchtower on building `i`, its visible monitoring range stretches from the nearest **strictly taller** building on the left to the nearest **strictly taller** building on the right (taller buildings block the view). So the effective covered interval for tower `i` is all buildings between those two blockers, inclusive of `i`.

To avoid radio interference, the city cannot choose two towers whose monitoring intervals overlap.

The usefulness of a tower on building `i` is:

- `height[i] × (number of buildings in its monitoring interval)`

Your task is to choose a set of non-overlapping towers so that total usefulness is maximum.

## Input

- First line: integer `n` — number of buildings.
- Second line: `n` integers `h1 h2 ... hn` — building heights.

## Output

- Print one integer: the maximum total usefulness.

## Constraints

- `1 ≤ n ≤ 2 * 10^5`
- `1 ≤ h[i] ≤ 10^9`

## Efficient idea (O(n log n))

1. Use monotonic stacks to compute for each building:
   - `L[i]`: index of nearest strictly greater building on the left, or `-1`.
   - `R[i]`: index of nearest strictly greater building on the right, or `n`.
2. Build one interval per building:
   - `start = L[i] + 1`
   - `end = R[i] - 1`
   - `weight = h[i] * (end - start + 1)`
3. Sort intervals by `end` and run weighted interval scheduling DP:
   - `dp[i] = best answer using first i intervals`
   - transition: skip current or take current + best compatible previous interval.

This is fast enough for the given limits.

## Test Cases

### Test Case 1
Input:
```
3
5 3 4
```
Output:
```
15
```

### Test Case 2
Input:
```
4
2 2 2 2
```
Output:
```
8
```

### Test Case 3
Input:
```
6
4 1 7 3 7 2
```
Output:
```
42
```
