# LL1-grammar-analyzer
编译原理课程设计，LL(1)文法分析器

## 1、设计目的：
设计并编写一个根据文法自动生成LL(1)分析器的程序，理解文法回溯等现象在LL分析中的不良影响，掌握FIRST集、FOLLOW集的定义和计算方法，掌握LL（1）分析器的工作原理和实现方法。
## 2、基本要求
- 根据输入的文件名，打开并读取文件中存放的文法信息。
- 计算每个非终结符的FIRST集合FOLLOW集。
- 输出文法对应的预测分析表
- 输入一个字符串。输出根据预测分析表分析该字符串的过程。
## 3、使用
直接导入源文件到项目中，编译运行即可，建议在 Visual Studio 中运行，需支持 C++11。

## 4、注意事项
- 输入文法必须是 LL(1) 文法，即：不能含有左递归，同一非终结符的产生式的选项的First集合相交必须为空。
- 没有词法分析部分，只能是简单文法，即：非终结符和终结符都只能是单个ascii字符
## 5、特殊说明
- 使用`@`符号作为空串符号，`$`符号作为句子末尾符号
- 开始文法符号设为输入文法中的第一个产生式的第一个字母
## 6、LL(1)文法测试用例
```cpp
1、声明语句的简化文法：
D->TL
T->i
T->r
L->dR
R->,dR
R->@

此文法合法串举例：
id
id,d,d
rd
rd,d

2、含加法、乘法的表达式的简化文法
E->TA
A->+TA
A->@
T->FB
B->*FB
B->@
F->(E)
F->d

此文法合法串举例：
d
d+d
d+d*d
(d+d)*(d+d)
(((d)))

3、识别a、b个数相等的字符串
S->aBS
S->bAS
S->@
A->a
A->bAA
B->b
B->aBB

此文法合法串举例：
$
ba
ab
abab
baab
abaababbba
bbbbbaaaaa

4、识别中间字母为c，两边为对称的ab串
S->aSa
S->bSb
S->c

此文法合法串举例：
c
aca
bcb
abbbcbbba
aababbcbbabaa

5、识别两端为个数相等的a、d，中间为个数相等的b、c，且a，b，c，d的个数均大于等于1的字符串
S->aB
B->Sd
B->Ad
A->bC
C->Ac
C->c

此文法合法串举例：
abcd
aabcdd
aabbbbccccdd
```
## 7、测试（使用上述第二个文法）
```cpp
请输入文法，每行一个，在行首按 Ctrl+Z 结束。第一个文法的首字符将被视为开始符号
E->TA
A->+TA
A->@
T->FB
B->*FB
B->@
F->(E)
F->d
^Z
终结符数量  ：7 分别为:{ + @ * ( ) d $ }
非终结符数量：5 分别为:{ E A T B F }
所有非终结符的 FIRST 集：
FIRST(E) = { ( d }
FIRST(A) = { + @ }
FIRST(T) = { ( d }
FIRST(B) = { * @ }
FIRST(F) = { ( d }

所有产生式右部的 FIRST 集：
FIRST(TA) = { ( d }
FIRST(+TA) = { + }
FIRST(@) = { @ }
FIRST(FB) = { ( d }
FIRST(*FB) = { * }
FIRST(@) = { @ }
FIRST((E)) = { ( }
FIRST(d) = { d }

所有非终结符的 FOLLOW 集：
FOLLOW(E) = { $ ) }
FOLLOW(A) = { $ ) }
FOLLOW(T) = { + $ ) }
FOLLOW(B) = { + $ ) }
FOLLOW(F) = { * + $ ) }

预测分析表：
                   +         *         (         )         d         $
         E                         E->TA               E->TA
         A    A->+TA                          A->@                A->@
         T                         T->FB               T->FB
         B      B->@    B->*FB                B->@                B->@
         F                        F->(E)                F->d
---句子测试---
请输入一个句子：（中间不含空格，回车结束, 退出请输入 quit）
d
                  栈                输入                动作
                  $E                  d$                初始
                 $AT                  d$               E->TA
                $ABF                  d$               T->FB
                $ABd                  d$                F->d
                 $AB                   $              匹配 d
                  $A                   $                B->@
                   $                   $                A->@
                   $                   $                接受
分析成功！
请输入一个句子：（中间不含空格，回车结束, 退出请输入 quit）
d+d
                  栈                输入                动作
                  $E                d+d$                初始
                 $AT                d+d$               E->TA
                $ABF                d+d$               T->FB
                $ABd                d+d$                F->d
                 $AB                 +d$              匹配 d
                  $A                 +d$                B->@
                $AT+                 +d$              A->+TA
                 $AT                  d$              匹配 +
                $ABF                  d$               T->FB
                $ABd                  d$                F->d
                 $AB                   $              匹配 d
                  $A                   $                B->@
                   $                   $                A->@
                   $                   $                接受
分析成功！
请输入一个句子：（中间不含空格，回车结束, 退出请输入 quit）
d+d*d
                  栈                输入                动作
                  $E              d+d*d$                初始
                 $AT              d+d*d$               E->TA
                $ABF              d+d*d$               T->FB
                $ABd              d+d*d$                F->d
                 $AB               +d*d$              匹配 d
                  $A               +d*d$                B->@
                $AT+               +d*d$              A->+TA
                 $AT                d*d$              匹配 +
                $ABF                d*d$               T->FB
                $ABd                d*d$                F->d
                 $AB                 *d$              匹配 d
               $ABF*                 *d$              B->*FB
                $ABF                  d$              匹配 *
                $ABd                  d$                F->d
                 $AB                   $              匹配 d
                  $A                   $                B->@
                   $                   $                A->@
                   $                   $                接受
分析成功！
请输入一个句子：（中间不含空格，回车结束, 退出请输入 quit）
d*d*d*d
                  栈                输入                动作
                  $E            d*d*d*d$                初始
                 $AT            d*d*d*d$               E->TA
                $ABF            d*d*d*d$               T->FB
                $ABd            d*d*d*d$                F->d
                 $AB             *d*d*d$              匹配 d
               $ABF*             *d*d*d$              B->*FB
                $ABF              d*d*d$              匹配 *
                $ABd              d*d*d$                F->d
                 $AB               *d*d$              匹配 d
               $ABF*               *d*d$              B->*FB
                $ABF                d*d$              匹配 *
                $ABd                d*d$                F->d
                 $AB                 *d$              匹配 d
               $ABF*                 *d$              B->*FB
                $ABF                  d$              匹配 *
                $ABd                  d$                F->d
                 $AB                   $              匹配 d
                  $A                   $                B->@
                   $                   $                A->@
                   $                   $                接受
分析成功！
请输入一个句子：（中间不含空格，回车结束, 退出请输入 quit）
(d+d)*d
                  栈                输入                动作
                  $E            (d+d)*d$                初始
                 $AT            (d+d)*d$               E->TA
                $ABF            (d+d)*d$               T->FB
              $AB)E(            (d+d)*d$              F->(E)
               $AB)E             d+d)*d$              匹配 (
              $AB)AT             d+d)*d$               E->TA
             $AB)ABF             d+d)*d$               T->FB
             $AB)ABd             d+d)*d$                F->d
              $AB)AB              +d)*d$              匹配 d
               $AB)A              +d)*d$                B->@
             $AB)AT+              +d)*d$              A->+TA
              $AB)AT               d)*d$              匹配 +
             $AB)ABF               d)*d$               T->FB
             $AB)ABd               d)*d$                F->d
              $AB)AB                )*d$              匹配 d
               $AB)A                )*d$                B->@
                $AB)                )*d$                A->@
                 $AB                 *d$              匹配 )
               $ABF*                 *d$              B->*FB
                $ABF                  d$              匹配 *
                $ABd                  d$                F->d
                 $AB                   $              匹配 d
                  $A                   $                B->@
                   $                   $                A->@
                   $                   $                接受
分析成功！
请输入一个句子：（中间不含空格，回车结束, 退出请输入 quit）
quit
```

