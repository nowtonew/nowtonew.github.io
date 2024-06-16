#include <iostream>
#include <map>
#include <set>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

// 11.机器人搬砖
// bool isEnough(int k, int hour, vector<int> &num)
// {
//     int time = 0;
//     for (int i = 0; i < num[i]; i++)
//     {
//         time += num[i] / k + (num[i] % k == 0 ? 0 : 1);
//         if (time > hour)
//             return false;
//     }
//     return true;
// }

// int main()
// {
//     int num;
//     int max = 0;
//     vector<int> bricks;
//     while (cin >> num)
//     {
//         bricks.push_back(num);
//         max = max < num ? num : max;
//         if (getchar() == '\n')
//             break;
//     }
//     cout << "max = " << max << endl;
//     int len = bricks.size();
//     cout << "len = " << len << endl;
//     if (len >= 8) // 仓库数量等于8输出砖块最大堆的值，大于8机器人搬不完输入-1
//     {
//         cout << (len > 8 ? -1 : max) << endl;
//         return 0;
//     }
//     int mid = 0;
//     int l = 1;
//     int ans = 0; // 要用ans记录最可能的值
//     while (l <= max)
//     {
//         mid = l + (max - l) / 2;
//         cout << "---mid = " << mid << endl;
//         if (isEnough(mid, 8, bricks))
//         {
//             max = mid - 1;
//             ans = mid;
//         }
//         else
//         {
//             l = mid + 1;
//         }
//     }
//     cout << ans << endl;
//     return 0;
// }

// 12.内存冷热标记
// int main()
// {
//     unordered_map<int, int> n_map;
//     vector<int> res;
//     int n;
//     cin >> n;
//     int num;
//     while (cin >> num)
//     {
//         n_map[num]++;
//         if (getchar() == '\n')
//             break;
//     }
//     int f;
//     cin >> f;
//     for (auto it : n_map)
//     {
//         if (it.second >= f)
//         {
//             res.push_back(it.first);
//         }
//     }
//     sort(res.begin(), res.end());
//     cout << res.size() << endl;
//     for (auto it : res)
//         cout << it << endl;
//     return 0;
// }

// 13.虚拟理财游戏
//------以下是第一版错误解法---试图用多重背包去解
// int main()
// {
//     int product; // 产品数量---即物品数量
//     cin >> product;
//     int money; // 总投资额---限定条件
//     cin >> money;
//     int bag; // 可接受的总风险---即背包容量
//     cin >> bag;
//     vector<int> val;
//     int val_num; // 投资回报率序列---即每个物品价值
//     while (cin >> val_num)
//     {
//         val.push_back(val_num);
//         if (getchar() == '\n')
//             break;
//     }
//     vector<int> weight;
//     int weight_num; // 风险序列---即每个物品重量
//     while (cin >> weight_num)
//     {
//         weight.push_back(weight_num);
//         if (getchar() == '\n')
//             break;
//     }
//     vector<int> pro_num;
//     int pro_num_num; // 每个产品可投资个数---即多重背包中的每种物品个数
//     while (cin >> pro_num_num)
//     {
//         pro_num.push_back(pro_num_num);
//         if (getchar() == '\n')
//             break;
//     }
//     vector<int> dp(bag + 1, 0); // dp数组以及初始化
//     for (int j = bag; j >= weight[0]; j--)
//     {
//         dp[j] = val[0];
//     }
//     vector<int> res; // 结果数组
//     for (int i = 0; i < product; i++){ //遍历物品
//         int max = 0;
//         for (int j = bag; j >= weight[i]; j--)
//         {                                          // 倒序遍历背包
//             for (int k = 1; k <= pro_num[i]; k++){ //遍历每种物品个数
//                 if(dp[j] < dp[j - k * weight[i]] + k * val[i]){
//                     dp[j] = dp[j - k * weight[i]] + k * val[i];
//                     max = k;
//                 }
//             }
//         }
//     }
// }

