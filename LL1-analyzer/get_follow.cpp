/*
@author g
@date 2019.6.17
生成所需要的 follow 数组
主要处理 follow
*/
#include "common_header.h"
using namespace std;
//产生式存放数组（不含公共左因子、不含左递归）
extern string grammar[maxnum];
//开始符号, 默认第一个文法的第一个字母为开始符号
extern char start_char;
extern int cnt_nonT;
extern int lines;
//所有的非终结符
extern vector<char> nonT;
//所有的终结符
extern vector<char> term;
//每一个产生式的 first 集合，注意 '$' '@'
extern vector<char> firstP[maxnum];
//每一个非终结符的 first 集合，注意 '$' '@'
extern vector<char> firstN[maxnum];
//每一个非终结符的 follow 集合，注意 '$' '@'
extern vector<char> follow[maxnum];

typedef pair<int, int> Pair2;
vector<Pair2> to_do;
//以下仅get_follow.cpp中使用
vector<char> firstbeta(int i, int pos)
{
	vector<char> res;
	bool keep = true; // 是否继续向后检查
	for (char c : grammar[i].substr(pos)) {
		if (!keep)
			break;
		if (typeOf(c) == Terminator) {
			add_unique_item(res, c);
			keep = false;
		}
		else { // 非终结符
			   //把这个非终结符的 first 收了
			keep = false;
			for (char b : firstN[indexOfNonT(c)]) {
				if (b == '@')
					keep = true;
				else
					add_unique_item(res, b);
			}
		}
	}
	// 如果最后 keep 仍为 true, 则说明 产生式 右部可空
	if (keep)
		add_unique_item(res, '@');
	return res;
}
//求单个元素的 FOLLOW 集
void singleFollow(char ch, vector<char> &inner_follow)
{
	int index_ch = indexOfNonT(ch);
	for (int k = 0;k < lines;k++) {
		string& cur_grammar = grammar[k];
		int index_head = indexOfNonT(cur_grammar[0]);
		int len = cur_grammar.length();
		for (int i = 3; i < len; i++)//次数为当前产生式右侧元素长度
		{
			if (cur_grammar[i] != ch)
				continue;
			auto next_follow = firstbeta(k, i + 1);
			bool hasat = false;
			for (auto d : next_follow) {
				if (d == '@') 
					hasat = true;
				else 
					add_unique_item(inner_follow, d);
			}
			if (hasat && index_head != index_ch)
				to_do.push_back(make_pair(index_head, index_ch));
		}
	}
}
//求解 follow
int old_follow_size[maxnum];
bool isSameSize() {
	for (int i = 0;i < cnt_nonT;i++) {
		if (old_follow_size[i] != follow[i].size())
			return false;
	}
	return true;
}
void copy_from_to(vector<char>& from, vector<char>& to) {
	for (char c : from) {
		add_unique_item(to, c);
	}
}
void getFollow()
{
	follow[indexOfNonT(start_char)].push_back('$');
	to_do.clear();
	for (int i = 0;i < cnt_nonT;i++) {
		singleFollow(nonT[i], follow[i]);
	}
	do {
		for (int i = 0;i < cnt_nonT;i++) {
			old_follow_size[i] = follow[i].size();
		}
		for (auto p : to_do) {
			copy_from_to(follow[p.first], follow[p.second]);
		}
	} while (!isSameSize()); //只要不一致，就重复
}