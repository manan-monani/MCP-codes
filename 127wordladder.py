class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        if (endWord not in wordList) or (beginWord == endWord):
            return 0
        words, res = set(wordList), 0
        q = deque([beginWord])
        while q:
            res += 1
            for _ in range(len(q)):
                node = q.popleft()
                if node == endWord:
                    return res
                for i in range(len(node)):
                    for c in range(97, 123):
                        if chr(c) == node[i]:
                            continue
                        nei = node[:i] + chr(c) + node[i + 1:]
                        if nei in words:
                            q.append(nei)
                            words.remove(nei)
        return 0
    

# Algorithm
# Convert the word list to a set for O(1) lookups.
# Start BFS from beginWord with distance counter set to 0.
# For each word in the current level, generate all possible words by changing one character at a time.
# If a generated word is in the word set, add it to the queue and remove it from the set to mark as visited.
# Return the distance when endWord is found, or 0 if the queue empties.

# time : O(m^2 . n)
# space : O(m^2 . n)