// 以下为正确解法
// 刚还在疑惑这个金额限制怎么加上去，结果发现看漏了题目的限制条件，这题不用多重背包，吐血
// 用暴力枚举，细节也非常多，写得困难
// int main()
// {
//     int product;
//     int money;
//     int risk;
//     cin >> product >> money >> risk;
//     vector<int> profit;
//     int profit_num;
//     while (cin >> profit_num)
//     {
//         profit.push_back(profit_num);
//         if (getchar() == '\n')
//             break;
//     }
//     vector<int> risks;
//     int risk_num;
//     while (cin >> risk_num)
//     {
//         risks.push_back(risk_num);
//         if (getchar() == '\n')
//             break;
//     }
//     vector<int> put;
//     int put_num;
//     while (cin >> put_num)
//     {
//         put.push_back(put_num);
//         if (getchar() == '\n')
//             break;
//     }
//     int max_profit = INT_MIN;
//     vector<int> res(product, 0);
//     vector<vector<int>> tag(2, vector<int>(2, -1));
//     for (int i = 0; i < product; i++) // 暴力枚举产品
//     {
//         if (risks[i] <= risk) // 只买这一种
//         {
//             int max_put = put[i] > money ? money : put[i];
//             if (max_put * profit[i] > max_profit)
//             {
//                 max_profit = max_put * profit[i];
//                 tag[0][0] = i;
//                 tag[0][1] = max_put;
//             }
//         }
//         else
//         {
//             continue;
//         }
//         for (int j = i + 1; j < product; j++) // 买两种
//         {
//             if (risks[i] + risks[j] <= risk)
//             {
//                 int puti;
//                 int putj;
//                 if (profit[i] >= profit[j])
//                 {
//                     puti = min(money, put[i]);
//                     putj = min(money - puti, put[j]);
//                 }
//                 else
//                 {
//                     putj = min(money, put[j]);
//                     puti = min(money - putj, put[i]);
//                 }
//                 if (puti * profit[i] + putj * profit[j] > max_profit)
//                 {
//                     max_profit = puti * profit[i] + putj * profit[j];
//                     tag[0][0] = i;
//                     tag[0][1] = puti;
//                     tag[1][0] = j;
//                     tag[1][1] = putj;
//                 }
//             }
//         }
//     }
//     for (int i = 0; i < product; i++)
//     {
//         if (i == tag[0][0])
//         {
//             cout << tag[0][1] << ' ';
//         }
//         else if (i == tag[1][0])
//         {
//             cout << tag[1][1] << ' ';
//         }
//         else
//         {
//             cout << 0 << ' ';
//         }
//     }
//     cout << endl;
//     return 0;
// }

// 14.游戏分组
// int main()
// {
//     vector<int> rank;
//     int sum = 0;
//     int num;
//     while (cin >> num)
//     {
//         rank.push_back(num);
//         sum += num;
//         if (getchar() == '\n')
//         {
//             break;
//         }
//     }
//     vector<int> dp(sum / 2 + 1, 0);
//     for (int j = sum / 2; j >= rank[0]; j--)
//     {
//         dp[j] = rank[0];
//     }
//     for (int i = 0; i < rank.size(); i++)
//     {
//         for (int j = sum / 2; j >= rank[i]; j--)
//         {
//             dp[j] = max(dp[j], dp[j - rank[i]] + rank[i]);
//         }
//     }
//     cout << abs(sum - 2 * dp[sum / 2]) << endl;
//     return 0;
// }

