/*

**** 程序名：词法分析-文件读取单词 
**** 时间：2020年10月13日
**** 作者：朱领

**** 程序思路
		1.数据清洗
		2.提取单词判断是否保留
		3.输出结果 

**** 变量含义：
		1.int aa;fseek的时候用来接着的
		2.string  word = "";
		3.string  reserved_word[20];//保留
	 	4.char buffer;//每次读进来的一个字符
		5.int num = 0;//每个单词中当前字符的位置
		6.int line = 1; //行数
		7.int row = 1; //列数，就是每行的第几个
		8.bool flag; //文件是否结束了
		9.int flag2;//单词的类型
		
		
**** 函数功能：
**** 
		1.int processor()
			功能：
				1. 使用文档操作函数打开源程序文件(code.txt)，
				2. 去除两种类型（“//”,“/*…”）的注释、
				3. 多余的空格合并为一个、换行符、回车符等，
				4. 然后将处理后的保存在另一个新的文件(afterdel.txt)中
				5. 最后关闭文档。 
	 	2.void set_reserve()
	 		功能：
			 	1.设置保留字 
	 	3.bool judge_word(char x)
	 		功能：
			 	1.判断是否为字母 
	 	4.bool judge_number(char x)
	 		功能：
			 	1.判断是否为数字
		5.bool judge_jiefu(char x)
			功能：
				1.判断是不是分界符
		6.bool judge_yunsuanfu1(char x) 
			功能： 
				1.判断加减乘
		7.bool judge_yunsuannfu2(char x)
			功能：
				1.判断大于小于之类
		8.int scan(FILE* fp)
			功能：
				1.从文件读取一个单词
**** 其他声明：

**** 实验内容：
		1.对于实验内容1，选择编写c语言的源程序存放在code.txt中，设计一个c语言的词法分析器，
			主要包含三部分，
				1.一部分是预处理函数，
				2.第二部分是扫描判断单词类型的函数，
				3.第三部分是主函数，调用其它函数；
	
 		2.对于实验内容2，主要实现在预处理函数processor()中，
		 	1.使用文档操作函数打开源程序文件(code.txt)，
		    2.去除两种类型（“//”,“/*…）的注释、多余的空格合并为一个、换行符、回车符等，
			3.然后将处理后的保存在另一个新的文件(afterdel.txt)中，最后关闭文档。

		3.对于实验内容3，打开处理后的文件，然后调用扫描函数，从文件里读取一个单词调用判断单词类型的函数与之前建立的符号表进行对比判断，最后格式化输出。 
	 

*/

//*******************************程序实现***************************************

//头文件区
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib> 

using namespace std;



//**************************全局变量区**********************************

//1.保留字数组 
string  reserved_word[20];

int aa;// fseek的时候用来接着的

string  word = "";

char buffer;//每次读进来的一个字符

int num = 0;//每个单词中当前字符的位置

int line = 1; //行数

int row = 1; //列数，就是每行的第几个

bool flag; //文件是否结束了

int flag2;//单词的类型



// ************************函数现实区***********************************

//1.设置保留字 
void set_reserve()
{
	reserved_word[1] = "return";
    reserved_word[2] = "def";
    reserved_word[3] = "if";
    reserved_word[4] = "else";
    reserved_word[5] = "while";
    reserved_word[6] = "return";
    reserved_word[7] = "char";
    reserved_word[8] = "for";
    reserved_word[9] = "and";
    reserved_word[10] = "or";
    reserved_word[11] = "int";
    reserved_word[12] = "bool";
} 

