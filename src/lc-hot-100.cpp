#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;

// --------------------------------------------------------------------

// 1.两数之和
// 用无序map作哈希，当前遍历到的值能在表中找到它需要的对应值，就直接返回，不能就将当前值加入到哈希表中
// vector<int> twoSum(vector<int> &nums, int target)
// {
//     unordered_map<int, int> temp;
//     for (int i = 0; i < nums.size(); i++)
//     {
//         if (temp.find(target - nums[i]) != temp.end())
//         {
//             return {i, temp[target - nums[i]]};
//         }
//         else
//             temp[nums[i]] = i;
//     }
//     return {};
// }

// 49.字母异位词分组
// 用无序map做哈希，key取字母排序后的“标准字符串”，当前遍历到的字符串排序后如果能在map中找到它对应的标准字符串，
// 就加到该标准字符串后面，不能找到就把它加到自己这个标准字符串后面
// 此题关键是习得——“字母异位词”这种题可以通过字符串排序找到同类——这个思路
// vector<vector<string>> groupAnagrams(vector<string> &strs)
// {
//     vector<vector<string>> res;
//     unordered_map<string, vector<string>> temp;
//     for (int i = 0; i < strs.size(); i++)
//     {
//         string s = strs[i];
//         sort(s.begin(), s.end());
//         temp[s].push_back(strs[i]);
//     }
//     for (auto i : temp)
//     {
//         res.push_back(i.second);
//     }
//     return res;
// }

// 128.最长连续序列---方法一
// 拿到题第一种思路是有点暴力的解法，将数组排序，然后用一个特殊单调递增栈遍历排序后的数组，如果当前数组元素比栈顶元素刚好大1，就入栈；否则就尝试更新res，
// 并将所有元素都出栈，把当前遍历的这个数组元素入栈（相当于一个新的计数周期开始了）。并注意，如果当前元素等于栈顶元素，直接continue跳过
// 这里用栈比双指针好的地方在于，遇到相同元素的时候栈可以不用管直接跳过，双指针还要记录下相同元素的个数然后在求长度的时候减去个数
// int longestConsecutive(vector<int> &nums)
// {
//     if (nums.size() < 2)
//         return nums.size();
//     sort(nums.begin(), nums.end());
//     stack<int> st;
//     st.push(nums[0]);
//     int count = 1;
//     int res = 0;
//     for (int i = 1; i < nums.size(); i++)
//     {
//         int cur = st.top();
//         if (nums[i] == cur)
//             continue;
//         if (nums[i] == cur + 1)
//         {
//             st.push(nums[i]);
//             count++;
//         }
//         else
//         {
//             res = max(res, count);
//             count = 1;
//             while (!st.empty())
//             {
//                 st.pop();
//             }
//             st.push(nums[i]);
//         }
//     }
//     return max(res, count);
// }

// 128.最长连续序列---方法二
// 方法二需要一些解题的想法，我们将数组元素放到set中进行去重，然后遍历set中的元素，如果比当前元素小1的元素在set中，说明当前元素必然不是一个序列的开头，直接跳过；
// 如果没有在set中，说明当前元素必然是一个序列的开头，我们将这个元素作为开头，进入内层的循环——每次加1在set中寻找，找到就将序列长度加1，找不到了就尝试更新res；
// 这个方法很妙！时间复杂度只有O(n)
// int longestConsecutive(vector<int> &nums)
// {
//     unordered_set<int> nset(nums.begin(), nums.end());
//     int count;
//     int res = 0;
//     for (int i : nset)
//     {
//         if (!nset.count(i - 1))
//         {
//             int cur = i;
//             count = 1;
//             while (nset.count(cur + 1))
//             {
//                 cur++;
//                 count++;
//             }
//             res = max(res, count);
//         }
//     }
//     return res;
// }

// 283.移动零
// 和移除元素一样的做法，用双指针，移动完后然后将左指针以及之后的位置的元素全部赋值0
// void moveZeroes(vector<int> &nums)
// {
//     int l = 0;
//     for (int r = 0; r < nums.size(); r++)
//     {
//         if (nums[r] != 0)
//         {
//             nums[l++] = nums[r];
//         }
//     }
//     for (int i = l; i < nums.size(); i++)
//     {
//         nums[i] = 0;
//     }
// }

