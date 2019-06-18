/*
	@author c
	@date 2019.6.17
	生成所需要的两个 first 数组
	主要处理 firstP、firstN
*/
#include "common_header.h"
using namespace std;
//产生式存放数组（不含公共左因子、不含左递归）
extern string grammar[maxnum];
extern int lines;
//所有的非终结符
extern vector<char> nonT;
//每一个产生式的 first 集合，注意 '$' '@'
extern vector<char> firstP[maxnum];
//每一个非终结符的 first 集合，注意 '$' '@'
extern vector<char> firstN[maxnum];
//单个 非终结符 的 first 集
void getfirst(char NonTer)
{
	int index_NonTer = indexOfNonT(NonTer);
	for (int j = 0;j < lines;j++) //遍历产生式 
	{
		if (grammar[j][0] != NonTer)
			continue;
		bool keep = true;// 是否继续向后检查
		for (char c : grammar[j].substr(3)) {
			if (!keep)
				break;
			if (typeOf(c) == Terminator) {
				add_unique_item(firstN[index_NonTer], c);
				keep = false;
			}
			else { // 非终结符
				//把这个非终结符的 first 收了
				keep = false;
				getfirst(c); // 收之前先递归求解一下
				for (char b : firstN[indexOfNonT(c)]) {
					if (b == '@')
						keep = true;
					else
						add_unique_item(firstN[index_NonTer], b);
				}
			}
		}
		// 如果最后 keep 仍为 true, 则说明 右部可空
		if (keep)
			add_unique_item(firstN[index_NonTer], '@');
	}
}
//求解所有终结符的first集 
void getFirstN()
{
	for_each(nonT.begin(), nonT.end(), getfirst);
}
//求解所有产生式右部的first集 
void getFirstP()
{
	for (int i = 0;i < lines;i++) {
		bool keep = true; // 是否继续向后检查
		for (char c : grammar[i].substr(3)) {
			if (!keep)
				break;
			if (typeOf(c) == Terminator) {
				add_unique_item(firstP[i], c);
				keep = false;
			}
			else { // 非终结符
				//把这个非终结符的 first 收了
				keep = false;
				for (char b : firstN[indexOfNonT(c)]) {
					if (b == '@')
						keep = true;
					else
						add_unique_item(firstP[i], b);
				}
			}
		}
		// 如果最后 keep 仍为 true, 则说明 产生式 右部可空
		if(keep)
			add_unique_item(firstP[i], '@');
	}
}