//2.数据清洗 
int processor()
{
	// 存取获取的每个字符 
	char str[1000],c,str1[1000]; 
	//i:记录获取的字符数 
	int i = 0,j = 0,falg = 0,len;
	
	//1.以读的方式打开二进制打开文件
	FILE* p;
	if ((p = fopen("code.txt", "rt")) == NULL) 
	{
        printf("无法打开需要清洗的code.txt文件\n");
        return  0;
    }
    else 
	{
		//2.将数据读入数组str中 
		while((c = getc(p)) != EOF) 
		{ 
			str[i++] = c;
		}
		//关闭文件
		fclose(p); 
		str[i] = '\0';
		
		//遍历字符数组开始清洗 
		printf("开始清洗\n"); 
		for (i = 0; i < strlen(str); i++) 
		{
			//1.清除单行注释
			if (str[i] == '/' && str[i + 1] == '/') 
			{
				//增加i的值跳过单行注释区 
                while (str[i++] != '\n') {}
            }
            //2. 清除多行注释 
            else if (str[i] == '/' && str[i + 1] == '*') 
			{
				//增加i的值没有遇到*/就跳过 
                while (!(str[i] == '*' && str[i + 1] == '/')) { i++; }
                //跳过*/ 
                i += 2;
            }
            //3.清除多个空格留一个 
            else if (str[i] == ' ' && str[i + 1] == ' ') 
			{
                while (str[i] == ' ') { i++; }
                //跳回最后的空格 
                i--;
                if (str1[j - 1] != ' ')
                    str1[j++] = ' ';
            }
			//4.换行处理 
            else if (str[i] == '\n') 
			{
                if (str1[j - 1] != ' ')
                    str1[j++] = ' ';
            }
            //5.tab键处理 
            else if (str[i] == 9) {
                while (str[i] == 9) {
                    i++;
                }
                if (str1[j - 1] != ' ')
                    str1[j++] = ' ';
                i--;
            }
            //6.其他字符处理
            else str1[j++] = str[i];
		}
		str1[j] = '\0';
		printf("清洗后的str：\n %s \n",str1);
        if ((p = fopen("afterdel.txt", "w")) == NULL) {
            printf("找不到afterdel.txt文件\n");
            return 0;
        }
        else {
        	//将str1中的字符写入afterdel.txt文件中 
            if (fputs(str1, p) != 0) {
                printf("预处理失败！\n");
            }
            else printf("预处理成功！\n");
        }
        fclose(p);	
	}
	return 0;	
} 
//看这个字是不是字母
bool judge_word(char x)
{
    if (x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z') {
        return true;
    }
    else return false;
}

//看这个字是不是数字
bool judge_number(char x)
{
    if (x >= '0' && x <= '9') {
        return true;
    }
    else return false;
}

//看这个字符是不是界符
bool judge_jiefu(char x)
{
    if (x == '(' || x == ')' || x == ',' || x == ';' || x == '{' || x == '}') {
        return true;
    }
    else return false;
}


//加减乘
bool judge_yunsuanfu1(char x)
{
    if (x == '+' || x == '-' || x == '*')
    {
        return true;
    }
    else return false;
}

//等于 赋值，大于小于 大于等于，小于等于，大于小于
bool judge_yunsuannfu2(char x)
{
    if (x == '=' || x == '>' || x == '<' || x == '&' || x == '||') {
        return true;
    }
    else return false;
}