// 11.盛最多水的容器
// 用双指针法，这道题想到这个解题的思路不是很容易，左右指针分别指向第一根和最后一根，下一步我们要向内移动，容器的长必然是要缩短的，那么想要容量有变大的可能，
// 容器的高就得比现在的两根柱子要高——这里不是说比两根都高，而是比矮的那根高就行了（因为决定容量的是短板.jpg），因此我们要向内移动矮柱子的指针
// int maxArea(vector<int> &height)
// {
//     vector<vector<int>> res;
//     int ans = INT_MIN;
//     int temp;
//     int l = 0, r = height.size() - 1;
//     while (l < r)
//     {
//         temp = (r - l) * min(height[l], height[r]);
//         ans = max(ans, temp);
//         if (height[l] <= height[r])
//         {
//             l++;
//         }
//         else
//         {
//             r--;
//         }
//     }
//     return ans;
// }

// 15.三数之和
// 首先，要以O(1)的速度想到用双指针把三重循环降为一重；其次，要想到得将数组排序；最后，要考虑三个遍历指针的去重细节
// 这个题实在太经典了，里面条件判断语句的编写也要注意，必须是if-else if-else的结构，不能是三个if，因为每个if处理后指针的位置都发生了改变
// vector<vector<int>> threeSum(vector<int> &nums)
// {
//     vector<vector<int>> res;
//     sort(nums.begin(), nums.end());
//     for (int i = 0; i < nums.size(); i++)
//     {
//         if (nums[i] > 0)
//             return res;
//         if (i > 0 && nums[i] == nums[i - 1])
//             continue;
//         int l = i + 1;
//         int r = nums.size() - 1;
//         while (l < r)
//         {
//             if (nums[i] + nums[l] + nums[r] == 0)
//             {
//                 res.push_back({nums[i], nums[l], nums[r]});
//                 while (l < r && nums[l] == nums[l + 1])
//                     l++;
//                 while (l < r && nums[r] == nums[r - 1])
//                     r--;
//                 l++;
//                 r--;
//             }
//             else if (nums[i] + nums[l] + nums[r] > 0)
//             {
//                 r--;
//             }
//             else
//             {
//                 l++;
//             }
//         }
//     }
//     return res;
// }

// 42.接雨水
// 首先想到用单调栈，但是没有想清楚用单增还是单减栈；其次，对于怎么计算雨水想法是错误的
// 看了题解梳理一下：用单减栈，这样当遇到大于栈顶元素的柱子时，说明出现了凹槽，可以计算可盛的雨水了；
// 然后，计算雨水时，是一列一列计算的，不可能一次把一个凹槽的水全算完，因此，遇到比栈顶元素大的柱子时，取栈顶元素计算是一个循环过程，只有当取到的栈顶元素比这个柱子大
// 循环计算雨水的过程才能结束
// 说到一列一列计算，解这个题的暴力想法其实是双指针，对于每一列，都计算它能安放的雨水，应该是分别找到它左边和右边最高的柱子，然后因为他宽度为1，所以他能放的雨水容量是
// (min(height[left], height[right]) - height[cur]) * 1
// int trap(vector<int> &height)
// {
//     stack<int> st;
//     st.push(0);
//     int ans = 0;
//     for (int i = 1; i < height.size(); i++)
//     {
//         if (height[i] < height[st.top()])
//         {
//             st.push(i);
//         }
//         else if (height[i] == height[st.top()])
//         {
//             st.pop();
//             st.push(i);
//         }
//         else
//         {
//             while (!st.empty() && height[i] > height[st.top()])
//             {
//                 int cur = st.top();
//                 st.pop();
//                 if (!st.empty())
//                 {
//                     int h = min(height[st.top()], height[i]) - height[cur];
//                     int w = i - st.top() - 1;
//                     ans += h * w;
//                 }
//             }
//             st.push(i);
//         }
//     }
//     return ans;
// }

// 84.柱状图中的最大矩形
// 和接雨水一样，也是要用单调栈。同样，当没有解题思路的时候，用单调栈也是解不出来的
// 这道题的解题思路是：以当前列作为高的最大矩形面积就是——当前列高度 * 当前列左右第一个比他矮的柱子的下标之差
// 要求当前列左右第一个比他小的列——用单增栈就显而易见了
// 还有关键点就是边界处理，如果第二根柱子就比第一根矮了，这时候没法求下标差；以及，如果柱子高度一直到末尾都是递增的，那一直没有求面积的时候了，结果就会为0
// 为了处理以上两种情况，在原数组首尾都插入0，这样两种特殊情况都会被覆盖到
// int largestRectangleArea(vector<int> &heights)
// {
//     stack<int> st;
//     heights.insert(heights.begin(), 0);
//     heights.push_back(0);
//     st.push(0);
//     int ans = 0;
//     for (int i = 1; i < heights.size(); i++)
//     {
//         if (heights[i] > heights[st.top()])
//         {
//             st.push(i);
//         }
//         else if (heights[i] == heights[st.top()])
//         {
//             st.pop();
//             st.push(i);
//         }
//         else
//         {
//             while (!st.empty() && heights[i] < heights[st.top()])
//             {
//                 int cur = st.top();
//                 st.pop();
//                 if (!st.empty())
//                 {
//                     int w = i - st.top() - 1;
//                     ans = max(ans, w * heights[cur]);
//                 }
//             }
//             st.push(i);
//         }
//     }
//     return ans;
// }

