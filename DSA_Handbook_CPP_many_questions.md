# The Complete DSA Handbook (C++) — Placement Preparation

> Every major pattern, from scratch, with intuition, C++ code, and time/space complexity.
> Read top to bottom once, then use as a lookup reference while solving problems.

---

## 1. Complexity Cheat Sheet

| Notation | Name | Example |
|---|---|---|
| O(1) | Constant | array index access |
| O(log n) | Logarithmic | binary search |
| O(n) | Linear | single loop |
| O(n log n) | Linearithmic | merge sort, sort() |
| O(n²) | Quadratic | nested loops |
| O(2ⁿ) | Exponential | subsets, brute recursion |
| O(n!) | Factorial | permutations |

**Rule of thumb for constraints (competitive/placement):**
- n ≤ 10 → O(n!) or O(2ⁿ · n) fine
- n ≤ 20 → O(2ⁿ)
- n ≤ 500 → O(n³)
- n ≤ 5,000 → O(n²)
- n ≤ 10⁶ → O(n log n)
- n ≤ 10⁸ → O(n) (tight)

**Space complexity** = extra memory used, *not counting input*, as a function of n (auxiliary arrays, recursion stack depth, hash maps, etc.)

---

## 2. Arrays & Two Pointers

### Pattern: Two Pointers (opposite ends)
**What it is:** Two variables ("pointers") start at opposite ends of an array and move toward each other, each step narrowing down the search — instead of checking every pair with nested loops.

**Intuition:** When array is sorted (or can be sorted) and you're looking for a pair/triplet satisfying a sum condition, moving two pointers from both ends avoids the O(n²) brute force.

**Use when:** "pair with target sum", "container with most water", "remove duplicates", "3Sum".

**Problem:** Given a sorted array and a target value, find the indices of two numbers that add up to the target.

*Example:* nums = [2,7,11,15], target = 9 → Output: [0,1]  (nums[0]+nums[1] = 2+7 = 9)

```cpp
// Two Sum on SORTED array — return indices (1-indexed) or values
#include <bits/stdc++.h>
using namespace std;

pair<int,int> twoSumSorted(vector<int>& a, int target) {
    int l = 0, r = a.size() - 1;
    while (l < r) {
        int sum = a[l] + a[r];
        if (sum == target) return {l, r};
        else if (sum < target) l++;   // need bigger sum
        else r--;                     // need smaller sum
    }
    return {-1, -1};
}
```
**Time:** O(n) — each pointer moves at most n times total. **Space:** O(1).

