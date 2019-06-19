/*
	@author w
	@date 2019.6.17
	分析函数，用来检测分析表 和 验证文法句子
	@date 2019.6.19
	修正打印bug
*/
#include "common_header.h"
using namespace std;

//文法数组
extern string grammar[maxnum];
//二维数组，预测分析表，存放产生式数组下标，没有的地方设置为 -1
extern int table[maxnum][maxnum];
//开始符号
extern char start_char;
//打印当前状态
void printCurrentStatus(const char* s1, const char* s2, const string& s3) {
	cout << setw(Table_width) << s1 << setw(Table_width) << s2 << setw(Table_width) << s3 << endl;
}
// 分析函数
// 如果成功分析，输出 分析动作
void analyze(const char* sentence, int len) {
	char str[300];
	strcpy(str, sentence);
	if (len == -1)
		len = strlen(str);
	str[len++] = '$'; // 在末尾加入 '$'
	str[len] = 0;
	char stk[200]; //数组模拟栈
	int pos = 0;
	// 向栈中加入'$'和开始符号
	stk[pos++] = '$';
	stk[pos++] = start_char;
	cout << setw(Table_width) << "栈" << setw(Table_width) << "输入" << setw(Table_width) << "动作" << endl;
	//打印 当前栈中内容 + 剩余输入 + 分析动作
	stk[pos] = 0;
	printCurrentStatus(stk, str, string("初始"));
	for (int i = 0;i < len;) {
		char top = stk[--pos];
		stk[pos] = 0;
		if (top == '$') {
			if (str[i] == '$') {
				printCurrentStatus("$", "$", string("接受"));
				cout << "分析成功！" << endl;
				break;
			}
			else {
				//打印 当前栈中内容 + 剩余输入 + 分析动作
				printCurrentStatus(stk, str + i, string("错误！"));
				cerr << "分析栈栈顶为'$'，但是输入尚未结束。" << endl;
				return;
			}
		}
		// 如果栈顶不是 '$'
		int current_type = typeOf(top);
		if (current_type == Terminator) {
			if (top == str[i]) {
				i++; //输入字符提取走
				string res("匹配 ");
				//打印 当前栈中内容 + 剩余输入 + 分析动作
				printCurrentStatus(stk, str + i, res + top);
			}
			else {
				//打印 当前栈中内容 + 剩余输入 + 分析动作
				printCurrentStatus(stk, str + i, string("错误！"));
				cerr << "分析栈栈顶为终结符 '" << top << "'，但是输入符号为 '" << str[i] << "'" << endl;
				return;
			}
		}
		else if (current_type == NonTerminator) {
			int g_index = table[indexOfNonT(top)][indexOfTerm(str[i])];
			if (g_index != -1) {
				if (grammar[g_index][3] != '@') { // 如果右边 是 @，那么不向栈中增加东西
					// 将产生式中右部内容 倒序 入栈
					for (int i = grammar[g_index].size() - 1; i >= 3;i--) {
						stk[pos++] = grammar[g_index][i];
					}
					stk[pos] = 0;
				}
				//打印 当前栈中内容 + 剩余输入 + 分析动作
				printCurrentStatus(stk, str + i, grammar[g_index]);
			}
			else {
				//打印 当前栈中内容 + 剩余输入 + 分析动作
				printCurrentStatus(stk, str + i, string("错误！"));
				cerr << "分析表 table[" << top << "][" << str[i] << "] 项为空。" << endl;
				return;
			}
		}
		else {
			cerr << "解析错误！" << endl;
			return;
		}
	}

}