// 739.每日温度
// 难点就是想到用单增栈解决这个问题，以及不要忘记处理那些后面没有比它更大温度的天数，将他们置为0
// vector<int> dailyTemperatures(vector<int> &temperatures)
// {
//     stack<int> st;
//     st.push(0);
//     for (int i = 1; i < temperatures.size(); i++)
//     {
//         if (temperatures[i] <= temperatures[st.top()])
//         {
//             st.push(i);
//         }
//         else
//         {
//             while (!st.empty() && temperatures[i] > temperatures[st.top()])
//             {
//                 temperatures[st.top()] = i - st.top();
//                 st.pop();
//             }
//             st.push(i);
//         }
//     }
//     while (!st.empty())
//     {
//         temperatures[st.top()] = 0;
//         st.pop();
//     }
//     return temperatures;
// }

//-----------------------------------------------------------------------

// 3.无重复字符的最长子串
// 要想到用滑动窗口，对于窗口中的字符用哈希，如果一个字符已经有哈希值，说明重复了，就将左指针移到这个重复字符的下一个位置——因此，哈希的值取的是字符的下标
// 写的时候思路不难，但是要注意细节，更新res的地点是在右指针正常右移后或窗口移动完成后
// int lengthOfLongestSubstring(string s)
// {
//     unordered_map<char, int> cnt;
//     int ans = 0;
//     int l = 0, r = 0;
//     for (; r < s.size(); r++)
//     {
//         if (!cnt.count(s[r]))
//         {
//             cnt[s[r]] = r;
//         }
//         else
//         {
//             while (l <= cnt[s[r]])
//             {
//                 cnt.erase(s[l]);
//                 l++;
//             }
//             cnt[s[r]] = r;
//         }
//         ans = max(ans, r - l + 1);
//     }
//     return ans;
// }

// 438.找到字符串中所有字母异位词
// 首先想到暴力解法：将P排序，然后遍历S，对每个窗口（string cur = s.substr(i, p.size())）中的字符串都排序后判断是否是P的字母异位词——显然，超时了
// 然后想到滑动窗口，用左右指针维护窗口大小（if (r - l + 1 == plen)），窗口中维护的仍是一个哈希表，以及一个valid值。如果窗口等于P，就对左指针做移除
// 这里的移除包含了两个操作——1.更新对valid的影响 2.更新对smap的影响
// vector<int> findAnagrams(string s, string p)
// {
//     vector<int> res;
//     unordered_map<char, int> pmap;
//     unordered_map<char, int> smap;
//     int plen = p.size();
//     int slen = s.size();
//     if (slen < plen)
//         return {};
//     int valid = 0;
//     for (char c : p)
//     {
//         pmap[c]++;
//     }
//     for (int l = 0, r = 0; r < slen; r++)
//     {
//         if (pmap.count(s[r]))
//         {
//             smap[s[r]]++;
//             if (pmap[s[r]] == smap[s[r]])
//             {
//                 valid++;
//             }
//         }
//         if (r - l + 1 == plen)
//         {
//             if (valid == pmap.size())
//             {
//                 res.push_back(l);
//             }
//             if (smap.count(s[l]))
//             {
//                 if (smap[s[l]] == pmap[s[l]])
//                 {
//                     valid--;
//                 }
//                 smap[s[l]]--;
//             }
//             l++;
//         }
//     }
//     return res;
// }

// 560.和为K的子数组
// 首先想到的是暴力解，但不出意外超时了
// 这是第一次接触前缀和的解法：pre[i]为从数组下标0到下标i的和，也就是i的前缀和，所求的和为k的子数组下标为（i，j），即可转化为：pre[j] - pre[i] == k；
// 这里区间如果求具体下标，那就必须要严谨，按照我们的定义，如果所求和为k的子数组下标为（i，j），那么应该是：pre[j] - pre[i - 1] == k；
// 又根据两数之和的哈希套路，可以使用哈希来简化求和过程
// 因此，第一步：求前缀和数组；第二步，遍历使用哈希表求解——这两步可以合在同一个循环中进行
// int subarraySum(vector<int> &nums, int k)
// {
//     int res = 0;
//     int sum = 0;
//     unordered_map<int, int> nmap;
//     nmap[0] = 1; //这里其实就是当起始点i为0的时候，到当前j的前缀和正好等于k，则表明是有一种情况的，所以nmap[0]必须要初始化为1，不然就漏掉了这种情况
//     for (int i : nums)
//     {
//         sum += i;
//         if (nmap.find(sum - k) != nmap.end())
//             res += nmap[sum - k];
//         nmap[sum]++;
//     }
//     return res;
// }

