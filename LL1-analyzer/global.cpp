/*
	@author w
	@date 2019.6.17
	公用 全局变量的 定义
	公用 全局函数的 定义
*/
#include "common_header.h"
using namespace std;

//产生式存放数组（不含公共左因子、不含左递归）
string grammar[maxnum];
//开始符号, 默认第一个文法的第一个字母为开始符号
char start_char;
//非终结符 与 终结符 的数量, 产生式数量
int cnt_nonT = 0;
int cnt_term = 0;
int lines = 0;
//所有的非终结符
vector<char> nonT;
//所有的终结符
vector<char> term;
//每一个产生式的 first 集合，注意 '$' '@',first 不含 $, follow 不含 @
vector<char> firstP[maxnum];
//每一个非终结符的 first 集合
vector<char> firstN[maxnum];
//每一个非终结符的 follow 集合
vector<char> follow[maxnum];
//二维数组，预测分析表，存放产生式数组下标，没有的地方设置为 -1
int table[maxnum][maxnum];

//查询 字符 x 在某个 vector<char> 中的下标，没有则返回 -1
//要求 vector<char> 中没有重复的元素
int indexOf(const vector<char>& v, char x) {
	vector<char>::const_iterator it = find(v.begin(), v.end(), x);
	return it == v.end() ? -1 : it - v.begin();
}
// 向vector中添加元素，如果已经存在则不添加
void add_unique_item(vector<char>& v, char c) {
	if (indexOf(v, c) == -1)
		v.push_back(c);
}

//查询 字符 x 是终结符还是非终结符
//返回值： 1 表示终结符，0 表示非终结符，-1表示出错了，哪个都不是
int typeOf(char x) {
	if (indexOf(nonT, x) != -1)
		return NonTerminator;
	if (indexOf(term, x) != -1)
		return Terminator;
	return -1;
}

//查询 字符 x 在 nonT 中下标
int indexOfNonT(char x) {
	return indexOf(nonT, x);
}
//查询 字符 x 在 term 中下标
int indexOfTerm(char x) {
	return indexOf(term, x);
}



