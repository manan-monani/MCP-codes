
# Algorithm:
# 1. Precompute prefix sums for the input array to allow O(1) range sum queries.
# 2. For each query, use the prefix sums to compute the sum of elements between indices left and right.
#    - prefix[i] stores the sum of nums[0] to nums[i].
#    - sumRange(left, right) = prefix[right] - prefix[left-1] (if left > 0), else prefix[right].

class NumArray:


    def __init__(self, nums: List[int]):
        # Step 1: Precompute prefix sums
        # Initialize an empty list to store prefix sums
        self.prefix = []
        cur = 0
        for num in nums:
            cur += num  # Add current number to running total
            self.prefix.append(cur)  # Store running total as prefix sum


    def sumRange(self, left: int, right: int) -> int:
        # Step 2: Answer range sum queries in O(1) time
        # rightSum is the sum from nums[0] to nums[right]
        rightSum = self.prefix[right]
        # leftSum is the sum from nums[0] to nums[left-1] (if left > 0)
        leftSum = self.prefix[left-1] if left > 0 else 0
        # The sum from nums[left] to nums[right] is rightSum - leftSum
        return rightSum - leftSum
        


# Your NumArray object will be instantiated and called as such:
# obj = NumArray(nums)
# param_1 = obj.sumRange(left,right)
#
# Time Complexity: O(1) per query (after O(n) preprocessing)
# Space Complexity: O(n) for prefix sums