// 239.滑动窗口最大值
// 这个题理解题意很容易，但是想出解决方法真的有点难
// 看了题解，需要用deque实现一个特殊单调队列——之前写的题多数用的是单调栈，单调队列第一次用
// deque是一个双端数组，对头尾都可以使用push和pop【push_front\pop_front\push_back\pop_back】
// 这个单调递减队列维护窗口中的最大值以及可能成为最大值的数字——要理解这句话，必须要想明白：
// 窗口移动时，最大值只和当前窗口最大值、即将移入窗口的值、即将移出窗口的值这三个数有关，和窗口中其他值没什么关系
// 队列维护成单调递减，就是为了留存可能成为窗口最大值的值
// private:
// class MyQueue //因为实现一个单调递减队列有多个操作函数，用一个类封装起来
// {
// public:
//     deque<int> que; //用deque做基础来实现，因为它是双端的，便于头出尾入，贴合本题构造要求
//     void pop(int value)
//     {
//         if (!que.empty() && que.front() == value)
//         {
//             que.pop_front();
//         }
//     }
//     void push(int value)
//     {
//         while (!que.empty() && que.back() < value)
//         {
//             que.pop_back();
//         }
//         que.push_back(value);
//     }
//     int front()
//     {
//         return que.front();
//     }
// };
// public:
// vector<int> maxSlidingWindow(vector<int> &nums, int k)
// {
//     MyQueue que;
//     vector<int> res;
//     for (int i = 0; i < k; i++)
//     {
//         que.push(nums[i]);
//     }
//     res.push_back(que.front());
//     for (int i = k; i < nums.size(); i++)
//     {
//         que.pop(nums[i - k]);
//         que.push(nums[i]);
//         res.push_back(que.front());
//     }
//     return res;
// }

// 76.最小覆盖子串
// 字母异位词+滑动窗口的组合题，和438.找到字符串中所有字母异位词这个题思路一致
// string minWindow(string s, string t)
// {
//     int ans = INT_MAX;
//     int start = 0;
//     if (s.size() < t.size())
//         return "";
//     unordered_map<char, int> tmap;
//     unordered_map<char, int> smap;
//     for (char c : t)
//     {
//         tmap[c]++;
//     }
//     int valid = 0;
//     for (int l = 0, r = 0; r < s.size(); r++)
//     {
//         if (tmap.count(s[r]))
//         {
//             smap[s[r]]++;
//             if (smap[s[r]] == tmap[s[r]])
//             {
//                 valid++;
//             }
//         }
//         while (valid == tmap.size())
//         {
//             if (smap.count(s[l]))
//             {
//                 if (tmap[s[l]] == smap[s[l]])
//                 {
//                     if (ans > r - l + 1)
//                     {
//                         ans = r - l + 1;
//                         start = l;
//                     }
//                     valid--;
//                 }
//                 smap[s[l]]--;
//             }
//             l++;
//         }
//     }
//     if (ans == INT_MAX)
//         return "";
//     return s.substr(start, ans);
// }

// 53.最大子数组和
// 这个题拿到手条件反射就是前缀和，但是不用那么麻烦，这个题目有特殊性，因为要求最大和，如果前面部分和为负数或者0，就可以直接舍去
// 注意代码里，两个if的位置不可以互换
// int maxSubArray(vector<int> &nums)
// {
//     int ans = INT_MIN;
//     int sum = 0;
//     for (int i = 0; i < nums.size(); i++)
//     {
//         sum += nums[i];
//         if (sum > ans)
//             ans = sum;
//         if (sum < 0)
//             sum = 0;
//     }
//     return ans;
// }
// 看到题解里有一个详细的动态规划的解法，写得超级好，也按标准动规思路写一下
// int maxSubArray(vector<int> &nums)
// {
//     vector<int> dp(nums.size(), 0);
//     dp[0] = nums[0];
//     int ans = dp[0];
//     for (int i = 1; i < nums.size(); i++)
//     {
//         dp[i] = max(nums[i], dp[i - 1] + nums[i]);
//         ans = max(ans, dp[i]);
//     }
//     return ans;
// }

