
/*
@author w
@date 2019.6.17
公共头文件
声明一些公用全局变量 和 函数
*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <set>
#include <cassert>
#include <iomanip>
#include <ctime>
#include <list>
#include <cctype>
#include <functional>
#define maxnum 50
#define Terminator 1
#define NonTerminator 0
// 表格宽度
#define Table_width 20
using namespace std;

//查询 字符 x 在 nonT 中下标
int indexOfNonT(char x);

//查询 字符 x 在 term 中下标
int indexOfTerm(char x);

//查询 字符 x 在某个 vector<char> 中的下标，没有则返回 -1
//要求 vector<char> 中没有重复的元素
int indexOf(const vector<char>& v, char x);

// 向vector中添加元素，如果已经存在则不添加
void add_unique_item(vector<char>& f, char c);

//查询 字符 x 是终结符还是非终结符
//返回值： 1 表示终结符，0 表示非终结符，-1表示出错了，哪个都不是
int typeOf(char x);

// 分析函数
// 如果成功分析，输出 分析动作
void analyze(const char* str, int len = -1);
//输入文法
void input_grammer();
// 提取非终结符 和 终结符, 保存到 nonT 和 term 中
void pick_up();
//firstN()非终结符的first
void getFirstN();
//firstP()产生式的first
void getFirstP();
//求解follow
void getFollow();
//生成预测分析表
void generateTable();


// 打印
void printAllTerminator();
void printAllNonTerminator();
void printAllFirstN();
void printAllFirstP();
void printAllFollow();
void printTable();

