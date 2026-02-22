'use strict';

const fs = require('fs');

function nearestGreaterLeft(heights) {
  const n = heights.length;
  const left = new Array(n).fill(-1);
  const stackIndex = [];

  for (let i = 0; i < n; i++) {
    while (stackIndex.length > 0 && heights[stackIndex[stackIndex.length - 1]] <= heights[i]) {
      stackIndex.pop();
    }

    if (stackIndex.length > 0) {
      left[i] = stackIndex[stackIndex.length - 1];
    }

    stackIndex.push(i);
  }

  return left;
}

function nearestGreaterRight(heights) {
  const n = heights.length;
  const right = new Array(n).fill(n);
  const stackIndex = [];

  for (let i = n - 1; i >= 0; i--) {
    while (stackIndex.length > 0 && heights[stackIndex[stackIndex.length - 1]] <= heights[i]) {
      stackIndex.pop();
    }

    if (stackIndex.length > 0) {
      right[i] = stackIndex[stackIndex.length - 1];
    }

    stackIndex.push(i);
  }

  return right;
}

function lowerBound(arr, target) {
  let left = 0;
  let right = arr.length;

  while (left < right) {
    const mid = Math.floor((left + right) / 2);
    if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return left;
}

function solve(heights) {
  const n = heights.length;

  const left = nearestGreaterLeft(heights);
  const right = nearestGreaterRight(heights);

  const intervals = [];
  for (let i = 0; i < n; i++) {
    const start = left[i] + 1;
    const end = right[i] - 1;
    const width = BigInt(end - start + 1);
    const weight = BigInt(heights[i]) * width;
    intervals.push({ start, end, weight });
  }

  intervals.sort((a, b) => {
    if (a.end !== b.end) return a.end - b.end;
    return a.start - b.start;
  });

  const ends = intervals.map(item => item.end);
  const dp = new Array(n + 1).fill(0n);

  for (let i = 1; i <= n; i++) {
    const start = intervals[i - 1].start;
    const weight = intervals[i - 1].weight;

    const countNonOverlap = lowerBound(ends, start);

    const takeCurrent = dp[countNonOverlap] + weight;
    const skipCurrent = dp[i - 1];
    dp[i] = takeCurrent > skipCurrent ? takeCurrent : skipCurrent;
  }

  return dp[n];
}

function main() {
  const input = fs.readFileSync(0, 'utf8').trim().split(/\s+/);
  let idx = 0;

  const n = Number(input[idx++]);
  const heights = new Array(n);
  for (let i = 0; i < n; i++) {
    heights[i] = Number(input[idx++]);
  }

  const answer = solve(heights);
  console.log(answer.toString());
}

main();