//-----------------------------------------------------------------------

// 56.合并区间
// 分析之后就是判断区间有没有交集，按分析思路写，但要注意两个细节
// 1.要将数组先按照起始值由小到大排序，否则如果最大区间出现在末尾，就无法完成合并
// 2.比较的时候是取结果数组中最后一个进行比较，而不是原数组中i和i-1进行比较
// static bool mycmp(const vector<int> &a, const vector<int> &b)
// {
//     return a[0] < b[0];
// }
// vector<vector<int>> merge(vector<vector<int>> &intervals)
// {
//     if (intervals.size() < 1)
//         return intervals;
//     sort(intervals.begin(), intervals.end(), mycmp);
//     vector<vector<int>> res;
//     res.push_back(intervals[0]);
//     for (int i = 1; i < intervals.size(); i++)
//     {
//         vector<int> v1 = res.back();
//         vector<int> v2 = intervals[i];
//         if (v2[0] <= v1[1] && v2[1] >= v1[0])
//         {
//             res.pop_back();
//             res.push_back({min(v1[0], v2[0]), max(v1[1], v2[1])});
//         }
//         else
//         {
//             res.push_back(intervals[i]);
//         }
//     }
//     return res;
// }

// 189.轮转数组
// 哎呀气死啦，之前做过翻转字符串的相关题，到数组就一点没想起来解题方法
// 这个题如果不能新开数组，就用原地翻转的思想，先翻转整个数组，然后分别翻转前K和后面，就能得到右移K个的数组了
// 注意：要对K进行判0和取模处理
// void rotate(vector<int> &nums, int k)
// {
//     if (nums.size() < 1 || k == 0)
//         return;
//     int len = nums.size();
//     int newk = k % len;
//     reverse(nums.begin(), nums.end());
//     reverse(nums.begin(), nums.begin() + newk);
//     reverse(nums.begin() + newk, nums.end());
// }
// 新开数组，那么就进行一下运算，n[i]会被放在新数组new[(i + k) % n.size()]的位置
// void rotate(vector<int> &nums, int k)
// {
//     int len = nums.size();
//     vector<int> newn(len);
//     for (int i = 0; i < len; i++)
//     {
//         newn[(i + k) % len] = nums[i];
//     }
//     nums.assign(newn.begin(), newn.end());
// }

// 238.除自身以外数组的乘积
// 用除法是最简单的，但是题目要求不能用除法
// 用两个新开数组，一个存前缀积，一个存后缀积，然后对于下标i，前缀积乘后缀积就是除它以外数组的积
// vector<int> productExceptSelf(vector<int> &nums)
// {
//     int len = nums.size();
//     vector<int> ans(len, 0);
//     vector<int> pre(len, 0);
//     vector<int> back(len, 0);
//     pre[0] = 1;
//     for (int i = 1; i < len; i++)
//     {
//         pre[i] = pre[i - 1] * nums[i - 1];
//     }
//     back[len - 1] = 1;
//     for (int i = len - 2; i >= 0; i--)
//     {
//         back[i] = back[i + 1] * nums[i + 1];
//     }
//     for (int i = 0; i < len; i++)
//     {
//         ans[i] = pre[i] * back[i];
//     }
//     return ans;
// }

// 41.缺失的第一个正数
// 按照朴素思路写了一版代码，ac了但应该不满足题目的限制要求
// int firstMissingPositive(vector<int> &nums)
// {
//     set<int> nset(nums.begin(), nums.end());
//     int i = 1;
//     for (; i <= nset.size(); i++)
//     {
//         if (nset.find(i) == nset.end())
//             return i;
//     }
//     return i;
// }

// 73.矩阵置零
// 用visited记录被更改过的0，遍历矩阵，遇到没有被更改过的0，就将它行列里不为零的都置零切标记为true
// void setZeroes(vector<vector<int>> &matrix)
// {
//     int m = matrix.size();
//     int n = matrix[0].size();
//     vector<vector<bool>> visited(m, vector<bool>(n, false));
//     for (int i = 0; i < m; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             if (matrix[i][j] == 0 && visited[i][j] == false)
//             {
//                 visited[i][j] = true;
//                 for (int newi = i, k = 0; k < n; k++)
//                 {
//                     if (matrix[newi][k] != 0)
//                     {
//                         matrix[newi][k] = 0;
//                         visited[newi][k] = true;
//                     }
//                 }
//                 for (int newj = j, t = 0; t < m; t++)
//                 {
//                     if (matrix[t][newj] != 0)
//                     {
//                         matrix[t][newj] = 0;
//                         visited[t][newj] = true;
//                     }
//                 }
//             }
//         }
//     }
// }