// 15.围棋的气
// int main()
// {
//     vector<vector<int>> chess(19, vector<int>(19, 0));
//     vector<int> black;
//     vector<int> white;
//     int num;
//     while (cin >> num)
//     {
//         black.push_back(num);
//         if (getchar() == '\n')
//         {
//             break;
//         }
//     }
//     while (cin >> num)
//     {
//         white.push_back(num);
//         if (getchar() == '\n')
//         {
//             break;
//         }
//     }
//     for (int i = 0; i < black.size(); i += 2)
//     {
//         int x = black[i];
//         int y = black[i + 1];
//         chess[x][y] = 1;
//     }
//     for (int i = 0; i < white.size(); i += 2)
//     {
//         int x = white[i];
//         int y = white[i + 1];
//         chess[x][y] = 2;
//     }
//     int dir[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
//     // vector<vector<bool>> visited(19, vector<bool>(19, false));
//     int bqi = 0;
//     int wqi = 0;
//     int temp1 = 0, temp2 = 0;
//     for (int i = 0; i < 19; i++)
//     {
//         for (int j = 0; j < 19; j++)
//         {
//             if (chess[i][j] != 1 && chess[i][j] != 2)
//             {
//                 for (int k = 0; k < 4; k++)
//                 {
//                     int nextx = i + dir[k][0];
//                     int nexty = j + dir[k][1];
//                     if (nextx < 0 || nexty < 0 || nextx >= 19 || nexty >= 19)
//                         continue;
//                     if (chess[nextx][nexty] == 1)
//                         temp1 = 1;
//                     if (chess[nextx][nexty] == 2)
//                         temp2 = 1;
//                 }
//                 if (temp1 == 1)
//                     bqi++;
//                 if (temp2 == 1)
//                     wqi++;
//                 temp1 = 0;
//                 temp2 = 0;
//             }
//         }
//     }
//     cout << bqi << ' ' << wqi << endl;
//     return 0;
// }

// 16.掌握的单词个数
// int main()
// {
//     int n;
//     cin >> n;
//     string str;
//     vector<string> words;
//     while (n--)
//     {
//         cin >> str;
//         words.push_back(str);
//     }
//     string chars;
//     cin >> chars;
//     unordered_map<char, int> c_map;
//     for (char c : chars)
//     {
//         c_map[c]++;
//     }
//     unordered_map<char, int> w_map;
//     int ans = 0;
//     for (string word : words)
//     {
//         int temp = 0;
//         int valid = 0;
//         for (char w : word)
//         {
//             w_map[w]++;
//         }
//         for (auto it : w_map)
//         {
//             if (c_map.count(it.first))
//             {
//                 if (c_map[it.first] >= it.second)
//                 {
//                     valid++;
//                 }
//                 else
//                 {
//                     temp += c_map[it.first] - it.second;
//                 }
//             }
//             else
//             {
//                 temp += it.second;
//             }
//         }
//         if (w_map.size() == valid)
//         {
//             ans++;
//         }
//         else
//         {
//             if (temp <= c_map['?'])
//             {
//                 ans++;
//             }
//         }
//         w_map.clear();
//     }
//     cout << ans << endl;
//     return 0;
// }

// 17.小明找位置
// int main()
// {
//     int n;
//     vector<int> nums;
//     while (cin >> n)
//     {
//         nums.push_back(n);
//         if (getchar() == '\n')
//         {
//             break;
//         }
//     }
//     cout << "nums_size: " << nums.size() << endl;
//     int target;
//     cin >> target;
//     int l = 0;
//     int r = nums.size() - 1;
//     int ans = 0;
//     while (l <= r)
//     {
//         int mid = l + (r - l) / 2;
//         if (target > nums[mid])
//         {
//             l = mid + 1;
//             ans = mid;
//         }
//         if (target < nums[mid])
//         {
//             r = mid - 1;
//         }
//     }
//     cout << ans + 2 << endl;
//     return 0;
// }

// 18.分割均衡字符串
// int main()
// {
//     string str;
//     cin >> str;
//     int ans = 0;
//     int x = 0, y = 0;
//     for (int r = 0; r < str.size(); r++)
//     {
//         if (str[r] == 'X')
//             x++;
//         else
//             y++;
//         if (x == y)
//         {
//             ans++;
//             x = 0;
//             y = 0;
//         }
//     }
//     cout << ans << endl;
//     return 0;
// }

// 19.小华地图寻宝
