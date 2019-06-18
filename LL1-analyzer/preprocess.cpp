/*
	@author w
	@date 2019.6.17
	预处理：文法输入函数，提取非终结符 和 终结符
	主要处理 grammar，nonT，term，cnt_nonT, cnt_term, lines
*/
#include "common_header.h"
using namespace std;
//产生式存放数组（不含公共左因子、不含左递归）
extern string grammar[maxnum];
//开始符号, 默认第一个文法的第一个字母为开始符号
extern char start_char; 
//非终结符 与 终结符 的数量, 产生式个数
extern int cnt_nonT;
extern int cnt_term;
extern int lines; 
//所有的非终结符
extern vector<char> nonT;
//所有的终结符
extern vector<char> term;

//直接从标准输入读取 文法
//格式类似下面，每个文法内部没有空格 
/**
A->aBc
A->d+
B->cA
B->@
*/
void input_grammer() {
	lines = 0;
	while (cin >> grammar[lines])
		lines++;
	cin.clear();
}
// 提取非终结符 和 终结符, 保存到 nonT 和 term 中
void pick_up() {
	bool vis[256] = {0};
	for (int i = 0;i < lines;i++) {
		char cur = grammar[i][0];
		if (!vis[(int)cur]) {
			nonT.push_back(cur);
			vis[(int)cur] = true;
		}
	}
	// 不是非终结符的都是终结符
	for (int i = 0;i < lines;i++) {
		int n = grammar[i].length();
		for (int j = 3;j < n;j++) {
			char cur = grammar[i][j];
			if (!vis[(int)cur]) {
				term.push_back(cur);
				vis[(int)cur] = true;
			}
		}
	}
	term.push_back('$');
	cnt_nonT = nonT.size();
	cnt_term = term.size();
	start_char = grammar[0][0];
}