// 54.螺旋矩阵
// 做这个题真的要非常细心&耐心
// 自己写了一版，ac了，就按照普通遍历思路写的，因为m,n大小可能不一样，这个题比之前做的螺旋矩阵要难一点点
// vector<int> spiralOrder(vector<vector<int>> &matrix)
// {
//     int m = matrix.size();
//     int n = matrix[0].size();
//     vector<int> res;
//     int starx = 0, stary = 0;
//     int loop = min(m, n) / 2;
//     int offset = 0;
//     while (loop)
//     {
//         int endx = m - 1 - offset;
//         int endy = n - 1 - offset;
//         for (int j = stary; j < endy; j++)
//         {
//             res.push_back(matrix[starx][j]);
//         }
//         for (int i = starx; i < endx; i++)
//         {
//             res.push_back(matrix[i][endy]);
//         }
//         for (int j = endy; j > stary; j--)
//         {
//             res.push_back(matrix[endx][j]);
//         }
//         for (int i = endx; i > starx; i--)
//         {
//             res.push_back(matrix[i][stary]);
//         }
//         starx++;
//         stary++;
//         offset++;
//         loop--;
//     }
//     if (m < n && m % 2)
//     {
//         int i = m / 2;
//         int j = i;
//         while (j <= m / 2 + n - m)
//         {
//             res.push_back(matrix[i][j]);
//             j++;
//         }
//     }
//     if (m > n && n % 2)
//     {
//         int j = n / 2;
//         int i = j;
//         while (i <= n / 2 + m - n)
//         {
//             res.push_back(matrix[i][j]);
//             i++;
//         }
//     }
//     if (m == n && m % 2)
//     {
//         res.push_back(matrix[m / 2][n / 2]);
//     }
//     return res;
// }
// 看了一个题解，真的优秀！！！定义上下左右四个边界，每次扫描一条边然后更新一下对应边界的值，太优秀了！！！
// 比起上面的解法，这叫一个干净利落！
// vector<int> spiralOrder(vector<vector<int>> &matrix)
// {
//     int m = matrix.size();
//     int n = matrix[0].size();
//     vector<int> res;
//     int up = 0;
//     int down = m - 1;
//     int left = 0;
//     int right = n - 1;
//     while (true)
//     {
//         for (int j = left; j <= right; j++)
//             res.push_back(matrix[up][j]);
//         if (++up > down)
//             break;
//         for (int i = up; i <= down; i++)
//             res.push_back(matrix[i][right]);
//         if (--right < left)
//             break;
//         for (int j = right; j >= left; j--)
//             res.push_back(matrix[down][j]);
//         if (--down < up)
//             break;
//         for (int i = down; i >= up; i--)
//             res.push_back(matrix[i][left]);
//         if (++left > right)
//             break;
//     }
//     return res;
// }

// 48.旋转图像
// 这题写到心态爆炸，自己写了半天分析不清楚坐标，看了一个题解，真的牛，按题解的思路写的
// void rotate(vector<vector<int>> &matrix)
// {
//     int n = matrix.size();
//     for (int i = 0; i < n / 2; i++)
//     {
//         for (int j = 0; j < (n + 1) / 2; j++)
//         {
//             int temp = matrix[i][j];
//             matrix[i][j] = matrix[n - 1 - j][i];
//             matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
//             matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
//             matrix[j][n - 1 - i] = temp;
//         }
//     }
// }

// 240.搜索二维矩阵
// 第一想法是用二分，但是一通写完提交报错，发现二分的思路错误
// 再想，用逻辑模拟，从右上角出发，目标值大就下移，小就左移（有点像贪心）
// 看了一下题解，这个思路是对的，但是代码写的不好，重新梳理一下思路后写出了优雅的代码
// bool searchMatrix(vector<vector<int>> &matrix, int target)
// {
//     int m = matrix.size();
//     int n = matrix[0].size();
//     int i = 0, j = n - 1;
//     while (i < m && j >= 0)
//     {
//         if (target > matrix[i][j])
//         {
//             i++;
//         }
//         else if (target < matrix[i][j])
//         {
//             j--;
//         }
//         else
//             return true;
//     }
//     return false;
// }

//-----------------------------------------------------------------------

