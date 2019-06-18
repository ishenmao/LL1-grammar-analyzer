/*
@author w
@date 2019.6.17
生成所需要的预测分析表, 处理 table
*/
#include "common_header.h"
using namespace std;

//产生式存放数组（不含公共左因子、不含左递归）
extern string grammar[maxnum];
//产生式个数
extern int lines;
//每一个产生式的 first 集合，注意 '$' '@'
extern vector<char> firstP[maxnum];

//每一个非终结符的 follow 集合，注意 '$'
extern vector<char> follow[maxnum];

//二维数组，预测分析表，存放产生式数组下标，没有的地方设置为 -1
extern int table[maxnum][maxnum];

//生成预测分析表
void generateTable() {
	memset(table, -1, sizeof table);
	for (int k = 0; k < lines;k++) {
		bool hasEmpty = false; // 标记 firstP[k] 中是否 含有 '@'
		int i = indexOfNonT(grammar[k][0]); // 第 k 个产生式的 开头非终结符 在 nonT 中下标
		for (char c : firstP[k]) {
			if (c == '@') { // 分析表中不用添加 @ 这一列，因为用不到
				hasEmpty = true;
			}
			else {
				int j = indexOfTerm(c);
				table[i][j] = k; // 将产生式 在 grammar 中的下标 填入分析表中
			}
		}
		// 如果有 “空”，那么还要 加入 follow[i] 中的每个终结符
		if (hasEmpty) {
			for (char c : follow[i]) { // 注：follow 中不可能含有 '@'
				int j = indexOfTerm(c);
				table[i][j] = k; // 将产生式 在 grammar 中的下标 填入分析表中
			}
		}
	}
}