**🔗 Practice:** [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) · [3Sum](https://leetcode.com/problems/3sum/) · [Container With Most Water](https://leetcode.com/problems/container-with-most-water/) · [Two Sum](https://leetcode.com/problems/two-sum/) · [3Sum Closest](https://leetcode.com/problems/3sum-closest/) · [4Sum](https://leetcode.com/problems/4sum/) · [Valid Palindrome](https://leetcode.com/problems/valid-palindrome/) · [Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/) · [Boats to Save People](https://leetcode.com/problems/boats-to-save-people/) · [Sort Transformed Array](https://leetcode.com/problems/sort-transformed-array/) · [Two Sum Less Than K](https://leetcode.com/problems/two-sum-less-than-k/) · [Rotate Array](https://leetcode.com/problems/rotate-array/) · [Partition Labels](https://leetcode.com/problems/partition-labels/)

### Pattern: Fast & Slow Pointers (same direction — in-place compaction)
**What it is:** One pointer ("slow") marks where the next valid element should go, while another pointer ("fast") scans ahead looking for it — lets you rewrite an array in place without extra memory.

**Recognize it by:** "remove duplicates in-place", "move zeroes to the end", "in-place" + "O(1) extra space" on an array.

**Problem:** Given a sorted array, remove the duplicates in-place so each element appears only once, and return the new length.

*Example:* nums = [1,1,2,2,3] → Output: length = 3, array becomes [1,2,3,_,_]

```cpp
// Remove duplicates from sorted array in-place
int removeDuplicates(vector<int>& a) {
    if (a.empty()) return 0;
    int slow = 0;
    for (int fast = 1; fast < a.size(); fast++) {
        if (a[fast] != a[slow]) {
            slow++;
            a[slow] = a[fast];
        }
    }
    return slow + 1; // new length
}
```
**Time:** O(n). **Space:** O(1).

**🔗 Practice:** [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) · [Move Zeroes](https://leetcode.com/problems/move-zeroes/) · [Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/) · [Remove Element](https://leetcode.com/problems/remove-element/) · [Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) · [Duplicate Zeros](https://leetcode.com/problems/duplicate-zeros/) · [Sort Array By Parity](https://leetcode.com/problems/sort-array-by-parity/) · [Shortest Word Distance](https://leetcode.com/problems/shortest-word-distance/) · [Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/) · [Remove Linked List Elements](https://leetcode.com/problems/remove-linked-list-elements/) · [Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/)

### Pattern: Dutch National Flag (3-way partition)
**What it is:** A specialised 3-pointer technique (named after the Dutch flag's three colour bands) for sorting an array that only contains 3 distinct values, in a single left-to-right pass.

**Recognize it by:** the array contains only a small fixed set of distinct values (like 0/1/2) and you must sort it in one pass without extra space.

**Intuition:** Sort an array of 0s,1s,2s in one pass using low/mid/high pointers.

**Problem:** Given an array containing only the values 0, 1, and 2, sort it in-place in a single pass.

*Example:* nums = [2,0,2,1,1,0] → Output: [0,0,1,1,2,2]

```cpp
void sortColors(vector<int>& a) {
    int low = 0, mid = 0, high = a.size() - 1;
    while (mid <= high) {
        if (a[mid] == 0) swap(a[low++], a[mid++]);
        else if (a[mid] == 1) mid++;
        else swap(a[mid], a[high--]); // don't increment mid here
    }
}
```
**Time:** O(n). **Space:** O(1).

**🔗 Practice:** [Sort Colors](https://leetcode.com/problems/sort-colors/) · [Sort Array By Parity II](https://leetcode.com/problems/sort-array-by-parity-ii/) · [Wiggle Sort](https://leetcode.com/problems/wiggle-sort/) · [Sort Array By Increasing Frequency](https://leetcode.com/problems/sort-array-by-increasing-frequency/) · [Sort Array by Parity](https://leetcode.com/problems/sort-array-by-parity/) · [Partition Array Into Three Parts With Equal Sum](https://leetcode.com/problems/partition-array-into-three-parts-with-equal-sum/) · [Minimum Swaps to Group All 1's Together](https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together/)

---

## 3. Sliding Window

**Intuition:** For contiguous subarray/substring problems, instead of recomputing sum/state for every window (O(n²)), expand the right edge and shrink the left edge, maintaining a running state.

### 3a. Fixed-size window
**What it is:** A "window" of exactly k elements slides across the array one step at a time; instead of resumming all k elements every step, you just add the new element and drop the old one.

**Recognize it by:** "subarray of size k", "every k consecutive elements", "window of fixed length k".

**Problem:** Given an array and an integer k, find the maximum sum among all contiguous subarrays of size exactly k.

*Example:* a = [2,1,5,1,3,2], k = 3 → Output: 9  (subarray [5,1,3])

**Dry Run:**

```text
window [0..2] = [2, 1, 5] -> sum = 8, best = 8
slide: +a[3](1) -a[0](2) -> sum = 7, best = 8
slide: +a[4](3) -a[1](1) -> sum = 9, best = 9
slide: +a[5](2) -a[2](5) -> sum = 6, best = 9
Answer: 9
```

```cpp
// Max sum of subarray of size k
int maxSumFixedWindow(vector<int>& a, int k) {
    int sum = 0;
    for (int i = 0; i < k; i++) sum += a[i];
    int best = sum;
    for (int i = k; i < a.size(); i++) {
        sum += a[i] - a[i - k];   // slide window by 1
        best = max(best, sum);
    }
    return best;
}
```
**Time:** O(n). **Space:** O(1).

**🔗 Practice:** [Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/) · [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) · [Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/) · [Grumpy Bookstore Owner](https://leetcode.com/problems/grumpy-bookstore-owner/) · [Repeated DNA Sequences](https://leetcode.com/problems/repeated-dna-sequences/) · [Maximum Points You Can Obtain from Cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/) · [Sliding Window Median](https://leetcode.com/problems/sliding-window-median/) · [Minimum Difference Between Highest and Lowest of K Scores](https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/) · [Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold](https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/) · [Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/)

### 3b. Variable-size window (shrinkable)
**What it is:** The window's right edge keeps expanding to include more elements, and whenever some condition is satisfied, the left edge shrinks inward — the window's size adapts to the data instead of staying fixed.

**Recognize it by:** "smallest/shortest subarray such that...", "longest subarray with at most/at least...", a running sum or count that should stay within a limit.

**Problem:** Given an array of positive integers and a target sum, find the length of the shortest contiguous subarray whose sum is ≥ target.

*Example:* target = 7, a = [2,3,1,2,4,3] → Output: 2  (subarray [4,3])

**Dry Run:**

```text
right=0 a[0]=2 -> sum=2
right=1 a[1]=3 -> sum=5
right=2 a[2]=1 -> sum=6
right=3 a[3]=2 -> sum=8
  window[0..3] len=4 >= target -> best=4
  shrink: sum -= a[0](2) -> left=1
right=4 a[4]=4 -> sum=10
  window[1..4] len=4 >= target -> best=4
  shrink: sum -= a[1](3) -> left=2
  window[2..4] len=3 >= target -> best=3
  shrink: sum -= a[2](1) -> left=3
right=5 a[5]=3 -> sum=9
  window[3..5] len=3 >= target -> best=3
  shrink: sum -= a[3](2) -> left=4
  window[4..5] len=2 >= target -> best=2
  shrink: sum -= a[4](4) -> left=5
Answer: 2
```

```cpp
// Smallest subarray with sum >= target
int minSubArrayLen(int target, vector<int>& a) {
    int n = a.size(), left = 0, sum = 0, best = INT_MAX;
    for (int right = 0; right < n; right++) {
        sum += a[right];
        while (sum >= target) {           // shrink while condition holds
            best = min(best, right - left + 1);
            sum -= a[left++];
        }
    }
    return best == INT_MAX ? 0 : best;
}
```
**Time:** O(n) — left pointer moves forward at most n times total. **Space:** O(1).

**🔗 Practice:** [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) · [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) · [Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/) · [Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/) · [Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/) · [Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/) · [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) · [Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/) · [Longest Subarray of 1's After Deleting One Element](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/) · [Get Equal Substrings Within Budget](https://leetcode.com/problems/get-equal-substrings-within-budget/) · [Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones/)

### 3c. Window with hashmap (longest substring without repeating chars)
**What it is:** Same sliding-window idea, but a hashmap tracks extra information (like the last-seen position of each character) so the window can jump forward correctly instead of shrinking one step at a time.

**Recognize it by:** "longest substring with at most k distinct characters", "without repeating characters", "contains all characters of..." — window + character frequency.

**Problem:** Given a string, find the length of the longest substring that doesn't contain any repeated characters.

*Example:* "abcabcbb" → Output: 3  (the substring "abc")

**Dry Run:**

```text
  window='a' len=1 best=1
  window='ab' len=2 best=2
  window='abc' len=3 best=3
right=3 c='a' seen before at 0 (>= left) -> left jumps to 1
  window='bca' len=3 best=3
right=4 c='b' seen before at 1 (>= left) -> left jumps to 2
  window='cab' len=3 best=3
right=5 c='c' seen before at 2 (>= left) -> left jumps to 3
  window='abc' len=3 best=3
right=6 c='b' seen before at 4 (>= left) -> left jumps to 5
  window='cb' len=2 best=3
right=7 c='b' seen before at 6 (>= left) -> left jumps to 7
  window='b' len=1 best=3
Answer: 3
```

```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char,int> lastSeen;
    int best = 0, left = 0;
    for (int right = 0; right < s.size(); right++) {
        char c = s[right];
        if (lastSeen.count(c) && lastSeen[c] >= left)
            left = lastSeen[c] + 1;       // jump left past the duplicate
        lastSeen[c] = right;
        best = max(best, right - left + 1);
    }
    return best;
}
```
**Time:** O(n). **Space:** O(min(n, alphabet size)).

**🔗 Practice:** [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · [Permutation in String](https://leetcode.com/problems/permutation-in-string/) · [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) · [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) · [Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/) · [Longest Substring with At Least K Repeating Characters](https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/) · [Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/) · [Longest Nice Substring](https://leetcode.com/problems/longest-nice-substring/)

---

## 4. Prefix Sum & Kadane's

### Prefix Sum
**What it is:** Precompute a running total as you go through the array once, so that the sum of ANY range [l, r] can later be answered instantly with a subtraction, instead of re-adding elements every query.

**Recognize it by:** many repeated "sum of range [l, r]" queries on the same array, or "subarray sum equals K".

**Intuition:** Precompute cumulative sums so any range sum query is O(1).

**Problem:** Given an array, answer multiple queries that each ask for the sum of elements between index l and r (inclusive), as fast as possible per query.

*Example:* a = [1,2,3,4,5], query(1,3) → Output: 9  (2+3+4)

```cpp
vector<long long> buildPrefix(vector<int>& a) {
    vector<long long> pre(a.size() + 1, 0);
    for (int i = 0; i < a.size(); i++) pre[i+1] = pre[i] + a[i];
    return pre;
}
// sum of range [l, r] inclusive = pre[r+1] - pre[l]
```
**Time:** O(n) build, O(1) query. **Space:** O(n).

**🔗 Practice:** [Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) · [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) · [Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/) · [Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/) · [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) · [Contiguous Array](https://leetcode.com/problems/contiguous-array/) · [Find Pivot Index](https://leetcode.com/problems/find-pivot-index/) · [Subarray Sums Divisible by K](https://leetcode.com/problems/subarray-sums-divisible-by-k/) · [Maximum Size Subarray Sum Equals k](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/) · [Running Sum of 1d Array](https://leetcode.com/problems/running-sum-of-1d-array/) · [Path Sum III](https://leetcode.com/problems/path-sum-iii/) · [Minimum Value to Get Positive Step by Step Sum](https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/)

**Variant — subarray sum equals K (using hashmap of prefix sums):**
```cpp
int subarraySum(vector<int>& a, int k) {
    unordered_map<long long,int> freq;
    freq[0] = 1;
    long long sum = 0;
    int count = 0;
    for (int x : a) {
        sum += x;
        if (freq.count(sum - k)) count += freq[sum - k];
        freq[sum]++;
    }
    return count;
}
```
**Time:** O(n). **Space:** O(n).

### Kadane's Algorithm (Maximum Subarray Sum)
**What it is:** A single left-to-right pass where, at each element, you decide: "is it better to keep extending my current run, or abandon it and start fresh from here?" — this greedy local decision gives the global best answer.

**Recognize it by:** "maximum sum subarray", "maximum product subarray", "best contiguous run" in a single array.

**Intuition:** At each index, either extend the previous subarray or start fresh — whichever gives a bigger sum.

**Problem:** Given an integer array (which may contain negative numbers), find the contiguous subarray with the largest sum.

*Example:* a = [-2,1,-3,4,-1,2,1,-5,4] → Output: 6  (subarray [4,-1,2,1])

```cpp
int maxSubArray(vector<int>& a) {
    int best = a[0], cur = a[0];
    for (int i = 1; i < a.size(); i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}
```
**Time:** O(n). **Space:** O(1).

**🔗 Practice:** [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) · [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) · [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) · [Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/) · [Maximum Subarray Sum After One Operation](https://leetcode.com/problems/maximum-subarray-sum-after-one-operation/) · [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) · [Max Subarray Sum with One Deletion](https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/) · [Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/) · [Maximum Alternating Subsequence Sum](https://leetcode.com/problems/maximum-alternating-subsequence-sum/)

---

## 5. Sorting Algorithms

| Algorithm | Time (avg) | Time (worst) | Space | Stable? |
|---|---|---|---|---|
| Bubble/Insertion/Selection | O(n²) | O(n²) | O(1) | Bubble/Insertion: yes |
| Merge Sort | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(1) | No |
| Counting Sort | O(n+k) | O(n+k) | O(k) | Yes |

### Merge Sort
**What it is:** A "divide and conquer" sort: keep splitting the array in half until pieces have 1 element (already sorted), then merge pairs of sorted pieces back together, always keeping the result sorted.

**Recognize it by:** you need a *stable* O(n log n) sort, or the merge step itself is reused to solve another problem (like counting inversions).

**Intuition:** Divide array into halves, sort each half, merge two sorted halves in linear time.

**Problem:** Sort an array of integers into ascending order.

*Example:* a = [5,2,4,1,3] → Output: [1,2,3,4,5]

```cpp
void merge(vector<int>& a, int l, int m, int r) {
    vector<int> left(a.begin()+l, a.begin()+m+1);
    vector<int> right(a.begin()+m+1, a.begin()+r+1);
    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size())
        a[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < left.size()) a[k++] = left[i++];
    while (j < right.size()) a[k++] = right[j++];
}
void mergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m+1, r);
    merge(a, l, m, r);
}
```
**Time:** O(n log n) always. **Space:** O(n) for merging.

**🔗 Practice:** [Sort an Array](https://leetcode.com/problems/sort-an-array/) · [Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) · [Sort List](https://leetcode.com/problems/sort-list/) · [Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) · [Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) · [Merge Intervals](https://leetcode.com/problems/merge-intervals/) · [Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/) · [Maximum Gap](https://leetcode.com/problems/maximum-gap/)

### Quick Sort (Lomuto partition)
**What it is:** Pick one element (the "pivot"), rearrange the array so everything smaller ends up on its left and everything bigger on its right, then repeat the same process independently on each side.

**Recognize it by:** you need in-place O(n log n) average sort, or the partition step is reused (e.g. Kth largest via quickselect).

**Intuition:** Pick a pivot, partition array so smaller elements go left, larger go right, recurse on both sides.

**Problem:** Sort an array of integers into ascending order, in-place, using a pivot-partitioning strategy.

*Example:* a = [5,2,4,1,3] → Output: [1,2,3,4,5]

```cpp
int partition(vector<int>& a, int low, int high) {
    int pivot = a[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (a[j] < pivot) swap(a[++i], a[j]);
    swap(a[i+1], a[high]);
    return i + 1;
}
void quickSort(vector<int>& a, int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}
```
**Time:** O(n log n) average, O(n²) worst (already sorted + bad pivot). **Space:** O(log n) recursion stack.

**🔗 Practice:** [Sort an Array](https://leetcode.com/problems/sort-an-array/) · [Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) · [Sort Colors](https://leetcode.com/problems/sort-colors/) · [Wiggle Sort II](https://leetcode.com/problems/wiggle-sort-ii/) · [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) · [Sort List](https://leetcode.com/problems/sort-list/) · [Relative Sort Array](https://leetcode.com/problems/relative-sort-array/)

### Counting Sort (when range of values is small)
**What it is:** Instead of comparing elements to each other, just count how many times each value appears (works only when values are small integers in a known range), then rebuild the array from those counts.

**Recognize it by:** values are small non-negative integers within a known, limited range (e.g. ages, marks out of 100).

**Problem:** Sort an array of non-negative integers whose maximum value is small and known in advance.

*Example:* a = [4,2,2,8,3,3,1], maxVal = 8 → Output: [1,2,2,3,3,4,8]

```cpp
void countingSort(vector<int>& a, int maxVal) {
    vector<int> count(maxVal + 1, 0);
    for (int x : a) count[x]++;
    int idx = 0;
    for (int v = 0; v <= maxVal; v++)
        while (count[v]-- > 0) a[idx++] = v;
}
```
**Time:** O(n + k). **Space:** O(k).

**🔗 Practice:** [Sort an Array](https://leetcode.com/problems/sort-an-array/) · [Sort Colors](https://leetcode.com/problems/sort-colors/) · [Relative Sort Array](https://leetcode.com/problems/relative-sort-array/) · [Height Checker](https://leetcode.com/problems/height-checker/) · [Sort the People](https://leetcode.com/problems/sort-the-people/) · [Maximum Gap](https://leetcode.com/problems/maximum-gap/) · [Sort Array by Increasing Frequency](https://leetcode.com/problems/sort-array-by-increasing-frequency/)

> In interviews, `sort(a.begin(), a.end())` (introsort, O(n log n)) is usually fine — know the theory, use STL in practice.

---

## 6. Binary Search Patterns

**Intuition:** Works whenever the search space is *monotonic* — i.e., there's a point where a condition flips from false→true (or true→false). Not just for sorted arrays; also for "search on the answer".

### 6a. Standard binary search
**What it is:** Repeatedly look at the middle element of a sorted array and eliminate the half that can't contain the target — cuts the search space in half every step instead of scanning one by one.

**Recognize it by:** the array (or search space) is already sorted and you need to find one exact value quickly.

**Problem:** Given a sorted array and a target value, return the index of the target, or -1 if it isn't present.

*Example:* a = [-1,0,3,5,9,12], target = 9 → Output: 4

```cpp
int binarySearch(vector<int>& a, int target) {
    int lo = 0, hi = a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        else if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
```
**Time:** O(log n). **Space:** O(1).

**🔗 Practice:** [Binary Search](https://leetcode.com/problems/binary-search/) · [Sqrt(x)](https://leetcode.com/problems/sqrtx/) · [Search Insert Position](https://leetcode.com/problems/search-insert-position/) · [Guess Number Higher or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/) · [Valid Perfect Square](https://leetcode.com/problems/valid-perfect-square/) · [Peak Index in a Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/) · [Arranging Coins](https://leetcode.com/problems/arranging-coins/) · [First Bad Version](https://leetcode.com/problems/first-bad-version/) · [Find Peak Element](https://leetcode.com/problems/find-peak-element/)

### 6b. First / Last occurrence (lower_bound / upper_bound style)
**What it is:** A tweak on standard binary search: even after finding a match, keep searching further left (or right) to find the very first (or last) position where the target occurs, since duplicates may exist.

**Recognize it by:** sorted array WITH duplicates, and you need the first or last position of a value, or a count of occurrences.

**Problem:** Given a sorted array that may contain duplicates, find the first (or last) index at which a target value occurs.

*Example:* a = [5,7,7,8,8,10], target = 8 → Output: first index = 3

```cpp
int firstOccurrence(vector<int>& a, int target) {
    int lo = 0, hi = a.size() - 1, ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) { ans = mid; hi = mid - 1; } // keep searching left
        else if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return ans;
}
```
**Time:** O(log n). **Space:** O(1).

**🔗 Practice:** [Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) · [Find Smallest Letter Greater Than Target](https://leetcode.com/problems/find-smallest-letter-greater-than-target/) · [H-Index II](https://leetcode.com/problems/h-index-ii/) · [Count Negative Numbers in a Sorted Matrix](https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/) · [Find Right Interval](https://leetcode.com/problems/find-right-interval/) · [Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/) · [Search Insert Position](https://leetcode.com/problems/search-insert-position/)

### 6c. Search in rotated sorted array
**What it is:** The array was sorted but then "rotated" (its front chunk moved to the back). At every step, one half of the current range is still normally sorted — figure out which half that is, then decide which side to continue searching in.

**Recognize it by:** the phrase "rotated sorted array" or "sorted array that has been shifted", with no duplicates mentioned.

**Intuition:** One half of the array (around mid) is always properly sorted — check which half, then decide which side to recurse into.

**Problem:** A sorted array has been rotated at some unknown pivot (e.g. [0,1,2,4,5,6,7] → [4,5,6,7,0,1,2]). Given the rotated array and a target, find its index.

*Example:* a = [4,5,6,7,0,1,2], target = 0 → Output: 4

**Dry Run:**

```text
lo=0 hi=6 mid=3 a[mid]=7  | left half [0..3] is sorted & target NOT in it -> lo=4
lo=4 hi=6 mid=5 a[mid]=1  | left half [4..5] is sorted & target in it -> hi=4
lo=4 hi=4 mid=4 a[mid]=0  -> found at 4
```

```cpp
int searchRotated(vector<int>& a, int target) {
    int lo = 0, hi = a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[lo] <= a[mid]) {                 // left half sorted
            if (a[lo] <= target && target < a[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {                               // right half sorted
            if (a[mid] < target && target <= a[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}
```
**Time:** O(log n). **Space:** O(1).

**🔗 Practice:** [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) · [Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) · [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) · [Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/) · [Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/) · [Single Element in a Sorted Array](https://leetcode.com/problems/single-element-in-a-sorted-array/) · [Count Negative Numbers in a Sorted Matrix](https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/)

### 6d. Binary Search on the Answer
**What it is:** Instead of searching through the array, binary search over the space of POSSIBLE ANSWERS (e.g. "could the answer be 5? could it be 10?") whenever "is this answer good enough?" gets easier to check as the guessed value increases.

**Intuition:** When the answer itself is a number in a range, and "can we achieve X?" is monotonic (feasible answers form a prefix/suffix), binary search over the answer value.

**Problem:** You're given bloomDay[i] (the day flower i blooms), and need m bouquets, each requiring k *adjacent* already-bloomed flowers. Find the minimum day on which you can make all m bouquets (or -1 if impossible).

*Example:* bloomDay = [1,10,3,10,2], m = 3, k = 1 → Output: 3

**Dry Run:**

```text
lo=1 hi=10 try day=5 -> canMake=True  -> shrink hi=5
lo=1 hi=5 try day=3 -> canMake=True  -> shrink hi=3
lo=1 hi=3 try day=2 -> canMake=False  -> raise lo=3
Answer: 3
```

```cpp
// Example: minimum days to make m bouquets of k adjacent flowers
bool canMake(vector<int>& bloom, int day, int m, int k) {
    int count = 0, bouquets = 0;
    for (int b : bloom) {
        if (b <= day) count++;
        else count = 0;
        if (count == k) { bouquets++; count = 0; }
    }
    return bouquets >= m;
}
int minDays(vector<int>& bloom, int m, int k) {
    if ((long long)m * k > bloom.size()) return -1;
    int lo = *min_element(bloom.begin(), bloom.end());
    int hi = *max_element(bloom.begin(), bloom.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canMake(bloom, mid, m, k)) hi = mid;   // try smaller
        else lo = mid + 1;
    }
    return lo;
}
```
**Time:** O(n log(max-min)). **Space:** O(1).

**🔗 Practice:** [Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) · [Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) · [Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) · [Find the Smallest Divisor Given a Threshold](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/) · [Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/) · [Magnetic Force Between Two Balls](https://leetcode.com/problems/magnetic-force-between-two-balls/) · [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) · [Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/) · [Divide Chocolate](https://leetcode.com/problems/divide-chocolate/)
**Recognize this pattern from:** "minimize the maximum", "maximize the minimum", "Koko eating bananas", "ship packages within D days", "split array largest sum".

---

## 7. Recursion & Backtracking

**Intuition:** Backtracking = try a choice → recurse → undo the choice (backtrack) if it doesn't lead to a solution. Think of it as DFS over a decision tree, pruning invalid branches early.

**Template:**
```cpp
void backtrack(/* state */) {
    if (/* base case: found a solution */) {
        // record it
        return;
    }
    for (/* each choice */) {
        if (/* choice invalid */) continue;   // pruning
        // make choice
        backtrack(/* updated state */);
        // undo choice
    }
}
```

### Subsets (power set)
**What it is:** For every element, branch into two choices — include it, or don't — building every possible combination. Backtracking explores one full choice-path at a time, then undoes the last choice to try the next option.

**Recognize it by:** "return all subsets", "all possible combinations", "power set" — order doesn't matter, size varies.

**Problem:** Given an array of distinct integers, return every possible subset (the power set).

*Example:* nums = [1,2,3] → Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

**Dry Run:**

```text
record subset []
choose 1 -> cur=[1]
  record subset [1]
  choose 2 -> cur=[1, 2]
    record subset [1, 2]
    choose 3 -> cur=[1, 2, 3]
      record subset [1, 2, 3]
    backtrack: remove 3 -> cur=[1, 2]
  backtrack: remove 2 -> cur=[1]
  choose 3 -> cur=[1, 3]
    record subset [1, 3]
  backtrack: remove 3 -> cur=[1]
backtrack: remove 1 -> cur=[]
choose 2 -> cur=[2]
  record subset [2]
  choose 3 -> cur=[2, 3]
    record subset [2, 3]
  backtrack: remove 3 -> cur=[2]
backtrack: remove 2 -> cur=[]
choose 3 -> cur=[3]
  record subset [3]
backtrack: remove 3 -> cur=[]
Total subsets found: 8
```

```cpp
void subsetsHelper(vector<int>& nums, int idx, vector<int>& cur, vector<vector<int>>& res) {
    res.push_back(cur);
    for (int i = idx; i < nums.size(); i++) {
        cur.push_back(nums[i]);
        subsetsHelper(nums, i + 1, cur, res);
        cur.pop_back();               // backtrack
    }
}
```
**Time:** O(2ⁿ · n) (2ⁿ subsets, O(n) to copy each). **Space:** O(n) recursion depth (+ O(2ⁿ·n) output).

**🔗 Practice:** [Subsets](https://leetcode.com/problems/subsets/) · [Subsets II](https://leetcode.com/problems/subsets-ii/) · [Combination Sum](https://leetcode.com/problems/combination-sum/) · [Combination Sum II](https://leetcode.com/problems/combination-sum-ii/) · [Letter Case Permutation](https://leetcode.com/problems/letter-case-permutation/) · [Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/) · [Beautiful Arrangement](https://leetcode.com/problems/beautiful-arrangement/) · [Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square/) · [Gray Code](https://leetcode.com/problems/gray-code/) · [Increasing Subsequences](https://leetcode.com/problems/non-decreasing-subsequences/) · [Split a String Into the Max Number of Unique Substrings](https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/)

### Permutations
**What it is:** Try placing each unused element next in the sequence, recurse to fill the remaining positions, then undo ("backtrack") and try a different element in that position — this generates every possible ordering.

**Recognize it by:** "return all orderings/arrangements", every element must be used exactly once and order matters.

**Problem:** Given an array of distinct integers, return every possible ordering (permutation) of them.

*Example:* nums = [1,2,3] → Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

**Dry Run:**

```text
choose 1 -> cur=[1]
  choose 2 -> cur=[1, 2]
    choose 3 -> cur=[1, 2, 3]
      complete permutation: [1, 2, 3]
  choose 3 -> cur=[1, 3]
    choose 2 -> cur=[1, 3, 2]
      complete permutation: [1, 3, 2]
choose 2 -> cur=[2]
  choose 1 -> cur=[2, 1]
    choose 3 -> cur=[2, 1, 3]
      complete permutation: [2, 1, 3]
  choose 3 -> cur=[2, 3]
    choose 1 -> cur=[2, 3, 1]
      complete permutation: [2, 3, 1]
choose 3 -> cur=[3]
  choose 1 -> cur=[3, 1]
    choose 2 -> cur=[3, 1, 2]
      complete permutation: [3, 1, 2]
  choose 2 -> cur=[3, 2]
    choose 1 -> cur=[3, 2, 1]
      complete permutation: [3, 2, 1]
Total permutations found: 6
```

```cpp
void permuteHelper(vector<int>& nums, vector<bool>& used, vector<int>& cur, vector<vector<int>>& res) {
    if (cur.size() == nums.size()) { res.push_back(cur); return; }
    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue;
        used[i] = true;
        cur.push_back(nums[i]);
        permuteHelper(nums, used, cur, res);
        cur.pop_back();
        used[i] = false;              // backtrack
    }
}
```
**Time:** O(n! · n). **Space:** O(n).

**🔗 Practice:** [Permutations](https://leetcode.com/problems/permutations/) · [Permutations II](https://leetcode.com/problems/permutations-ii/) · [Next Permutation](https://leetcode.com/problems/next-permutation/) · [Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) · [Permutation Sequence](https://leetcode.com/problems/permutation-sequence/) · [Palindrome Permutation II](https://leetcode.com/problems/palindrome-permutation-ii/) · [Beautiful Arrangement II](https://leetcode.com/problems/beautiful-arrangement-ii/) · [Unique Paths III](https://leetcode.com/problems/unique-paths-iii/)

### N-Queens
**What it is:** Place one queen per row; before placing, check if it's under attack from queens already placed. If a placement leads to a dead end later, backtrack and try the next column in that row.

**Recognize it by:** placing items on a grid under "no two can conflict" constraints (rows/columns/diagonals), needing every valid full arrangement.

**Problem:** Place n queens on an n×n chessboard so that no two queens attack each other (same row, column, or diagonal); return all distinct arrangements.

*Example:* n = 4 → Output: 2 valid board arrangements

**Dry Run:**

```text
row 0: try col 0 (not attacked) -> place, board=[0, -1, -1, -1]
row 1: col 0 is attacked by an earlier queen -> skip
row 1: col 1 is attacked by an earlier queen -> skip
row 1: try col 2 (not attacked) -> place, board=[0, 2, -1, -1]
row 1: try col 3 (not attacked) -> place, board=[0, 3, -1, -1]
row 2: try col 1 (not attacked) -> place, board=[0, 3, 1, -1]
row 0: try col 1 (not attacked) -> place, board=[1, -1, -1, -1]
row 1: col 0 is attacked by an earlier queen -> skip
row 1: col 1 is attacked by an earlier queen -> skip
row 1: col 2 is attacked by an earlier queen -> skip
row 1: try col 3 (not attacked) -> place, board=[1, 3, -1, -1]
row 2: try col 0 (not attacked) -> place, board=[1, 3, 0, -1]
row 3: try col 2 (not attacked) -> place, board=[1, 3, 0, 2]
row 4: all queens placed -> first solution = [1, 3, 0, 2]
... continues exploring remaining branches ...
Answer: 2 total solutions for n=4
```

```cpp
bool isSafe(vector<string>& board, int row, int col, int n) {
    for (int i = 0; i < row; i++) if (board[i][col] == 'Q') return false;
    for (int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--) if (board[i][j]=='Q') return false;
    for (int i = row-1, j = col+1; i >= 0 && j < n; i--, j++) if (board[i][j]=='Q') return false;
    return true;
}
void solveNQueens(vector<string>& board, int row, int n, vector<vector<string>>& res) {
    if (row == n) { res.push_back(board); return; }
    for (int col = 0; col < n; col++) {
        if (!isSafe(board, row, col, n)) continue;
        board[row][col] = 'Q';
        solveNQueens(board, row + 1, n, res);
        board[row][col] = '.';        // backtrack
    }
}
```
**Time:** O(n!) roughly (with pruning much faster in practice). **Space:** O(n²) for board + O(n) recursion.

**🔗 Practice:** [N-Queens](https://leetcode.com/problems/n-queens/) · [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) · [Combination Sum](https://leetcode.com/problems/combination-sum/) · [Word Search](https://leetcode.com/problems/word-search/) · [Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/) · [N-Queens II](https://leetcode.com/problems/n-queens-ii/) · [Combination Sum III](https://leetcode.com/problems/combination-sum-iii/) · [Restore IP Addresses](https://leetcode.com/problems/restore-ip-addresses/) · [Word Break II](https://leetcode.com/problems/word-break-ii/) · [Expression Add Operators](https://leetcode.com/problems/expression-add-operators/)

**Backtracking recognizes:** subsets, combinations, permutations, N-Queens, Sudoku solver, word search on grid, palindrome partitioning, combination sum.

---

## 8. Linked List Patterns

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

### Reverse a linked list (iterative)
**What it is:** Walk through the list one node at a time, and instead of pointing each node to the NEXT node, make it point to the PREVIOUS one — by the end, the whole list points backward.

**Recognize it by:** "reverse a linked list" (whole list or a sub-range of it) — a classic pointer-rewiring task.

**Intuition:** Walk the list, re-point each `next` backward, carry three pointers: prev, curr, next.

**Problem:** Given the head of a singly linked list, reverse it and return the new head.

*Example:* 1→2→3→4→5 → Output: 5→4→3→2→1

```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    return prev; // new head
}
```
**Time:** O(n). **Space:** O(1).

**🔗 Practice:** [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) · [Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/) · [Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/) · [Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/) · [Rotate List](https://leetcode.com/problems/rotate-list/) · [Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/) · [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/) · [Add Two Numbers II](https://leetcode.com/problems/add-two-numbers-ii/)

### Floyd's Cycle Detection (slow/fast pointers)
**What it is:** Send two pointers down the list at different speeds (one step vs two steps at a time). If there's a loop, the faster one will eventually "lap" the slower one and they'll meet — like two runners on a circular track.

**Recognize it by:** "does this linked list have a cycle", "find the start of the cycle", or any problem framed as "detect a loop".

**Intuition:** Fast pointer moves 2 steps, slow moves 1. If there's a cycle, they must eventually meet (fast "laps" slow).

**Problem:** Given the head of a linked list, determine whether it contains a cycle (some node's `next` eventually points back to an earlier node).

*Example:* 3→2→0→-4→(points back to the node valued 2) → Output: true

```cpp
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```
**Finding cycle start:** after slow==fast meet, reset one pointer to head; move both one step at a time — they meet at cycle start.
```cpp
ListNode* detectCycleStart(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) {
            ListNode* ptr = head;
            while (ptr != slow) { ptr = ptr->next; slow = slow->next; }
            return ptr;
        }
    }
    return nullptr;
}
```
**Time:** O(n). **Space:** O(1).

**🔗 Practice:** [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/) · [Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/) · [Happy Number](https://leetcode.com/problems/happy-number/) · [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) · [Circular Array Loop](https://leetcode.com/problems/circular-array-loop/) · [Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/) · [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/)

### Merge two sorted lists
**What it is:** Walk both lists side by side with two pointers, always picking whichever current node is smaller to attach next to the result — since both inputs are already sorted, the merged result comes out sorted too.

**Recognize it by:** combining two (or more) already-sorted linked lists or arrays into one sorted result.

**Problem:** Given the heads of two sorted linked lists, merge them into one sorted linked list.

*Example:* list1 = 1→2→4, list2 = 1→3→4 → Output: 1→1→2→3→4→4

```cpp
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (a && b) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}
```
**Time:** O(n+m). **Space:** O(1) (excluding output).

**🔗 Practice:** [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) · [Sort List](https://leetcode.com/problems/sort-list/) · [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) · [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/) · [Merge Two Binary Trees](https://leetcode.com/problems/merge-two-binary-trees/) · [Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) · [Merge In Between Linked Lists](https://leetcode.com/problems/merge-in-between-linked-lists/)

### Find middle of linked list (slow/fast)
**What it is:** Move one pointer one step at a time and another pointer two steps at a time; when the fast one reaches the end, the slow one is sitting exactly at the middle.

**Recognize it by:** you need the middle node of a linked list without knowing its length in advance (common inside merge-sort-on-list or palindrome-list problems).

**Problem:** Given the head of a linked list, return its middle node (if there are two middle nodes, return the second one).

*Example:* 1→2→3→4→5 → Output: node with value 3

```cpp
ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    return slow;
}
```
**Time:** O(n). **Space:** O(1).

**🔗 Practice:** [Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/) · [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/) · [Reorder List](https://leetcode.com/problems/reorder-list/) · [Sort List](https://leetcode.com/problems/sort-list/) · [Delete the Middle Node of a Linked List](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/) · [Convert Sorted List to Binary Search Tree](https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/) · [Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)
Used inside merge sort on linked lists, and palindrome-linked-list checks.

### LRU Cache (linked list + hashmap)
**What it is:** Combine a doubly linked list (which remembers the ORDER items were used, most-recent at the front) with a hashmap (which gives instant lookup by key) to build a cache that can evict the least-recently-used item in O(1) time.

**Recognize it by:** "design a cache", "evict least recently used", any problem asking for O(1) get/put with an eviction policy.

**Intuition:** Doubly linked list keeps usage order (most-recent at head); hashmap gives O(1) node lookup by key.

**Problem:** Design a fixed-capacity cache supporting get(key) and put(key, value) in O(1) time each, that evicts the Least Recently Used item whenever it's full.

*Example:* capacity=2; put(1,1); put(2,2); get(1)→1; put(3,3) evicts key 2; get(2)→-1

```cpp
class LRUCache {
    int cap;
    list<pair<int,int>> dll; // {key, value}, front = most recently used
    unordered_map<int, list<pair<int,int>>::iterator> mp;
public:
    LRUCache(int capacity) : cap(capacity) {}
    int get(int key) {
        if (!mp.count(key)) return -1;
        auto it = mp[key];
        dll.splice(dll.begin(), dll, it);  // move to front
        return it->second;
    }
    void put(int key, int value) {
        if (mp.count(key)) {
            dll.erase(mp[key]);
        } else if (dll.size() == cap) {
            mp.erase(dll.back().first);
            dll.pop_back();
        }
        dll.push_front({key, value});
        mp[key] = dll.begin();
    }
};
```
**Time:** O(1) get/put. **Space:** O(capacity).

**🔗 Practice:** [LRU Cache](https://leetcode.com/problems/lru-cache/) · [LFU Cache](https://leetcode.com/problems/lfu-cache/) · [Design Circular Queue](https://leetcode.com/problems/design-circular-queue/) · [Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/) · [Design Twitter](https://leetcode.com/problems/design-twitter/) · [All O`one Data Structure](https://leetcode.com/problems/all-oone-data-structure/) · [Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)

---

## 9. Stack Patterns

### Valid Parentheses
**What it is:** Use a stack as a "pile" of open brackets waiting to be closed: every opening bracket gets pushed on, and every closing bracket must match (and pop) whatever is currently on top — otherwise the brackets don't line up correctly.

**Recognize it by:** matching/nesting of paired symbols — brackets, tags, or any "open X must be closed by a matching Y" rule.

**Problem:** Given a string containing just the characters '(', ')', '{', '}', '[', ']', determine whether every bracket is properly closed and nested.

*Example:* "()[]{}" → Output: true.   "(]" → Output: false

```cpp
bool isValid(string s) {
    stack<char> st;
    unordered_map<char,char> match = {{')','('},{']','['},{'}','{'}};
    for (char c : s) {
        if (c=='('||c=='['||c=='{') st.push(c);
        else {
            if (st.empty() || st.top() != match[c]) return false;
            st.pop();
        }
    }
    return st.empty();
}
```
**Time:** O(n). **Space:** O(n).

**🔗 Practice:** [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) · [Min Stack](https://leetcode.com/problems/min-stack/) · [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) · [Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/) · [Score of Parentheses](https://leetcode.com/problems/score-of-parentheses/) · [Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/) · [Check if a Parentheses String Can Be Valid](https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/) · [Different Ways to Add Parentheses](https://leetcode.com/problems/different-ways-to-add-parentheses/) · [Basic Calculator](https://leetcode.com/problems/basic-calculator/) · [Maximum Nesting Depth of the Parentheses](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/)

### Monotonic Stack — Next Greater Element
**What it is:** Keep a stack of elements that are waiting to find something bigger than them. As soon as a bigger element shows up, it "resolves" every smaller element still sitting on the stack, all in one linear pass.

**Recognize it by:** "next greater/smaller element", "daily temperatures", "stock span" — anything needing, for each element, the nearest bigger/smaller one on one side.

**Intuition:** Keep a stack of indices whose "next greater" hasn't been found yet. When a bigger element comes, it's the answer for everything smaller left on the stack.

**Problem:** For every element in an array, find the first element to its right that is strictly greater; -1 if none exists.

*Example:* a = [2,1,2,4,3] → Output: [4,2,4,-1,-1]

**Dry Run:**

```text
i=0 a[i]=2  stack(idx)=[]
  push 0 -> stack=[0]
i=1 a[i]=1  stack(idx)=[0]
  push 1 -> stack=[0, 1]
i=2 a[i]=2  stack(idx)=[0, 1]
  a[1]=1 < 2 -> res[1]=2, pop 1
  push 2 -> stack=[0, 2]
i=3 a[i]=4  stack(idx)=[0, 2]
  a[2]=2 < 4 -> res[2]=4, pop 2
  a[0]=2 < 4 -> res[0]=4, pop 0
  push 3 -> stack=[3]
i=4 a[i]=3  stack(idx)=[3]
  push 4 -> stack=[3, 4]
Answer: [4, 2, 4, -1, -1]
```

```cpp
vector<int> nextGreaterElement(vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st;                     // stores indices, values decreasing bottom→top
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            res[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}
```
**Time:** O(n) — each index pushed & popped at most once. **Space:** O(n).

**🔗 Practice:** [Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/) · [Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) · [Online Stock Span](https://leetcode.com/problems/online-stock-span/) · [Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/) · [Remove K Digits](https://leetcode.com/problems/remove-k-digits/) · [132 Pattern](https://leetcode.com/problems/132-pattern/) · [Final Prices With a Special Discount in a Shop](https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/) · [Sum of Subarray Ranges](https://leetcode.com/problems/sum-of-subarray-ranges/) · [Asteroid Collision](https://leetcode.com/problems/asteroid-collision/)

**Same pattern powers:** largest rectangle in histogram, daily temperatures, stock span, trapping rain water (stack variant).

### Largest Rectangle in Histogram (monotonic stack)
**What it is:** Keep a stack of bar heights in increasing order. When a shorter bar appears, it means the taller bars behind it can't extend any further right, so pop them off and calculate the biggest rectangle they could have formed.

**Recognize it by:** "largest rectangle", "maximal rectangle", or trapping-water style problems built on top of a next-greater-element idea.

**Problem:** Given the heights of histogram bars (each of width 1), find the area of the largest rectangle that can be formed within the histogram.

*Example:* heights = [2,1,5,6,2,3] → Output: 10

**Dry Run:**

```text
i=0 cur=2  stack(idx)=[]
i=1 cur=1  stack(idx)=[0]
  pop height=2 width=1 area=2 -> best=2
i=2 cur=5  stack(idx)=[1]
i=3 cur=6  stack(idx)=[1, 2]
i=4 cur=2  stack(idx)=[1, 2, 3]
  pop height=6 width=1 area=6 -> best=6
  pop height=5 width=2 area=10 -> best=10
i=5 cur=3  stack(idx)=[1, 4]
i=6 cur=0  stack(idx)=[1, 4, 5]
  pop height=3 width=1 area=3 -> best=10
  pop height=2 width=4 area=8 -> best=10
  pop height=1 width=6 area=6 -> best=10
Answer: 10
```

```cpp
int largestRectangleArea(vector<int>& h) {
    stack<int> st;                     // increasing heights
    int best = 0, n = h.size();
    for (int i = 0; i <= n; i++) {
        int cur = (i == n) ? 0 : h[i];
        while (!st.empty() && h[st.top()] >= cur) {
            int height = h[st.top()]; st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            best = max(best, height * width);
        }
        st.push(i);
    }
    return best;
}
```
**Time:** O(n). **Space:** O(n).

**🔗 Practice:** [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) · [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) · [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) · [Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/) · [Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/) · [Remove Duplicate Letters](https://leetcode.com/problems/remove-duplicate-letters/) · [132 Pattern](https://leetcode.com/problems/132-pattern/)

---

## 10. Queue & Deque Patterns

### Sliding Window Maximum (monotonic deque)
**What it is:** Keep a double-ended queue (deque) of candidates for "current window's maximum", always removing smaller elements from the back before adding a new one — so the front of the deque is always the answer for the current window.

**Recognize it by:** "maximum/minimum in every window of size k" — a sliding window where you need the extreme value, not a sum.

**Intuition:** Maintain a deque of indices with strictly decreasing values (front = current window max). Pop smaller values from the back before pushing; pop from front if out of window.

**Problem:** Given an array and a window size k, return the maximum value in every window of size k as it slides from left to right.

*Example:* a = [1,3,-1,-3,5,3,6,7], k = 3 → Output: [3,3,5,5,6,7]

**Dry Run:**

```text
i=0: deque(idx)=[0] -> window not full yet
i=1: a[0]=1 < 3 -> pop_back
i=1: deque(idx)=[1] -> window not full yet
i=2: deque(idx)=[1, 2] -> window max = 3
i=3: deque(idx)=[1, 2, 3] -> window max = 3
i=4: front idx 1 out of window -> pop_front
i=4: a[3]=-3 < 5 -> pop_back
i=4: a[2]=-1 < 5 -> pop_back
i=4: deque(idx)=[4] -> window max = 5
i=5: deque(idx)=[4, 5] -> window max = 5
i=6: a[5]=3 < 6 -> pop_back
i=6: a[4]=5 < 6 -> pop_back
i=6: deque(idx)=[6] -> window max = 6
i=7: a[6]=6 < 7 -> pop_back
i=7: deque(idx)=[7] -> window max = 7
Answer: [3, 3, 5, 5, 6, 7]
```

```cpp
vector<int> maxSlidingWindow(vector<int>& a, int k) {
    deque<int> dq;                     // stores indices
    vector<int> res;
    for (int i = 0; i < a.size(); i++) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front(); // out of window
        while (!dq.empty() && a[dq.back()] < a[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}
```
**Time:** O(n). **Space:** O(k).

**🔗 Practice:** [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) · [Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/) · [Constrained Subsequence Sum](https://leetcode.com/problems/constrained-subsequence-sum/) · [Jump Game VI](https://leetcode.com/problems/jump-game-vi/) · [Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/)

### BFS with a queue (generic template)
**What it is:** Explore a graph or grid "layer by layer": visit all neighbours of the start node first, then all of THEIR neighbours, and so on — using a queue guarantees you finish one full layer before starting the next, which is what gives BFS its shortest-path guarantee.

**Recognize it by:** "shortest path", "minimum number of steps", "level by level" in an unweighted graph or grid.

**Problem:** Given a 2D grid of '1' (land) and '0' (water), count the number of islands (groups of connected land cells).

*Example:* grid = [["1","1","0"],["0","1","0"],["0","0","1"]] → Output: 2

```cpp
void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        // process node
        for (int nxt : adj[node]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                q.push(nxt);
            }
        }
    }
}
```
**Time:** O(V+E). **Space:** O(V).

**🔗 Practice:** [Number of Islands](https://leetcode.com/problems/number-of-islands/) · [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) · [Walls and Gates](https://leetcode.com/problems/walls-and-gates/) · [01 Matrix](https://leetcode.com/problems/01-matrix/) · [Open the Lock](https://leetcode.com/problems/open-the-lock/) · [As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/) · [Nearest Exit from Entrance in Maze](https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/) · [Bus Routes](https://leetcode.com/problems/bus-routes/)

---

## 11. Trees

```cpp
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

### Traversals
**What it is:** The different orders in which you can visit every node of a tree: top-first (preorder), sorted order for a BST (inorder), children-before-parent (postorder), or level-by-level using a queue (level order / BFS).

**Recognize it by:** any question that starts with "given a binary tree, return/print/visit its nodes in ___ order".

**Problem:** Given the root of a binary tree, return its node values visited in a given order (preorder, inorder, postorder, or level order).

*Example:* tree = [1,null,2,3] → inorder Output: [1,3,2]

```cpp
void preorder(TreeNode* root, vector<int>& out) {  // Root-Left-Right
    if (!root) return;
    out.push_back(root->val);
    preorder(root->left, out);
    preorder(root->right, out);
}
void inorder(TreeNode* root, vector<int>& out) {   // Left-Root-Right (sorted for BST)
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}
void postorder(TreeNode* root, vector<int>& out) { // Left-Right-Root
    if (!root) return;
    postorder(root->left, out);
    postorder(root->right, out);
    out.push_back(root->val);
}
vector<vector<int>> levelOrder(TreeNode* root) {   // BFS level by level
    vector<vector<int>> res;
    if (!root) return res;
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        vector<int> level;
        for (int i = 0; i < sz; i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    return res;
}
```
**Time:** O(n) all traversals. **Space:** O(h) for DFS recursion (h = height), O(n) worst case for BFS queue.

**🔗 Practice:** [Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/) · [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) · [Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/) · [Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/) · [Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/) · [Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/) · [N-ary Tree Preorder Traversal](https://leetcode.com/problems/n-ary-tree-preorder-traversal/) · [Average of Levels in Binary Tree](https://leetcode.com/problems/average-of-levels-in-binary-tree/) · [Vertical Order Traversal of a Binary Tree](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/) · [Cousins in Binary Tree](https://leetcode.com/problems/cousins-in-binary-tree/)

### Height / Diameter of a tree
**What it is:** Compute a value "bottom-up": each node asks its children for their answers first (via recursion), combines them, and passes its own answer up to its parent — the classic recursive tree pattern.

**Recognize it by:** "height of a tree", "diameter" (longest path between two nodes), "is this tree balanced" — needs a value computed bottom-up from children.

**Intuition:** Diameter (longest path between any two nodes) at any node = left height + right height. Compute bottom-up.

**Problem:** Given the root of a binary tree, find the length (in edges) of the longest path between any two nodes.

*Example:* tree = [1,2,3,4,5] → Output: diameter = 3

```cpp
int diameter = 0;
int height(TreeNode* root) {
    if (!root) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    diameter = max(diameter, lh + rh);   // update global answer
    return 1 + max(lh, rh);
}
```
**Time:** O(n). **Space:** O(h).

**🔗 Practice:** [Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) · [Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/) · [Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/) · [Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/) · [Diameter of N-Ary Tree](https://leetcode.com/problems/diameter-of-n-ary-tree/) · [Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/) · [Longest Univalue Path](https://leetcode.com/problems/longest-univalue-path/)

### Lowest Common Ancestor (general binary tree)
**What it is:** Search both subtrees for the two target nodes. If they turn up in DIFFERENT subtrees of some node, that node is where their paths first meet — the lowest common ancestor.

**Recognize it by:** "find the lowest/nearest common ancestor of two nodes" in a tree.

**Intuition:** Recurse into both subtrees; if a node finds both p and q in different subtrees, it IS the LCA.

**Problem:** Given the root of a binary tree and two of its nodes p and q, find their lowest (deepest) common ancestor.

*Example:* tree with p = 5, q = 1 → Output: their LCA is the node valued 3

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;       // p and q found in different subtrees
    return left ? left : right;
}
```
**Time:** O(n). **Space:** O(h).

**🔗 Practice:** [Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) · [Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/) · [Lowest Common Ancestor of a Binary Tree III](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/) · [Smallest Common Region](https://leetcode.com/problems/smallest-common-region/) · [Maximum Difference Between Node and Ancestor](https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/) · [All Nodes Distance K in Binary Tree](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/)

### Serialize / Deserialize
**What it is:** "Serialize" turns a tree into a flat string (e.g. using preorder traversal, marking empty spots with a placeholder like '#') so it can be saved or sent somewhere; "deserialize" reads that string back and rebuilds the exact same tree structure.

**Recognize it by:** "design an algorithm to serialize/deserialize" a tree — converting a structure to a string and back losslessly.

**Problem:** Design an algorithm to convert a binary tree into a string (serialize), and reconstruct the exact same tree from that string (deserialize).

*Example:* tree = [1,2,3,null,null,4,5] → serialized: "1 2 # # 3 4 # # 5 # #"

```cpp
void serialize(TreeNode* root, string& out) {
    if (!root) { out += "# "; return; }
    out += to_string(root->val) + " ";
    serialize(root->left, out);
    serialize(root->right, out);
}
TreeNode* deserializeHelper(istringstream& in) {
    string val; in >> val;
    if (val == "#") return nullptr;
    TreeNode* root = new TreeNode(stoi(val));
    root->left = deserializeHelper(in);
    root->right = deserializeHelper(in);
    return root;
}
```
**Time:** O(n). **Space:** O(n).

**🔗 Practice:** [Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) · [Serialize and Deserialize BST](https://leetcode.com/problems/serialize-and-deserialize-bst/) · [Encode and Decode Strings](https://leetcode.com/problems/encode-and-decode-strings/) · [Find Duplicate Subtrees](https://leetcode.com/problems/find-duplicate-subtrees/) · [Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) · [Verify Preorder Serialization of a Binary Tree](https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/)

---

## 12. Binary Search Trees

### BST Insert / Search
**What it is:** Because a Binary Search Tree keeps smaller values to the left and bigger values to the right of every node, you can decide which direction to go at each step just by comparing — no need to check every node.

**Recognize it by:** operations on a Binary Search Tree where you must decide left/right using value comparisons instead of checking every node.

**Problem:** Given the root of a Binary Search Tree, insert a new value into it (or search for whether a value exists), keeping the BST property intact.

*Example:* insert 5 into BST rooted at 4 → 5 becomes the right child of 4

```cpp
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}
TreeNode* searchBST(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    return val < root->val ? searchBST(root->left, val) : searchBST(root->right, val);
}
```
**Time:** O(h) — O(log n) balanced, O(n) skewed worst case. **Space:** O(h).

**🔗 Practice:** [Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree/) · [Search in a Binary Search Tree](https://leetcode.com/problems/search-in-a-binary-search-tree/) · [Range Sum of BST](https://leetcode.com/problems/range-sum-of-bst/) · [Minimum Absolute Difference in BST](https://leetcode.com/problems/minimum-absolute-difference-in-bst/) · [Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/) · [Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/) · [Delete Leaves With a Given Value](https://leetcode.com/problems/delete-leaves-with-a-given-value/) · [Trim a Binary Search Tree](https://leetcode.com/problems/trim-a-binary-search-tree/)

### BST Delete
**What it is:** Removing a node is easy if it has 0 or 1 children (just reconnect around it), but if it has 2 children, you swap its value with the next-bigger value in the tree (its "inorder successor") and delete that instead.

**Recognize it by:** "delete a node from a BST" while keeping the BST property valid.

**Intuition:** 3 cases — leaf (just remove), one child (replace with child), two children (replace with inorder successor, i.e., min of right subtree, then delete that).

**Problem:** Given the root of a BST and a key, delete the node with that key from the tree while keeping it a valid BST.

*Example:* delete 3 from [5,3,6,2,4,null,7] → Output: [5,4,6,2,null,null,7]

```cpp
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->val) root->left = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        TreeNode* succ = root->right;
        while (succ->left) succ = succ->left;   // inorder successor
        root->val = succ->val;
        root->right = deleteNode(root->right, succ->val);
    }
    return root;
}
```
**Time:** O(h). **Space:** O(h).

**🔗 Practice:** [Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/) · [Trim a Binary Search Tree](https://leetcode.com/problems/trim-a-binary-search-tree/) · [Balance a Binary Search Tree](https://leetcode.com/problems/balance-a-binary-search-tree/) · [Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree/) · [Search in a Binary Search Tree](https://leetcode.com/problems/search-in-a-binary-search-tree/) · [Split BST](https://leetcode.com/problems/split-bst/)

### Validate BST
**What it is:** Check that every node's value actually falls within the valid (min, max) range allowed by its ancestors — just checking a node against its immediate parent isn't enough, since a value could break the rule set by a grandparent further up.

**Recognize it by:** "determine if a binary tree is a valid BST" — check ordering constraints across the WHOLE ancestor chain, not just parent-child.

**Problem:** Given the root of a binary tree, determine whether it is a valid Binary Search Tree.

*Example:* [5,1,4,null,null,3,6] → Output: false  (4's left child 3 is less than 5, breaking the BST rule two levels up)

```cpp
bool validate(TreeNode* root, long long lo, long long hi) {
    if (!root) return true;
    if (root->val <= lo || root->val >= hi) return false;
    return validate(root->left, lo, root->val) && validate(root->right, root->val, hi);
}
bool isValidBST(TreeNode* root) {
    return validate(root, LLONG_MIN, LLONG_MAX);
}
```
**Time:** O(n). **Space:** O(h).

**🔗 Practice:** [Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/) · [Recover Binary Search Tree](https://leetcode.com/problems/recover-binary-search-tree/) · [Convert BST to Greater Tree](https://leetcode.com/problems/convert-bst-to-greater-tree/) · [Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/) · [Find Mode in Binary Search Tree](https://leetcode.com/problems/find-mode-in-binary-search-tree/) · [Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)

### Kth Smallest in BST (inorder gives sorted order)
**What it is:** An inorder traversal of a BST always visits nodes in sorted order — so simply count nodes as you traverse inorder, and stop as soon as you reach the kth one.

**Recognize it by:** "kth smallest/largest element in a BST" — inorder traversal gives you sorted order for free.

**Problem:** Given the root of a BST and an integer k, return the k-th smallest value stored in it.

*Example:* [3,1,4,null,2], k = 1 → Output: 1

```cpp
int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (true) {
        while (cur) { st.push(cur); cur = cur->left; }
        cur = st.top(); st.pop();
        if (--k == 0) return cur->val;
        cur = cur->right;
    }
}
```
**Time:** O(h + k). **Space:** O(h).

**🔗 Practice:** [Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) · [Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/) · [Inorder Successor in BST](https://leetcode.com/problems/inorder-successor-in-bst/) · [Closest Binary Search Tree Value](https://leetcode.com/problems/closest-binary-search-tree-value/) · [Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) · [Contains Duplicate III](https://leetcode.com/problems/contains-duplicate-iii/)

---

## 13. Heaps / Priority Queue

**Intuition:** A heap gives O(log n) insert and O(1) access to min/max. Use whenever you repeatedly need "the current smallest/largest" — top-K problems, merging sorted lists, scheduling.

```cpp
priority_queue<int> maxHeap;                       // default: max at top
priority_queue<int, vector<int>, greater<int>> minHeap; // min at top
```

### Kth Largest Element
**What it is:** Keep a min-heap (a structure that gives instant access to the smallest element) of size k as you scan the array. Whenever the heap grows past k, kick out its smallest — whatever survives at the top is the kth largest.

**Recognize it by:** "kth largest/smallest", "top k" elements from an unsorted collection.

**Intuition:** Keep a min-heap of size k. If heap grows beyond k, pop smallest — heap top ends up as the kth largest.

**Problem:** Given an unsorted array and an integer k, find the k-th largest element in the array.

*Example:* nums = [3,2,1,5,6,4], k = 2 → Output: 5

```cpp
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : nums) {
        minHeap.push(x);
        if (minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}
```
**Time:** O(n log k). **Space:** O(k).

**🔗 Practice:** [Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) · [Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) · [Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/) · [Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/) · [K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/) · [Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/) · [Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/) · [Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/) · [IPO](https://leetcode.com/problems/ipo/)

### Merge K Sorted Lists
**What it is:** Put the front node of every list into a min-heap. Repeatedly pull out the smallest, attach it to your result, and push in whatever node came right after it from the same list — the heap always knows the next-smallest across ALL lists.

**Recognize it by:** merging MORE THAN TWO sorted lists/arrays at once — a heap generalizes the two-pointer merge to k inputs.

**Problem:** Given an array of k sorted linked lists, merge them all into one sorted linked list.

*Example:* lists = [[1,4,5],[1,3,4],[2,6]] → Output: [1,1,2,3,4,4,5,6]

```cpp
struct Compare {
    bool operator()(ListNode* a, ListNode* b) { return a->val > b->val; }
};
ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
    for (auto l : lists) if (l) pq.push(l);
    ListNode dummy(0), *tail = &dummy;
    while (!pq.empty()) {
        ListNode* node = pq.top(); pq.pop();
        tail->next = node; tail = node;
        if (node->next) pq.push(node->next);
    }
    return dummy.next;
}
```
**Time:** O(n log k) where n = total nodes, k = number of lists. **Space:** O(k).

**🔗 Practice:** [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) · [Smallest Range Covering Elements from K Lists](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/) · [Ugly Number II](https://leetcode.com/problems/ugly-number-ii/) · [Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/) · [Find K-th Smallest Pair Distance](https://leetcode.com/problems/find-k-th-smallest-pair-distance/) · [Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/)

### Top-K Frequent Elements (heap + hashmap)
**What it is:** First count how often each element appears using a hashmap, then use a small heap of size k to keep track of only the k most frequent ones seen so far.

**Recognize it by:** "k most/least frequent elements", "k closest points" — top-k by some computed score.

**Problem:** Given an integer array and an integer k, return the k most frequently occurring elements.

*Example:* nums = [1,1,1,2,2,3], k = 2 → Output: [1,2]

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> freq;
    for (int x : nums) freq[x]++;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap; // {freq, val}
    for (auto& [val, f] : freq) {
        minHeap.push({f, val});
        if (minHeap.size() > k) minHeap.pop();
    }
    vector<int> res;
    while (!minHeap.empty()) { res.push_back(minHeap.top().second); minHeap.pop(); }
    return res;
}
```
**Time:** O(n log k). **Space:** O(n).

**🔗 Practice:** [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) · [K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/) · [Task Scheduler](https://leetcode.com/problems/task-scheduler/) · [Reorganize String](https://leetcode.com/problems/reorganize-string/) · [Ugly Number II](https://leetcode.com/problems/ugly-number-ii/) · [Frequency Sort](https://leetcode.com/problems/sort-characters-by-frequency/) · [Rearrange String k Distance Apart](https://leetcode.com/problems/rearrange-string-k-distance-apart/) · [Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/)

---

## 14. Tries

**Intuition:** A tree where each edge is a character; words sharing prefixes share paths. Enables O(word length) prefix/search operations instead of scanning all words.

```cpp
struct TrieNode {
    TrieNode* children[26] = {};
    bool isEnd = false;
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        TrieNode* node = find(word);
        return node && node->isEnd;
    }

    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }

private:
    TrieNode* find(string s) {
        TrieNode* node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!node->children[idx]) return nullptr;
            node = node->children[idx];
        }
        return node;
    }
};
```
**Time:** O(L) per insert/search where L = word length. **Space:** O(total characters inserted × 26) worst case (or use `unordered_map<char,TrieNode*>` for sparser storage).

**Used for:** autocomplete, word search II (backtracking + trie), longest common prefix, IP routing.

---

## 15. Graphs

Representation:
```cpp
vector<vector<int>> adj(n);             // unweighted
adj[u].push_back(v); adj[v].push_back(u); // undirected

vector<vector<pair<int,int>>> wadj(n);  // weighted: {neighbor, weight}
wadj[u].push_back({v, w});
```

### DFS (recursive)
**What it is:** Go as deep as possible down one path before backtracking — dive into a neighbour, then that neighbour's neighbour, and so on, only coming back up once you hit a dead end.

**Recognize it by:** "count connected components / islands", "explore as far as possible", or any grid/graph problem naturally expressed with recursion.

**Problem:** Given a 2D grid of '1' (land) and '0' (water), count the number of islands using depth-first search.

*Example:* grid = [["1","1","0"],["0","1","0"],["0","0","1"]] → Output: 2

```cpp
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    // process node
    for (int nxt : adj[node])
        if (!visited[nxt]) dfs(nxt, adj, visited);
}
```
**Time:** O(V+E). **Space:** O(V) recursion + visited array.

**🔗 Practice:** [Number of Islands](https://leetcode.com/problems/number-of-islands/) · [Clone Graph](https://leetcode.com/problems/clone-graph/) · [Max Area of Island](https://leetcode.com/problems/max-area-of-island/) · [Flood Fill](https://leetcode.com/problems/flood-fill/) · [Surrounded Regions](https://leetcode.com/problems/surrounded-regions/) · [Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/) · [Number of Enclaves](https://leetcode.com/problems/number-of-enclaves/) · [Coloring A Border](https://leetcode.com/problems/coloring-a-border/) · [Number of Closed Islands](https://leetcode.com/problems/number-of-closed-islands/) · [Employee Importance](https://leetcode.com/problems/employee-importance/) · [Keys and Rooms](https://leetcode.com/problems/keys-and-rooms/)

### BFS — shortest path in unweighted graph
**What it is:** Explore the graph in expanding "rings" outward from the start node using a queue. Because you finish visiting everything at distance 1 before moving to distance 2, the first time you reach any node IS via the shortest path.

**Recognize it by:** "fewest steps/moves", "shortest transformation sequence", "minimum number of operations" in an unweighted graph.

**Problem:** Given an unweighted graph and a source node, find the shortest distance (in number of edges) from the source to every other node.

*Example:* adjacency list of a graph, src = 0 → Output: dist[] = shortest hop-count to each node

```cpp
vector<int> bfsShortestPath(int src, vector<vector<int>>& adj, int n) {
    vector<int> dist(n, -1);
    queue<int> q;
    dist[src] = 0; q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }
        }
    }
    return dist;
}
```
**Time:** O(V+E). **Space:** O(V).

**🔗 Practice:** [Word Ladder](https://leetcode.com/problems/word-ladder/) · [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) · [Snakes and Ladders](https://leetcode.com/problems/snakes-and-ladders/) · [Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/) · [Minimum Genetic Mutation](https://leetcode.com/problems/minimum-genetic-mutation/) · [Jump Game III](https://leetcode.com/problems/jump-game-iii/)

### Dijkstra's Algorithm (shortest path, non-negative weights)
**What it is:** Like BFS, but for weighted edges: always expand outward from whichever unvisited node currently has the smallest known distance (tracked with a min-heap), and update its neighbours' distances if a shorter path was just found.

**Recognize it by:** "shortest/cheapest path" with weighted edges, all weights non-negative (e.g. travel time, cost).

**Intuition:** Greedily pick the unvisited node with smallest known distance (via min-heap), relax its neighbors.

**Problem:** Given a weighted graph with non-negative edge weights, a source node, and a target node, find the shortest travel time (or determine it's unreachable).

*Example:* times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, source k = 2 → Output: 2 (time for the signal to reach all nodes)

**Dry Run:**

```text
pop (dist=0, node=2)
  relax edge 2->1 (w=1): dist[1] inf -> 1
  relax edge 2->3 (w=1): dist[3] inf -> 1
pop (dist=1, node=1)
pop (dist=1, node=3)
  relax edge 3->4 (w=1): dist[4] inf -> 2
pop (dist=2, node=4)
Answer: dist[] from node 2 = [1, 0, 1, 2]
```

```cpp
vector<long long> dijkstra(int src, vector<vector<pair<int,int>>>& adj, int n) {
    vector<long long> dist(n, LLONG_MAX);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[src] = 0; pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;         // stale entry
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```
**Time:** O((V+E) log V). **Space:** O(V+E).

**🔗 Practice:** [Network Delay Time](https://leetcode.com/problems/network-delay-time/) · [Path with Maximum Probability](https://leetcode.com/problems/path-with-maximum-probability/) · [Path with Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) · [Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/) · [Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/) · [Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)

### Union-Find (Disjoint Set Union) with path compression + union by rank
**What it is:** A structure for tracking "which group is each item in" and quickly merging two groups together. "Path compression" flattens the lookup chain as you go so future lookups are almost instant.

**Recognize it by:** "connected components", "are these two nodes connected", "will adding this edge create a cycle", "number of provinces/groups".

**Intuition:** Efficiently track connected components; near-O(1) union/find amortized.

**Problem:** Given n cities and a list of direct connections between some of them, find the number of connected 'provinces' (groups of cities reachable from each other).

*Example:* isConnected = [[1,1,0],[1,1,0],[0,0,1]] → Output: 2 provinces

**Dry Run:**

```text
union(0,1): merge root 0 into root 1 -> parent=[1, 1, 2, 3, 4, 5]
union(1,2): merge root 1 into root 2 -> parent=[1, 2, 2, 3, 4, 5]
union(2,3): merge root 2 into root 3 -> parent=[1, 2, 3, 3, 4, 5]
union(0,3): already same group (root 3) -> cycle would form!
  edge (0,3) is redundant — it closes a cycle
```

```cpp
class DSU {
    vector<int> parent, rank_;
public:
    DSU(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;         // already connected (cycle if edge!)
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }
};
```
**Time:** O(α(n)) ≈ O(1) amortized per operation. **Space:** O(n).

**🔗 Practice:** [Number of Provinces](https://leetcode.com/problems/number-of-provinces/) · [Redundant Connection](https://leetcode.com/problems/redundant-connection/) · [Accounts Merge](https://leetcode.com/problems/accounts-merge/) · [Most Stones Removed with Same Row or Column](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/) · [Satisfiability of Equality Equations](https://leetcode.com/problems/satisfiability-of-equality-equations/) · [Number of Islands II](https://leetcode.com/problems/number-of-islands-ii/) · [Smallest String With Swaps](https://leetcode.com/problems/smallest-string-with-swaps/) · [Evaluate Division](https://leetcode.com/problems/evaluate-division/) · [Regions Cut By Slashes](https://leetcode.com/problems/regions-cut-by-slashes/) · [Minimize Malware Spread](https://leetcode.com/problems/minimize-malware-spread/)

### Kruskal's MST (uses DSU)
**What it is:** To connect all nodes as cheaply as possible: sort every edge by weight, cheapest first, and greedily add an edge only if it doesn't create a cycle (checked instantly using Union-Find).

**Recognize it by:** "minimum cost to connect all points/cities", "minimum spanning tree" — connect everything as cheaply as possible with no cycles.

**Problem:** Given a set of points on a plane, connect all of them using the minimum possible total edge cost (a Minimum Spanning Tree), where the cost between two points is their distance.

*Example:* points = [[0,0],[2,2],[3,10],[5,2],[7,0]] → Output: minimum total cost = 20

```cpp
long long kruskalMST(int n, vector<array<int,3>>& edges) { // {weight, u, v}
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    long long total = 0;
    for (auto& [w, u, v] : edges)
        if (dsu.unite(u, v)) total += w;
    return total;
}
```
**Time:** O(E log E). **Space:** O(V+E).

**🔗 Practice:** [Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) · [Connecting Cities With Minimum Cost](https://leetcode.com/problems/connecting-cities-with-minimum-cost/) · [Optimize Water Distribution in a Village](https://leetcode.com/problems/optimize-water-distribution-in-a-village/) · [The Earliest Moment When Everyone Become Friends](https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/) · [Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/) · [Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/)

### Topological Sort (Kahn's Algorithm — BFS based)
**What it is:** Find a valid "order to do things in" when some tasks depend on others finishing first: repeatedly pick off any task that currently has no remaining unfinished dependencies (in-degree 0), then update the tasks that depended on it.

**Recognize it by:** "course schedule", "build order", "task dependencies" — anything with a "must happen before" ordering constraint.

**Intuition:** Repeatedly remove nodes with in-degree 0; valid only for DAGs.

**Problem:** Given numCourses and a list of prerequisite pairs [a, b] (b must be finished before a), determine a valid order to take all courses, or detect that it's impossible.

*Example:* numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]] → Output: [0,1,2,3] (one valid order)

```cpp
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) indeg[v]++;
    queue<int> q;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    return order.size() == n ? order : vector<int>{}; // empty = cycle detected
}
```
**Time:** O(V+E). **Space:** O(V).

**🔗 Practice:** [Course Schedule](https://leetcode.com/problems/course-schedule/) · [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) · [Alien Dictionary (Premium)](https://leetcode.com/problems/alien-dictionary/) · [Sequence Reconstruction](https://leetcode.com/problems/sequence-reconstruction/) · [Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/) · [Course Schedule III](https://leetcode.com/problems/course-schedule-iii/) · [Parallel Courses](https://leetcode.com/problems/parallel-courses/) · [Find All Possible Recipes from Given Supplies](https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/) · [Loud and Rich](https://leetcode.com/problems/loud-and-rich/)

### Cycle Detection
**What it is:** Figure out if a graph loops back on itself. For undirected graphs, Union-Find catches a cycle the moment an edge connects two nodes already in the same group. For directed graphs, DFS tracks nodes "currently being explored" — revisiting one of those means you've found a loop.

**Recognize it by:** "detect a cycle in a graph", "is this graph a valid tree", "find the redundant edge".

- **Undirected graph:** DSU (unite returns false → cycle) or DFS with parent tracking.
- **Directed graph:** DFS with 3 colors (white/gray/black) — a back-edge to a gray node means cycle; or check topo sort produces fewer than n nodes.

**Problem:** Given a list of edges forming a graph that was originally a tree but has one extra edge added, find that redundant edge which creates a cycle.

*Example:* edges = [[1,2],[1,3],[2,3]] → Output: [2,3] is the redundant edge

```cpp
bool hasCycleDirected(int u, vector<vector<int>>& adj, vector<int>& state) {
    // state: 0=unvisited, 1=in progress, 2=done
    state[u] = 1;
    for (int v : adj[u]) {
        if (state[v] == 1) return true;               // back edge -> cycle
        if (state[v] == 0 && hasCycleDirected(v, adj, state)) return true;
    }
    state[u] = 2;
    return false;
}
```
**Time:** O(V+E). **Space:** O(V).

**🔗 Practice:** [Redundant Connection](https://leetcode.com/problems/redundant-connection/) · [Course Schedule](https://leetcode.com/problems/course-schedule/) · [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/) · [Redundant Connection II](https://leetcode.com/problems/redundant-connection-ii/) · [Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/) · [Detect Cycles in 2D Grid](https://leetcode.com/problems/detect-cycles-in-2d-grid/) · [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)

---

## 16. Dynamic Programming

**Intuition:** DP = recursion + memoization (avoid recomputing overlapping subproblems), OR build up bottom-up using a table. Recognize DP when: (1) the problem asks for optimal value / count of ways, and (2) it has **overlapping subproblems** + **optimal substructure** (solution built from solutions to smaller versions of itself).

**General approach:**
1. Define state: what parameters uniquely describe a subproblem? `dp[i]`, `dp[i][j]`, etc.
2. Define recurrence: how does `dp[i]` relate to smaller states?
3. Base case.
4. Decide direction: top-down (recursion + memo) or bottom-up (iterative table).

### 16a. 1D DP — Fibonacci / Climbing Stairs
**What it is:** The answer for step n only depends on the answers for a couple of steps before it. Instead of recomputing those smaller answers every time (which gets exponentially slow), store them once and reuse them.

**Recognize it by:** the answer for n clearly depends only on the answers for a couple of smaller values just before it (n-1, n-2, ...).

**Problem:** You're climbing a staircase of n steps; each move you can climb 1 or 2 steps. Count how many distinct ways there are to reach the top.

*Example:* n = 3 → Output: 3  (1+1+1, 1+2, 2+1)

**Dry Run:**

```text
dp[1]=1, dp[2]=2
dp[3] = dp[2](2) + dp[1](1) = 3
dp[4] = dp[3](3) + dp[2](2) = 5
dp[5] = dp[4](5) + dp[3](3) = 8
Answer: dp[5] = 8
```

```cpp
// Top-down memoization
int memo[10001];
int climbStairs(int n) {
    if (n <= 2) return n;
    if (memo[n]) return memo[n];
    return memo[n] = climbStairs(n-1) + climbStairs(n-2);
}
// Bottom-up, O(1) space
int climbStairsBU(int n) {
    if (n <= 2) return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) { int c = a + b; a = b; b = c; }
    return b;
}
```
**Time:** O(n). **Space:** O(n) memo version, O(1) optimized.

**🔗 Practice:** [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) · [House Robber](https://leetcode.com/problems/house-robber/) · [House Robber II](https://leetcode.com/problems/house-robber-ii/) · [Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/) · [Fibonacci Number](https://leetcode.com/problems/fibonacci-number/) · [Delete and Earn](https://leetcode.com/problems/delete-and-earn/) · [N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/) · [Decode Ways](https://leetcode.com/problems/decode-ways/) · [Paint Fence](https://leetcode.com/problems/paint-fence/)

### 16b. 0/1 Knapsack
**What it is:** For every item, you make a binary choice: take it or skip it — you can't take a fraction of it or take it twice. Build a table where dp[i][w] answers "what's the best value using the first i items within weight limit w".

**Recognize it by:** "each item can be used at most once", "partition into two equal subsets", "can we make exactly this sum" with a hard include/exclude choice per item.

**Intuition:** For each item, decide include or exclude. `dp[i][w]` = best value using first i items with capacity w.

**Problem:** Given an array of positive integers, determine whether it can be split into two subsets whose sums are equal.

*Example:* nums = [1,5,11,5] → Output: true  ({1,5,5} and {11} both sum to 11)

**Dry Run:**

```text
total=22, need subset summing to target=11
considering item 1:
  dp[1] becomes True (via dp[0] + item 1)
considering item 5:
  dp[6] becomes True (via dp[1] + item 5)
  dp[5] becomes True (via dp[0] + item 5)
considering item 11:
  dp[11] becomes True (via dp[0] + item 11)
considering item 5:
  dp[10] becomes True (via dp[5] + item 5)
dp[11] = True  -> Answer: True
```

```cpp
int knapsack01(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i-1][w];                     // exclude item i
            if (wt[i-1] <= w)
                dp[i][w] = max(dp[i][w], dp[i-1][w - wt[i-1]] + val[i-1]); // include
        }
    }
    return dp[n][W];
}
// Space-optimized: 1D array, iterate w from high to low
int knapsack01Optimized(vector<int>& wt, vector<int>& val, int W) {
    vector<int> dp(W+1, 0);
    for (int i = 0; i < wt.size(); i++)
        for (int w = W; w >= wt[i]; w--)
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}
```
**Time:** O(n·W). **Space:** O(n·W) or O(W) optimized.

**🔗 Practice:** [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) · [Target Sum](https://leetcode.com/problems/target-sum/) · [Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/) · [Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/) · [Last Stone Weight](https://leetcode.com/problems/last-stone-weight/) · [Tallest Billboard](https://leetcode.com/problems/tallest-billboard/)

### 16c. Unbounded Knapsack — Coin Change (min coins)
**What it is:** Similar to 0/1 knapsack, but this time each item (coin) can be reused an unlimited number of times — so the table doesn't need to track "which items used", just "what's the best answer for this remaining amount".

**Recognize it by:** "minimum/number of ways to make an amount" where each item/coin CAN be reused unlimited times.

**Problem:** Given a set of coin denominations and a target amount, find the fewest coins needed to make that amount (or -1 if it can't be made).

*Example:* coins = [1,2,5], amount = 11 → Output: 3  (5+5+1)

**Dry Run:**

```text
dp[1] = 1
dp[2] = 1
dp[5] = 1
dp[6] = 2
dp[10] = 2
dp[11] = 3
Answer: dp[11] = 3
```

```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int a = 1; a <= amount; a++)
        for (int c : coins)
            if (c <= a && dp[a-c] != INT_MAX)
                dp[a] = min(dp[a], dp[a-c] + 1);
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}
```
**Time:** O(amount × coins.size()). **Space:** O(amount).

**🔗 Practice:** [Coin Change](https://leetcode.com/problems/coin-change/) · [Coin Change II](https://leetcode.com/problems/coin-change-ii/) · [Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/) · [Perfect Squares](https://leetcode.com/problems/perfect-squares/) · [Minimum Cost For Tickets](https://leetcode.com/problems/minimum-cost-for-tickets/) · [Word Break](https://leetcode.com/problems/word-break/)

### 16d. Longest Common Subsequence (2D DP on strings)
**What it is:** Build a 2D grid where dp[i][j] represents "the answer using the first i characters of string A and the first j characters of string B" — if the current characters match, extend a previous diagonal answer; otherwise take the best of skipping a character from either string.

**Recognize it by:** comparing TWO strings/sequences and the answer depends on characters matching or not — LCS, edit distance, shortest common supersequence all share this table shape.

**Problem:** Given two strings, find the length of their longest common subsequence (characters in the same relative order, not necessarily contiguous).

*Example:* "abcde" and "ace" → Output: 3  ("ace")

**Dry Run:**

```text
DP table (rows=a, cols=b):
      a  c  e
    0  0  0  0
  a 0  1  1  1
  b 0  1  1  1
  c 0  1  2  2
  d 0  1  2  2
  e 0  1  2  3
Answer: dp[5][3] = 3
```

```cpp
int longestCommonSubsequence(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (a[i-1] == b[j-1]) ? dp[i-1][j-1] + 1
                                          : max(dp[i-1][j], dp[i][j-1]);
    return dp[n][m];
}
```
**Time:** O(n·m). **Space:** O(n·m) (can optimize to O(min(n,m))).

**🔗 Practice:** [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) · [Edit Distance](https://leetcode.com/problems/edit-distance/) · [Shortest Common Supersequence](https://leetcode.com/problems/shortest-common-supersequence/) · [Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/) · [Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/) · [Interleaving String](https://leetcode.com/problems/interleaving-string/) · [Uncrossed Lines](https://leetcode.com/problems/uncrossed-lines/) · [Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/) · [Minimum ASCII Delete Sum for Two Strings](https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/)
**Same table powers:** edit distance, longest common substring, shortest common supersequence.

### 16e. Longest Increasing Subsequence
**What it is:** dp[i] means "the longest increasing run of numbers that ENDS exactly at index i". To fill it in, look back at every earlier index with a smaller value and see which one gives the longest chain so far.

**Recognize it by:** "longest increasing/decreasing subsequence" — order must be preserved, but elements don't have to be adjacent.

**Intuition (O(n²)):** `dp[i]` = LIS ending at index i = 1 + max(dp[j]) for all j<i with a[j]<a[i].

**Problem:** Given an integer array, find the length of the longest strictly increasing subsequence.

*Example:* nums = [10,9,2,5,3,7,101,18] → Output: 4  ([2,3,7,101] or [2,3,7,18])

**Dry Run:**

```text
x=10: extends tails -> [10]
x=9: replaces tails[0]=10 -> [9]
x=2: replaces tails[0]=9 -> [2]
x=5: extends tails -> [2, 5]
x=3: replaces tails[1]=5 -> [2, 3]
x=7: extends tails -> [2, 3, 7]
x=101: extends tails -> [2, 3, 7, 101]
x=18: replaces tails[3]=101 -> [2, 3, 7, 18]
Answer: length = 4
```

```cpp
int lengthOfLIS(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1);
    int best = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
    for (int x : dp) best = max(best, x);
    return best;
}
```
**Time:** O(n²). **Space:** O(n).

**🔗 Practice:** [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) · [Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/) · [Number of Longest Increasing Subsequence](https://leetcode.com/problems/number-of-longest-increasing-subsequence/) · [Maximum Length of Pair Chain](https://leetcode.com/problems/maximum-length-of-pair-chain/) · [Longest String Chain](https://leetcode.com/problems/longest-string-chain/) · [Minimum Number of Removals to Make Mountain Array](https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/) · [Longest Continuous Increasing Subsequence](https://leetcode.com/problems/longest-continuous-increasing-subsequence/)

**Intuition (O(n log n)):** Maintain an array `tails` where `tails[k]` = smallest possible tail of an increasing subsequence of length k+1. Binary search to place each element.
```cpp
int lengthOfLIS_fast(vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}
```
**Time:** O(n log n). **Space:** O(n).

### 16f. Grid DP — Unique Paths / Min Path Sum
**What it is:** Moving only right or down through a grid, the best way to reach any cell depends only on the best way to reach the cell above it and the cell to its left — so fill the grid top-left to bottom-right, reusing answers as you go.

**Recognize it by:** moving through a 2D grid only right/down (or similar restricted moves), optimizing a sum or counting paths.

**Problem:** Given an m×n grid of non-negative numbers, find a path from the top-left to the bottom-right corner (moving only right or down) that minimizes the sum of numbers along the path.

*Example:* grid = [[1,3,1],[1,5,1],[4,2,1]] → Output: 7  (path 1→3→1→1→1)

**Dry Run:**

```text
DP table (min cost to reach each cell):
  1  4  5
  2  7  6
  6  8  7
Answer: dp[2][2] = 7
```

```cpp
int minPathSum(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) dp[i][j] = grid[i][j];
            else if (i == 0) dp[i][j] = dp[i][j-1] + grid[i][j];
            else if (j == 0) dp[i][j] = dp[i-1][j] + grid[i][j];
            else dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    return dp[n-1][m-1];
}
```
**Time:** O(n·m). **Space:** O(n·m), optimizable to O(m).

**🔗 Practice:** [Unique Paths](https://leetcode.com/problems/unique-paths/) · [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) · [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) · [Dungeon Game](https://leetcode.com/problems/dungeon-game/) · [Triangle](https://leetcode.com/problems/triangle/) · [Cherry Pickup](https://leetcode.com/problems/cherry-pickup/) · [Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/) · [Out of Boundary Paths](https://leetcode.com/problems/out-of-boundary-paths/) · [Maximal Square](https://leetcode.com/problems/maximal-square/)

### 16g. DP on Trees
**What it is:** Same "combine children's answers" idea as tree height/diameter, but now used to solve an optimization problem — each node computes its best answer using the (already computed) best answers of its children.

**Recognize it by:** an optimization question (max/min sum, longest path, etc.) on a tree, where each node's answer depends on combining its children's answers.

**Intuition:** Compute a value bottom-up via post-order traversal; each node combines results from its children.

**Problem:** Given the root of a binary tree, find the maximum sum of any path between two nodes (the path doesn't need to pass through the root).

*Example:* tree = [1,2,3] → Output: 6  (path 2→1→3)

```cpp
// Max path sum in a binary tree (classic tree DP)
int maxPathSum(TreeNode* root, int& best) {
    if (!root) return 0;
    int left = max(0, maxPathSum(root->left, best));   // ignore negative branches
    int right = max(0, maxPathSum(root->right, best));
    best = max(best, root->val + left + right);        // path through this node
    return root->val + max(left, right);                // best path if extending upward
}
```
**Time:** O(n). **Space:** O(h).

**🔗 Practice:** [Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/) · [House Robber III](https://leetcode.com/problems/house-robber-iii/) · [Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/) · [Longest Univalue Path](https://leetcode.com/problems/longest-univalue-path/) · [Binary Tree Cameras](https://leetcode.com/problems/binary-tree-cameras/) · [Sum Root to Leaf Numbers](https://leetcode.com/problems/sum-root-to-leaf-numbers/) · [Second Minimum Node In a Binary Tree](https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/)

### 16h. Bitmask DP (Traveling Salesman style)
**What it is:** When n is small (≤ ~20), represent "which subset of items have been used so far" as a single integer where each bit means one item — this lets the DP state be just (bitmask, current position) instead of needing a whole separate array per subset.

**Recognize it by:** n is small (≤ ~20) and the state needs to remember "which subset of items has been used/visited so far".

**Intuition:** When n is small (≤ ~20) and state includes "which subset of items used", encode subset as a bitmask.

**Problem:** Given n cities and the distance between every pair, find the minimum-cost route that visits every city exactly once and returns to the starting city.

*Example:* 4 cities with a given distance matrix → Output: the minimum total tour cost

**Dry Run:**

```text
state(mask=0b111, pos=2) -> best cost from here = 50
state(mask=0b1011, pos=3) -> best cost from here = 45
state(mask=0b11, pos=1) -> best cost from here = 70
state(mask=0b111, pos=1) -> best cost from here = 45
state(mask=0b1101, pos=3) -> best cost from here = 35
state(mask=0b101, pos=2) -> best cost from here = 65
... (10 states total explored)
Answer: minimum tour cost = 80
```

```cpp
int n;
vector<vector<int>> dist;
vector<vector<int>> dp; // dp[mask][i] = min cost visiting set `mask`, ending at i
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) return dist[pos][0]; // return to start
    if (dp[mask][pos] != -1) return dp[mask][pos];
    int ans = INT_MAX;
    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city))) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            ans = min(ans, newAns);
        }
    }
    return dp[mask][pos] = ans;
}
```
**Time:** O(n² · 2ⁿ). **Space:** O(n · 2ⁿ).

**🔗 Practice:** [Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/) · [Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/) · [Minimum Cost to Connect Two Groups of Points](https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/) · [Maximum Students Taking Exam](https://leetcode.com/problems/maximum-students-taking-exam/) · [Distribute Repeating Integers](https://leetcode.com/problems/distribute-repeating-integers/) · [Minimum Number of Work Sessions to Finish the Tasks](https://leetcode.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/)

---

## 17. Greedy Algorithms

**Intuition:** Make the locally optimal choice at each step, hoping it leads to a global optimum. Works only when the problem has the **greedy-choice property** — prove it (or trust it's a known greedy problem) before using it; unlike DP, greedy doesn't explore alternatives.

### Activity Selection / Interval Scheduling (max non-overlapping intervals)
**What it is:** Sort all the intervals by their END time, then greedily keep picking whichever remaining interval finishes soonest — finishing early always leaves the most room for whatever comes after.

**Recognize it by:** "maximum non-overlapping intervals", "minimum intervals to remove so none overlap", "maximum meetings you can attend".

**Intuition:** Always pick the interval that finishes earliest — it leaves the most room for future intervals.

**Problem:** Given a list of intervals, find the maximum number of them that can be kept without any two overlapping (equivalently, the minimum number to remove).

*Example:* intervals = [[1,2],[2,3],[3,4],[1,3]] → Output: keep 3 (remove just [1,3])

```cpp
int maxNonOverlapping(vector<pair<int,int>>& intervals) { // {start, end}
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a.second < b.second;                       // sort by end time
    });
    int count = 0, lastEnd = INT_MIN;
    for (auto& [s, e] : intervals) {
        if (s >= lastEnd) { count++; lastEnd = e; }
    }
    return count;
}
```
**Time:** O(n log n). **Space:** O(1) extra (excluding sort).

**🔗 Practice:** [Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/) · [Meeting Rooms](https://leetcode.com/problems/meeting-rooms/) · [Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/) · [Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/) · [Car Pooling](https://leetcode.com/problems/car-pooling/) · [Maximum Length of Pair Chain](https://leetcode.com/problems/maximum-length-of-pair-chain/)

### Merge Intervals
**What it is:** Sort intervals by start time, then walk through them once: if the next interval overlaps with the one you're currently building, stretch it to cover both; otherwise, close it off and start a new one.

**Recognize it by:** "merge overlapping intervals", "insert an interval" into an existing sorted list of intervals.

**Problem:** Given a list of intervals, merge all intervals that overlap and return the resulting non-overlapping set.

*Example:* intervals = [[1,3],[2,6],[8,10],[15,18]] → Output: [[1,6],[8,10],[15,18]]

```cpp
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> res;
    for (auto& iv : intervals) {
        if (!res.empty() && iv[0] <= res.back()[1])
            res.back()[1] = max(res.back()[1], iv[1]);
        else
            res.push_back(iv);
    }
    return res;
}
```
**Time:** O(n log n). **Space:** O(n).

**🔗 Practice:** [Merge Intervals](https://leetcode.com/problems/merge-intervals/) · [Insert Interval](https://leetcode.com/problems/insert-interval/) · [Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/) · [Interval List Intersections](https://leetcode.com/problems/interval-list-intersections/) · [Employee Free Time](https://leetcode.com/problems/employee-free-time/) · [My Calendar I](https://leetcode.com/problems/my-calendar-i/) · [My Calendar II](https://leetcode.com/problems/my-calendar-ii/)

### Fractional Knapsack
**What it is:** Unlike 0/1 knapsack, here you're ALLOWED to take a fraction of an item. So greedily grab items with the best value-per-weight ratio first, and only take a partial amount of the last item that doesn't fully fit.

**Recognize it by:** items CAN be split/taken partially (unlike 0/1 knapsack) and you're maximizing value under a weight/capacity limit.

**Problem:** Given items each with a value and a weight, and a knapsack of limited capacity, maximize total value where items CAN be taken fractionally.

*Example:* items(value,weight) = [(60,10),(100,20),(120,30)], W = 50 → Output: 240

```cpp
double fractionalKnapsack(vector<pair<int,int>>& items, int W) { // {value, weight}
    sort(items.begin(), items.end(), [](auto& a, auto& b) {
        return (double)a.first / a.second > (double)b.first / b.second; // value/weight desc
    });
    double totalValue = 0;
    for (auto& [val, wt] : items) {
        if (W >= wt) { totalValue += val; W -= wt; }
        else { totalValue += val * ((double)W / wt); break; }
    }
    return totalValue;
}
```
**Time:** O(n log n). **Space:** O(1).

**🔗 Practice:** [Maximum Units on a Truck](https://leetcode.com/problems/maximum-units-on-a-truck/) · [IPO](https://leetcode.com/problems/ipo/) · [Minimum Number of Refueling Stops](https://leetcode.com/problems/minimum-number-of-refueling-stops/) · [Two City Scheduling](https://leetcode.com/problems/two-city-scheduling/) · [Boats to Save People](https://leetcode.com/problems/boats-to-save-people/) · [Course Schedule III](https://leetcode.com/problems/course-schedule-iii/)

### Jump Game (greedy reachability)
**What it is:** Track the furthest index you could possibly reach so far as you scan left to right. If at some point your current position is already beyond that furthest-reachable point, you're stuck and can never get further.

**Recognize it by:** "can you reach the last index", "minimum jumps to reach the end" — each position tells you how far you're allowed to jump.

**Problem:** Given an array where each element is the maximum jump length from that position, determine whether you can reach the last index starting from the first.

*Example:* nums = [2,3,1,1,4] → Output: true.   nums = [3,2,1,0,4] → Output: false

```cpp
bool canJump(vector<int>& nums) {
    int reach = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (i > reach) return false;
        reach = max(reach, i + nums[i]);
    }
    return true;
}
```
**Time:** O(n). **Space:** O(1).

**🔗 Practice:** [Jump Game](https://leetcode.com/problems/jump-game/) · [Jump Game II](https://leetcode.com/problems/jump-game-ii/) · [Gas Station](https://leetcode.com/problems/gas-station/) · [Jump Game III](https://leetcode.com/problems/jump-game-iii/) · [Jump Game IV](https://leetcode.com/problems/jump-game-iv/) · [Video Stitching](https://leetcode.com/problems/video-stitching/) · [Jump Game VII](https://leetcode.com/problems/jump-game-vii/)

---

## 18. Bit Manipulation

| Trick | Code | Use |
|---|---|---|
| Check bit i | `(n >> i) & 1` | test if bit set |
| Set bit i | `n \| (1 << i)` | turn bit on |
| Clear bit i | `n & ~(1 << i)` | turn bit off |
| Toggle bit i | `n ^ (1 << i)` | flip bit |
| Remove lowest set bit | `n & (n - 1)` | count set bits, power of 2 check |
| Isolate lowest set bit | `n & (-n)` | Fenwick tree indexing |
| Check power of 2 | `n > 0 && (n & (n-1)) == 0` | — |

### Count set bits (Brian Kernighan's algorithm)
**What it is:** The trick `n & (n - 1)` always clears the LOWEST set bit of n in one operation — so repeating it until n becomes 0 counts exactly how many 1-bits n had, without checking every single bit position one by one.

**Recognize it by:** "count the number of 1 bits", "Hamming weight", or any problem repeatedly checking/clearing individual bits.

**Problem:** Given a non-negative integer, count the number of 1-bits in its binary representation (Hamming weight).

*Example:* n = 11 (binary 1011) → Output: 3

```cpp
int countSetBits(int n) {
    int count = 0;
    while (n) { n &= (n - 1); count++; }
    return count;
}
```
**Time:** O(number of set bits). **Space:** O(1).

**🔗 Practice:** [Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/) · [Counting Bits](https://leetcode.com/problems/counting-bits/) · [Binary Watch](https://leetcode.com/problems/binary-watch/) · [Hamming Distance](https://leetcode.com/problems/hamming-distance/) · [Total Hamming Distance](https://leetcode.com/problems/total-hamming-distance/) · [Number Complement](https://leetcode.com/problems/number-complement/)

### Single Number (XOR trick)
**What it is:** XOR-ing a number with itself gives 0, and XOR-ing with 0 changes nothing — so if every number in an array appears in a pair except one, XOR-ing everything together cancels out all the pairs and leaves only the lonely number.

**Recognize it by:** "every element appears twice except one" (or similar parity-based uniqueness) — a strong hint to try XOR.

**Intuition:** `a ^ a = 0`, `a ^ 0 = a` — XOR-ing all elements cancels out pairs, leaving the unique one.

**Problem:** Given a non-empty array where every element appears twice except for one, find that single element.

*Example:* nums = [4,1,2,1,2] → Output: 4

```cpp
int singleNumber(vector<int>& nums) {
    int result = 0;
    for (int x : nums) result ^= x;
    return result;
}
```
**Time:** O(n). **Space:** O(1).

**🔗 Practice:** [Single Number](https://leetcode.com/problems/single-number/) · [Single Number II](https://leetcode.com/problems/single-number-ii/) · [Single Number III](https://leetcode.com/problems/single-number-iii/) · [Missing Number](https://leetcode.com/problems/missing-number/) · [XOR Operation in an Array](https://leetcode.com/problems/xor-operation-in-an-array/) · [Find the Original Array of Prefix Xor](https://leetcode.com/problems/find-the-original-array-of-prefix-xor/) · [Repeated DNA Sequences](https://leetcode.com/problems/repeated-dna-sequences/)

### Generate all subsets using bitmasking
**What it is:** Every number from 0 to 2ⁿ−1, written in binary, is a unique pattern of "included / not included" for n items — so looping through all those numbers and reading their bits generates every possible subset.

**Recognize it by:** n is small (≤ ~20) and you need every subset — bitmasking is a compact non-recursive alternative to backtracking subsets.

**Problem:** Given an array of distinct integers, generate every possible subset (the power set) by treating each number from 0 to 2ⁿ−1 as an inclusion/exclusion mask.

*Example:* nums = [1,2,3] → Output: all 8 subsets, e.g. mask=101 → {1,3}

```cpp
vector<vector<int>> subsetsBitmask(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> res;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) subset.push_back(nums[i]);
        res.push_back(subset);
    }
    return res;
}
```
**Time:** O(2ⁿ · n). **Space:** O(2ⁿ · n) output.

**🔗 Practice:** [Subsets](https://leetcode.com/problems/subsets/) · [Power of Two](https://leetcode.com/problems/power-of-two/) · [Sum of All Subset XOR Totals](https://leetcode.com/problems/sum-of-all-subset-xor-totals/) · [Maximum XOR of Two Numbers in an Array](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/) · [Count Number of Maximum Bitwise-OR Subsets](https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/) · [Partition Array Into Two Arrays to Minimize Sum Difference](https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/)

---

## 19. Math for DSA

### GCD / LCM
**What it is:** The Greatest Common Divisor of two numbers can be found by repeatedly replacing the bigger number with the remainder of dividing it by the smaller one (Euclid's algorithm) — it shrinks fast, so this converges in very few steps.

**Recognize it by:** reducing fractions, finding a common cycle length, or any "largest number that evenly divides both" question.

**Problem:** Given two positive integers, find their Greatest Common Divisor and Least Common Multiple.

*Example:* a = 12, b = 18 → Output: gcd = 6, lcm = 36

```cpp
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
```
**Time:** O(log(min(a,b))). **Space:** O(log(min(a,b))) recursion (or O(1) iterative).

**🔗 Practice:** [Greatest Common Divisor of Strings](https://leetcode.com/problems/greatest-common-divisor-of-strings/) · [Nth Magical Number](https://leetcode.com/problems/nth-magical-number/) · [Find Greatest Common Divisor of Array](https://leetcode.com/problems/find-greatest-common-divisor-of-array/) · [Water and Jug Problem](https://leetcode.com/problems/water-and-jug-problem/) · [Uncommon Words from Two Sentences](https://leetcode.com/problems/uncommon-words-from-two-sentences/) · [Simplify Path](https://leetcode.com/problems/simplify-path/)

### Sieve of Eratosthenes (all primes up to n)
**What it is:** Starting from 2, cross out every multiple of each prime you find — whatever numbers are never crossed out by the time you finish are exactly the primes. Much faster than checking each number individually for primality.

**Recognize it by:** you need ALL primes up to some n, not just a single primality check — precompute once, answer many queries fast.

**Problem:** Given an integer n, find all prime numbers less than or equal to n.

*Example:* n = 10 → Output: [2, 3, 5, 7]

```cpp
vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; (long long)i * i <= n; i++)
        if (isPrime[i])
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
    return isPrime;
}
```
**Time:** O(n log log n). **Space:** O(n).

**🔗 Practice:** [Count Primes](https://leetcode.com/problems/count-primes/) · [Four Divisors](https://leetcode.com/problems/four-divisors/) · [Prime Arrangements](https://leetcode.com/problems/prime-arrangements/) · [Closest Prime Numbers in Range](https://leetcode.com/problems/closest-prime-numbers-in-range/) · [Prime Palindrome](https://leetcode.com/problems/prime-palindrome/) · [Prime Number of Set Bits in Binary Representation](https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/)

### Fast Exponentiation (modular power)
**What it is:** To compute base^exp, repeatedly square the base and halve the exponent (using the binary representation of the exponent) instead of multiplying base by itself exp times — turns a linear-time operation into a logarithmic one.

**Recognize it by:** computing a huge power modulo something ("mod 1e9+7"), especially with an exponent too large to loop through directly.

**Problem:** Compute (base^exp) mod m efficiently, even when exp is extremely large.

*Example:* base = 2, exp = 10, mod = 1_000_000_007 → Output: 1024

```cpp
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}
```
**Time:** O(log exp). **Space:** O(1).

**🔗 Practice:** [Pow(x, n)](https://leetcode.com/problems/powx-n/) · [Super Pow](https://leetcode.com/problems/super-pow/) · [Count Good Numbers](https://leetcode.com/problems/count-good-numbers/) · [K-th Symbol in Grammar](https://leetcode.com/problems/k-th-symbol-in-grammar/) · [Check if Point Is Reachable](https://leetcode.com/problems/check-if-point-is-reachable/) · [Minimum Non-Zero Product of the Array](https://leetcode.com/problems/minimum-non-zero-product-of-the-array/)

### Factorial / nCr with modular inverse (for large n)
**What it is:** Since normal division doesn't work cleanly under a modulus, "dividing" by a number modulo a prime is done by multiplying by its modular inverse instead (computed via fast exponentiation, using Fermat's Little Theorem).

**Recognize it by:** "number of ways to choose", combinatorics questions with results requested modulo a large prime.

**Problem:** Compute nCr (n choose r) modulo a large prime, for n large enough that factorials overflow normal integers.

*Example:* n = 5, r = 2, MOD = 1e9+7 → Output: 10  (5C2 = 10)

```cpp
const int MOD = 1e9 + 7;
vector<long long> fact;
void precomputeFactorials(int n) {
    fact.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;
}
long long modInverse(long long a) { return power(a, MOD - 2, MOD); } // Fermat's little theorem
long long nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return fact[n] * modInverse(fact[r]) % MOD * modInverse(fact[n-r]) % MOD;
}
```
**Time:** O(n) precompute, O(log MOD) per query. **Space:** O(n).

**🔗 Practice:** [Unique Paths](https://leetcode.com/problems/unique-paths/) · [Unique Paths III](https://leetcode.com/problems/unique-paths-iii/) · [Count Vowels Permutation](https://leetcode.com/problems/count-vowels-permutation/) · [Knight Dialer](https://leetcode.com/problems/knight-dialer/) · [Student Attendance Record II](https://leetcode.com/problems/student-attendance-record-ii/) · [Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/)

---

## 20. How to Practice (Roadmap)

1. **Arrays/Strings/Two Pointers/Sliding Window** (1–2 weeks) — build pattern recognition first, this is 30% of interview questions.
2. **Sorting + Binary Search** (3–5 days) — especially "binary search on answer".
3. **Recursion/Backtracking** (1 week) — draw the recursion tree for every problem until it's automatic.
4. **Linked List, Stack, Queue** (1 week) — mostly pointer manipulation, low conceptual overhead once patterns click.
5. **Trees + BST** (1–2 weeks) — master traversals cold, then move to tree DP and LCA-family problems.
6. **Heaps + Tries** (3–5 days).
7. **Graphs** (2 weeks) — BFS/DFS first, then Dijkstra/Union-Find/MST/Topo sort.
8. **Dynamic Programming** (2–3 weeks, the hardest, highest ROI topic) — go pattern by pattern: 1D → knapsack family → LCS family → grid DP → tree DP → bitmask DP.
9. **Greedy + Bit Manipulation + Math** (1 week) — smaller topics but frequently used as sub-routines.

**Habits that matter more than volume:**
- For every problem: state the **pattern** it belongs to before coding.
- Always state **time and space complexity** out loud, even in practice.
- Redo problems you struggled with after 3–4 days (spaced repetition) rather than only doing new ones.
- Once comfortable, time yourself: 25–35 minutes per medium problem is the interview bar.

---

*This handbook covers the core pattern set used across almost all placement-level DSA rounds (product-based and service-based companies). For company-specific practice, layer in their most frequently asked problems on top of these patterns — the underlying technique will almost always be one from this document.*
