/*--------------------------------------------------------------------------------------------------|
给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起	|
始位置。																							|
																									|
注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。		|
 																									|
																									|
示例 1：																							|
																									|
输入：																								|
  s = "barfoothefoobarman",																			|
  words = ["foo","bar"]																				|
输出：[0,9]																							|
解释：																								|
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。												|
输出的顺序不重要, [9,0] 也是有效答案。																|
示例 2：																							|
																									|
输入：																								|
  s = "wordgoodgoodgoodbestword",																	|
  words = ["word","good","best","word"]																|
输出：[]																							|
																									|
来源：力扣（LeetCode）																				|
链接：https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words					|
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。								|
---------------------------------------------------------------------------------------------------*/

/*
*
*	执行用时：76 ms, 在所有 C++ 提交中击败了75.19%的用户
*	内存消耗：22.9 MB, 在所有 C++ 提交中击败了38.95%的用户
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<int> findSubstring(string s, vector<string>& words)
{
	if (words.size() == 0)
	{
		return {};
	}
	int sLen = s.size();
	int wlen = words[0].size();
	int wLen = words.size() * wlen;
	if (sLen < wLen)
	{
		return {};
	}
	vector<int> res;

	unordered_map<string, int> wMap, sMap;

	for (string word : words)
	{
		wMap[word]++;
	}

	for (int k = 0; k < wlen; k++)
	{
		int head = k, now = k;
		while (head < sLen - wLen + 1)
		{
			while (now < head + wLen)
			{
				string now_word = s.substr(now, wlen);
				sMap[now_word]++;
				now += wlen;

				if (wMap[now_word] == 0)
				{
					head = now;
					sMap.clear();
					break;
				}
				else if (sMap[now_word] > wMap[now_word])
				{
					while (sMap[now_word] > wMap[now_word])
					{
						sMap[s.substr(head, wlen)]--;
						head += wlen;
					}
					break;
				}
			}
			if (now == head + wLen)
			{
				res.push_back(head);
				sMap[s.substr(head, wlen)]--;
				head += wlen;
			}
		}
		sMap.clear();
	}
	return res;
}

int main()
{
	string s = "wordgoodgoodgoodbestword";
	vector<string> words = { "word","good","best","word" };
}