#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

// 四数之和
// int main()
// {
//     int n;
//     vector<int> num;
//     while (cin >> n)
//     {
//         num.push_back(n);
//         if (getchar() == '\n')
//         {
//             break;
//         }
//     }
//     int target;
//     cin >> target;
//     if (num.size() < 4)
//     {
//         cout << "no answer!" << endl;
//         return -1;
//     }
//     vector<vector<int>> res;
//     sort(num.begin(), num.end());
//     for (int i = 0; i < num.size(); i++)
//     {
//         if (i != 0 && (num[i] == num[i - 1]))
//             i++;
//         for (int j = i + 1; j < num.size(); j++)
//         {
//             if (j != i + 1 && (num[j] == num[j - 1]))
//                 j++;
//             int l = j + 1;
//             int r = num.size() - 1;
//             while (l < r)
//             {
//                 int temp = num[i] + num[j] + num[l] + num[r];
//                 if (temp < target)
//                 {
//                     l++;
//                     if (num[l] == num[l - 1])
//                         l++;
//                 }
//                 else if (temp > target)
//                 {
//                     r--;
//                     if (num[r] == num[r + 1])
//                         r--;
//                 }
//                 else
//                 {
//                     res.push_back({num[i], num[j], num[l], num[r]});
//                     l++;
//                     r--;
//                     while (l < r && (num[l] == num[l - 1]))
//                         l++;
//                     while (l < r && (num[r] == num[r + 1]))
//                         r--;
//                 }
//             }
//         }
//     }
//     for (auto p : res)
//     {
//         for (auto pp : p)
//         {
//             cout << pp << ' ';
//         }
//         cout << endl;
//     }
//     cout << endl;
//     return 0;
// }

// 重复的子字符串
// int main()
// {
//     string s;
//     cin >> s;
//     string t = s + s;
//     t = t.substr(1, t.size() - 2);
//     if (t.find(s) != -1)
//     {
//         cout << "true" << endl;
//         return 0;
//     }
//     else
//     {
//         cout << "false" << endl;
//         return 0;
//     }
// }

// 最后一个单词的长度
// int main()
// {
//     string s;
//     getline(cin, s);
//     int i = s.size() - 1;
//     while (s[i] == ' ')
//     {
//         i--;
//     }
//     int j = i;
//     while (s[j] != ' ' && j >= 0)
//     {
//         j--;
//     }
//     cout << i - j << endl;
//     return 0;
// }

// 反转字符串中单词的顺序但不反转每个单词

// 方法1:新开数组存单词，再反向输出
// int main()
// {
//     string temp;
//     vector<string> res;
//     string s;
//     getline(cin, s);
//     for (char c : s)
//     {
//         if (c == ' ')
//         {
//             if (!temp.empty())
//             {
//                 res.push_back(temp);
//                 temp.clear();
//             }
//         }
//         else
//         {
//             temp += c;
//         }
//     }
//     for (int i = res.size() - 1; i >= 0; i--)
//     {
//         cout << res[i] << ' ';
//     }
//     cout << endl;
//     return 0;
// }

// 方法2:不新开数组，去掉字符串所有不应该存在的空格，反转整个字符串，再反转里面的单词
// 反转字符串其实库函数里有，reverse(s.begin(), s.end())，但是还是手动实现一下
// void myReverse(string &s, int start, int end)
// {
//     for (int i = start, j = end; i < j; i++, j--)
//     {
//         swap(s[i], s[j]);
//     }
// }
// // 双指针法去除字符串所有不合法空格，包括首尾的
// void outempty(string &s)
// {
//     int l = 0;
//     for (int r = 0; r < s.size(); r++)
//     {
//         if (s[r] != ' ')
//         {
//             if (l != 0)
//                 s[l++] = ' ';
//             while (r < s.size() && s[r] != ' ')
//             {
//                 s[l++] = s[r++];
//             }
//         }
//     }
//     s.resize(l);
// }
// int main()
// {
//     string s;
//     getline(cin, s);
//     int i = 0;
//     outempty(s);
//     myReverse(s, 0, s.size() - 1);
//     for (int l = 0, r = 0; r <= s.size(); r++)
//     {
//         if (s[r] == ' ' || r == s.size())
//         {
//             myReverse(s, l, r - 1);
//             l = r + 1;
//         }
//     }
//     cout << s << endl;
//     return 0;
// }

// 右旋字符串
// 能新开空间就用两个子字符串重新拼接
// 不能就整体反转，再将前K和后K分别反转
// int main()
// {
//     string s;
//     cin >> s;
//     int k;
//     cin >> k;
//     reverse(s.begin(), s.end());
//     reverse(s.begin(), s.begin() + k); //reverse函数翻转区间是左闭右开的
//     reverse(s.begin() + k, s.end());
//     cout << s << endl;
//     return 0;
// }