// 160.相交链表
// 明白相交的定义是下一个节点是同一个节点，而不是下一个节点的值相同
// 过程就是按照思路模拟的
// ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
// {
//     ListNode *curA = headA;
//     ListNode *curB = headB;
//     int lenA = 0, lenB = 0;
//     while (curA != NULL)
//     {
//         curA = curA->next;
//         lenA++;
//     }
//     while (curB != NULL)
//     {
//         curB = curB->next;
//         lenB++;
//     }
//     curA = headA;
//     curB = headB;
//     if (lenA < lenB)
//     {
//         swap(lenA, lenB);
//         swap(curA, curB);
//     }
//     int diff = lenA - lenB;
//     while (diff--)
//     {
//         curA = curA->next;
//     }
//     while (curA != NULL)
//     {
//         if (curA == curB)
//         {
//             return curA;
//         }
//         curA = curA->next;
//         curB = curB->next;
//     }
//     return NULL;
// }

// 206.反转链表
// 用三个指针，pre, cur, nxt，不需要虚拟头节点
// ListNode *reverseList(ListNode *head)
// {
//     ListNode *pre = nullptr;
//     ListNode *cur = head;
//     ListNode *nxt;
//     while (cur != nullptr)
//     {
//         nxt = cur->next;
//         cur->next = pre;
//         pre = cur;
//         cur = nxt;
//     }
//     return pre;
// }

// 234.回文链表
// 最开始想用一个指针指向头，一个指向尾，然后头右移尾左移，后来发现想多了，这是链表，尾指针左移办不到
// 然后想用一个数组存链表节点值，每次比较头指针和数组尾的值，可行
// bool isPalindrome(ListNode *head)
// {
//     vector<int> vec;
//     ListNode *curH = head;
//     while (curH != nullptr)
//     {
//         vec.push_back(curH->val);
//         curH = curH->next;
//     }
//     curH = head;
//     while (curH != nullptr)
//     {
//         if (curH->val != vec.back())
//             return false;
//         curH = curH->next;
//         vec.pop_back();
//     }
//     return true;
// }

// 141.环形链表
// 拿到题后第一想法是双指针，但是因为没想通循环怎么写，就放弃了这个方法，然后，就在哪里纠结犹豫
// 发现自己有个问题，就是不敢尝试，想对自己说，你要知道，题目的解法不是靠犹豫，想，就能解出来的，必须要尝试，哪怕觉得写法不完美，也要写一下试一下再说
// 然后就试了一下用map存走过的节点，可行，ac了
// bool hasCycle(ListNode *head)
// {
//     unordered_map<ListNode *, int> lmap;
//     ListNode *cur = head;
//     while (cur != NULL)
//     {
//         if (!lmap.count(cur))
//         {
//             lmap[cur]++;
//             cur = cur->next;
//         }
//         else
//             return true;
//     }
//     return false;
// }
// 写上面代码的时候突然意识到循环条件该怎么写了，就把快慢指针解法写出来了。比上面空间复杂度好，因为没有新开map
// 要注意第一句判空以及循环条件中对空指针的判断，以前写的时候不是很明白，今天自己想才知道，对谁判空取决于一种情况——当前如果是空指针，那么取空指针的next一定会报错
// 因此，可能取next的指针都要进行判空处理
// 写完下一题又回来看了一下这个题的代码，还能优化一下，不需要再第一句就进行判空，直接用循环条件做判空就可以，循环体里面先移动，移动完后再进行比较
// bool hasCycle(ListNode *head)
// {
//     ListNode *curs = head;
//     ListNode *curf = head;
//     while (curf != NULL && curf->next != NULL)
//     {
//         curs = curs->next;
//         curf = curf->next->next;
//         if (curs == curf)
//             return true;
//     }
//     return false;
// }

// 142.环形链表||
// 拿到题后有思路，之前做过这个题，知道怎么推导入口，自己写了一版代码也ac了
// 回去复习了一下卡哥的推导过程，也看了一下卡哥原版代码，优雅！对比起来自己写的还是有不少冗余的判断，又更改了一下自己的代码
// ListNode *detectCycle(ListNode *head)
// {
//     ListNode *curs = head;
//     ListNode *curf = head;
//     while (curf != NULL && curf->next != NULL)
//     {
//         curs = curs->next;
//         curf = curf->next->next;
//         if (curs == curf)
//         {
//             ListNode *pre = head;
//             ListNode *back = curf;
//             while (pre != back)
//             {
//                 pre = pre->next;
//                 back = back->next;
//             }
//             return pre;
//         }
//     }
//     return NULL;
// }