//从文件里读一个单词
int scan(FILE* fp)
{
    buffer = fgetc(fp);//读取一个字符
    if (feof(fp)) {//检测结束符
        flag = 0; return 0;
    }
    else if (buffer == ' ')
    {
        row++;
        return 0;
    }
    else if (buffer == '\n')
    {
        row = 1;
        return 0;
    }
    //如果是字母开头或'_' 看关键字还是普通单词
    else if (judge_word(buffer) || buffer == '_')
    {
        word += buffer;
        row++;
        while ((buffer = fgetc(fp)) && (judge_word(buffer) || judge_number(buffer) || buffer == '_'))
        {
            word += buffer;
            row++;
        }
        if (feof(fp)) {
            flag = 0;
            return 1;
        }
        for (int i = 1; i <= 12; i++) {
            if (word == reserved_word[i]) {
                aa = fseek(fp, -1, SEEK_CUR);//如果执行成功，stream将指向以fromwhere为基准，偏移offset（指针偏移量）个字节的位置，函数返回0。
                return 3;
            }
        }
        aa = fseek(fp, -1, SEEK_CUR);
        return 1;
    }

    //开始是加减乘 一定是类型4
    else if (judge_yunsuanfu1(buffer))
    {
        word += buffer;
        row++;
        return 4;
    }

    //开始是数字就一定是数字
    else if (judge_number(buffer))
    {
        word += buffer;
        row++;
        while ((buffer = fgetc(fp)) && judge_number(buffer))
        {
            word += buffer;
            row++;
        }
        if (feof(fp)) {
            flag = 0;
            return 2;
        }
        aa = fseek(fp, -1, SEEK_CUR);
        return 2;
    }

    //检验界符
    else if (judge_jiefu(buffer))
    {
        word += buffer;
        row++;
        return 6;
    }

    //检验 <=、  >=、  <>、  == =、 <、>
    else if (judge_yunsuannfu2(buffer))
    {
        row++;
        word += buffer;
        if (buffer == '<')   //为了检验题目中的<> <=
        {
            buffer = fgetc(fp);
            if (buffer == '>' || buffer == '=')
            {
                word += buffer;
                row++;
                return 5;
            }
        }
        //检验  >= ==
        else {
            buffer = fgetc(fp);
            if (buffer == '=')
            {
                word += buffer;
                row++;
                return 5;
            }
        }
        if (feof(fp)) {
            flag = 0;
        }
        aa = fseek(fp, -1, SEEK_CUR);
        return 4;
    }

    //首字符是/ 有可能是除号 也有可能是注释
    else if (buffer == '/')
    {
        row++;
        word += buffer;
        buffer = fgetc(fp);
        aa = fseek(fp, -1, SEEK_CUR);
        return 4;
    }

    else {
        word += buffer;
        row++;
        return -1;
    }
}



int main()
{
	//1.设置保留字
	set_reserve(); 
	
	//2.数据清洗
	processor();
	cout << "打开 " << "afterdel.txt文件\n" << endl;
	//3.打开文件循环读取一个单词判断类型
	//4.flag用来判断类型 
	flag = 1;
    FILE* fp;
    if (!(fp = fopen("afterdel.txt", "r")))
    {
        cout << "没有找到这个文件或者其他错误\n " << endl;
        flag = 0;
    }
    while (flag == 1)
    {
        //flag2 返回的类型
        flag2 = scan(fp);//反复调用函数提取单词

        if (flag2 == 1)
        {
            cout << "type:1 identifier(标识符)      " << word << endl;
            if (word.length() > 20)
                cout << "长度不能超过20" << endl;
                //begin()返回string中第一个元素所对应的位置。
                //end()返回string中最后一个元素的后一个位置（可以用字符串末尾的"\0"来理解：我们不写"\0"，但还是存在。
				//注意，这里是可以理解，真正的解释可能不是这个...）。 
            word.erase(word.begin(), word.end());
        }
         else if (flag2 == 2)
        {
            cout << "type:2 positive number（正数） " << word << endl;
            //if(word[0]=='0')
            //cout<<"ERROR: The first digit cannot be 0!"<<endl;
            word.erase(word.begin(), word.end());
        }
        else if (flag2 == 3)
        {
            cout << "type:3 reserved word（保留字）   " << word << endl;
            word.erase(word.begin(), word.end());
        }
        else if (flag2 == 4)
        {
            cout << "type:4 unary_operator（一目运算符）  " << word << endl;
            word.erase(word.begin(), word.end());
        }
        else if (flag2 == 5)
        {
            cout << "type:5 double_operator（二目运算符） " << word << endl;
            word.erase(word.begin(), word.end());
        }
        else if (flag2 == 6)
        {
            cout << "type:6 Separator（分隔符）       " << word << endl;
            word.erase(word.begin(), word.end());
        }
        //非法字符
        else if (flag2 == -1)
        {
            cout << "Illegal character（非法符号）      " << word << endl;
            word.erase(word.begin(), word.end());
        }
    }
	//4.关闭文件 
	int a = fclose(fp);
    cout << "按e关闭" << endl;
    char end;
    while (cin >> end && end != 'e') {
        cout << "只有e可以关闭" << endl;
    }
    return 0;
} 

 
 