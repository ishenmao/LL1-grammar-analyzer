/*
@author w
@date 2019.6.18
打印一些东西
*/
#include "common_header.h"
using namespace std;

//产生式存放数组（不含公共左因子、不含左递归）
extern string grammar[maxnum];
//开始符号, 默认第一个文法的第一个字母为开始符号
extern char start_char;
extern int cnt_nonT;
extern int cnt_term;
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
//二维数组，预测分析表，存放产生式数组下标，没有的地方设置为 -1
extern int table[maxnum][maxnum];
//打印所有终结符
void printAllTerminator() {
	cout << "终结符数量  ：" << cnt_term << " 分别为:{";
	for (char c : term) {
		cout << " " << c;
	}
	cout << " }" << endl;
}
//打印所有非终结符
void printAllNonTerminator() {
	cout << "非终结符数量：" << cnt_nonT << " 分别为:{";
	for (char c : nonT) {
		cout << " " << c;
	}
	cout << " }" << endl;
}
//打印所有 firstN
void printAllFirstN() {
	cout << "所有非终结符的 FIRST 集：" << endl;
	for (int i = 0;i < cnt_nonT;i++) {
		cout << "FIRST(" << nonT[i] << ") = {";
		for (char fi : firstN[i]) {
			cout << " " << fi;
		}
		cout << " }" << endl;
	}
	cout << endl;
}
//打印所有 firstP
void printAllFirstP() {
	cout << "所有产生式右部的 FIRST 集：" << endl;
	for (int i = 0;i < lines;i++) {
		cout << "FIRST(" << grammar[i].substr(3) << ") = {";
		for (char fi : firstP[i]) {
			cout << " " << fi;
		}
		cout << " }" << endl;
	}
	cout << endl;
}
//打印所有 follow
void printAllFollow() {
	cout << "所有非终结符的 FOLLOW 集：" << endl;
	for (int i = 0;i < cnt_nonT;i++) {
		cout << "FOLLOW(" << nonT[i] << ") = {";
		for (char fi : follow[i]) {
			cout << " " << fi;
		}
		cout << " }" << endl;
	}
	cout << endl;
}
//打印 预测分析表
void printTable() {
	int output_width = 10;
	cout << "预测分析表：" << endl;
	cout << setw(output_width) << " ";
	for (char char_term : term) {
		if (char_term == '@')
			continue;
		cout << setw(output_width) << char_term;
	}
	cout << endl;
	for (int i = 0;i < cnt_nonT;i++) {
		cout << setw(output_width) << nonT[i];
		for (int j = 0;j < cnt_term;j++) {
			if (term[j] == '@')
				continue;
			if(table[i][j] == -1)
				cout << setw(output_width) << " ";
			else
				cout << setw(output_width) << grammar[table[i][j]];
		}
		cout << endl;
	}
}