// 21.合并两个有序链表
// 采用了新开一个链表来存合并后的链表
// ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
// {
//     ListNode *newL = new ListNode(0);
//     ListNode *curn = newL;
//     ListNode *cur1 = list1;
//     ListNode *cur2 = list2;
//     while (cur1 != nullptr && cur2 != nullptr)
//     {
//         if (cur1->val < cur2->val)
//         {
//             curn->next = cur1;
//             cur1 = cur1->next;
//         }
//         else
//         {
//             curn->next = cur2;
//             cur2 = cur2->next;
//         }
//         curn = curn->next;
//     }
//     if (cur1 == nullptr)
//     {
//         curn->next = cur2;
//     }
//     if (cur2 == nullptr)
//     {
//         curn->next = cur1;
//     }
//     return newL->next;
// }

// 2.两数相加---链表
// 第一版代码写出来ac了，但是冗余部分多，看了一下题解，找到了解决办法，将短链表用0代替
// ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
// {
//     ListNode *newL = new ListNode(0);
//     ListNode *cur = newL;
//     int temp = 0;
//     while (l1 != nullptr || l2 != nullptr)
//     {
//         int n1 = l1 != nullptr ? l1->val : 0;
//         int n2 = l2 != nullptr ? l2->val : 0;
//         int count = n1 + n2;
//         if (temp)
//             count++;
//         if (count > 9)
//         {
//             count %= 10;
//             temp = 1;
//         }
//         else
//             temp = 0;
//         if (l1 != nullptr)
//             l1 = l1->next;
//         if (l2 != nullptr)
//             l2 = l2->next;
//         cur->next = new ListNode(count);
//         cur = cur->next;
//     }
//     if (temp)
//     {
//         cur->next = new ListNode(temp);
//     }
//     return newL->next;
// }

// 19.删除链表的倒数第n个节点
// 用双指针，可以不用遍历求链表长度，设置一个虚拟头节点（为了不对原本头节点做特殊处理）快指针先前移 n + 1位，然后快慢指针一起移动
// 当快指针指向尾部空指针的时候，慢指针就指向要删除节点的前一个节点了
// ListNode *removeNthFromEnd(ListNode *head, int n)
// {
//     ListNode *dummyhead = new ListNode(0);
//     dummyhead->next = head;
//     ListNode *s = dummyhead;
//     ListNode *f = dummyhead;
//     while (n--)
//     {
//         f = f->next;
//     }
//     f = f->next;
//     while (f != nullptr)
//     {
//         s = s->next;
//         f = f->next;
//     }
//     s->next = s->next->next;
//     return dummyhead->next;
// }

// 24.两两交换链表中的节点
// 老熟人了，用三个指针进行交换，每次只处理两个相关节点，一步一步来，不要想着一口气换完一堆节点，经常练才不会换着换着换晕了
// ListNode *swapPairs(ListNode *head)
// {
//     ListNode *dummyhead = new ListNode(0);
//     dummyhead->next = head;
//     ListNode *pre = dummyhead;
//     ListNode *cur = head;
//     ListNode *nxt;
//     while (cur != nullptr && cur->next != nullptr)
//     {
//         nxt = cur->next;
//         cur->next = nxt->next;
//         nxt->next = cur;
//         pre->next = nxt;
//         pre = cur;
//         cur = cur->next;
//     }
//     return dummyhead->next;
// }

// 25.K个一组翻转链表
// 之前做这个题用了很久，这次还是用了很久，反思了一下，就是细节方面写得很差，整体思路是对的，但是边界条件一直写不对，最后还是写崩了看了之前的代码
// 首先是翻转链表这个子函数，里面的循环判断语句一直没写对
// 其次是K个翻转的时候，没有把当前遍历节点为空（即已经到了链表尾部）考虑进去，导致一直报空指针错误
// pair<ListNode *, ListNode *> reverseList(ListNode *start, ListNode *end)
// {
//     ListNode *pre = nullptr;
//     ListNode *cur = start;
//     ListNode *nxt;
//     while (pre != end)
//     {
//         nxt = cur->next;
//         cur->next = pre;
//         pre = cur;
//         cur = nxt;
//     }
//     return {end, start};
// }
// ListNode *reverseKGroup(ListNode *head, int k)
// {
//     ListNode *dummyhead = new ListNode(0);
//     dummyhead->next = head;
//     ListNode *prev = dummyhead;
//     while (head)
//     {
//         ListNode *cur = prev;
//         for (int i = 0; i < k; i++)
//         {
//             cur = cur->next;
//             if (cur == nullptr)
//                 return dummyhead->next;
//         }
//         ListNode *nxt = cur->next;
//         pair<ListNode *, ListNode *> res;
//         res = reverseList(head, cur);
//         prev->next = res.first;
//         res.second->next = nxt;
//         prev = res.second;
//         head = nxt;
//     }
//     return dummyhead->next;
// }
