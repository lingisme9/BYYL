/*

**** ���������ʷ�����-�ļ���ȡ���� 
**** ʱ�䣺2020��10��13��
**** ���ߣ�����

**** ����˼·
		1.������ϴ
		2.��ȡ�����ж��Ƿ���
		3.������ 

**** �������壺
		1.int aa;fseek��ʱ���������ŵ�
		2.string  word = "";
		3.string  reserved_word[20];//����
	 	4.char buffer;//ÿ�ζ�������һ���ַ�
		5.int num = 0;//ÿ�������е�ǰ�ַ���λ��
		6.int line = 1; //����
		7.int row = 1; //����������ÿ�еĵڼ���
		8.bool flag; //�ļ��Ƿ������
		9.int flag2;//���ʵ�����
		
		
**** �������ܣ�
**** 
		1.int processor()
			���ܣ�
				1. ʹ���ĵ�����������Դ�����ļ�(code.txt)��
				2. ȥ���������ͣ���//��,��/*��������ע�͡�
				3. ����Ŀո�ϲ�Ϊһ�������з����س����ȣ�
				4. Ȼ�󽫴����ı�������һ���µ��ļ�(afterdel.txt)��
				5. ���ر��ĵ��� 
	 	2.void set_reserve()
	 		���ܣ�
			 	1.���ñ����� 
	 	3.bool judge_word(char x)
	 		���ܣ�
			 	1.�ж��Ƿ�Ϊ��ĸ 
	 	4.bool judge_number(char x)
	 		���ܣ�
			 	1.�ж��Ƿ�Ϊ����
		5.bool judge_jiefu(char x)
			���ܣ�
				1.�ж��ǲ��Ƿֽ��
		6.bool judge_yunsuanfu1(char x) 
			���ܣ� 
				1.�жϼӼ���
		7.bool judge_yunsuannfu2(char x)
			���ܣ�
				1.�жϴ���С��֮��
		8.int scan(FILE* fp)
			���ܣ�
				1.���ļ���ȡһ������
**** ����������

**** ʵ�����ݣ�
		1.����ʵ������1��ѡ���дc���Ե�Դ��������code.txt�У����һ��c���ԵĴʷ���������
			��Ҫ���������֣�
				1.һ������Ԥ��������
				2.�ڶ�������ɨ���жϵ������͵ĺ�����
				3.��������������������������������
	
 		2.����ʵ������2����Ҫʵ����Ԥ������processor()�У�
		 	1.ʹ���ĵ�����������Դ�����ļ�(code.txt)��
		    2.ȥ���������ͣ���//��,��/*������ע�͡�����Ŀո�ϲ�Ϊһ�������з����س����ȣ�
			3.Ȼ�󽫴����ı�������һ���µ��ļ�(afterdel.txt)�У����ر��ĵ���

		3.����ʵ������3���򿪴������ļ���Ȼ�����ɨ�躯�������ļ����ȡһ�����ʵ����жϵ������͵ĺ�����֮ǰ�����ķ��ű���жԱ��жϣ�����ʽ������� 
	 

*/

//*******************************����ʵ��***************************************

//ͷ�ļ���
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib> 

using namespace std;



//**************************ȫ�ֱ�����**********************************

//1.���������� 
string  reserved_word[20];

int aa;// fseek��ʱ���������ŵ�

string  word = "";

char buffer;//ÿ�ζ�������һ���ַ�

int num = 0;//ÿ�������е�ǰ�ַ���λ��

int line = 1; //����

int row = 1; //����������ÿ�еĵڼ���

bool flag; //�ļ��Ƿ������

int flag2;//���ʵ�����



// ************************������ʵ��***********************************

//1.���ñ����� 
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

//2.������ϴ 
int processor()
{
	// ��ȡ��ȡ��ÿ���ַ� 
	char str[1000],c,str1[1000]; 
	//i:��¼��ȡ���ַ��� 
	int i = 0,j = 0,falg = 0,len;
	
	//1.�Զ��ķ�ʽ�򿪶����ƴ��ļ�
	FILE* p;
	if ((p = fopen("code.txt", "rt")) == NULL) 
	{
        printf("�޷�����Ҫ��ϴ��code.txt�ļ�\n");
        return  0;
    }
    else 
	{
		//2.�����ݶ�������str�� 
		while((c = getc(p)) != EOF) 
		{ 
			str[i++] = c;
		}
		//�ر��ļ�
		fclose(p); 
		str[i] = '\0';
		
		//�����ַ����鿪ʼ��ϴ 
		printf("��ʼ��ϴ\n"); 
		for (i = 0; i < strlen(str); i++) 
		{
			//1.�������ע��
			if (str[i] == '/' && str[i + 1] == '/') 
			{
				//����i��ֵ��������ע���� 
                while (str[i++] != '\n') {}
            }
            //2. �������ע�� 
            else if (str[i] == '/' && str[i + 1] == '*') 
			{
				//����i��ֵû������*/������ 
                while (!(str[i] == '*' && str[i + 1] == '/')) { i++; }
                //����*/ 
                i += 2;
            }
            //3.�������ո���һ�� 
            else if (str[i] == ' ' && str[i + 1] == ' ') 
			{
                while (str[i] == ' ') { i++; }
                //�������Ŀո� 
                i--;
                if (str1[j - 1] != ' ')
                    str1[j++] = ' ';
            }
			//4.���д��� 
            else if (str[i] == '\n') 
			{
                if (str1[j - 1] != ' ')
                    str1[j++] = ' ';
            }
            //5.tab������ 
            else if (str[i] == 9) {
                while (str[i] == 9) {
                    i++;
                }
                if (str1[j - 1] != ' ')
                    str1[j++] = ' ';
                i--;
            }
            //6.�����ַ�����
            else str1[j++] = str[i];
		}
		str1[j] = '\0';
		printf("��ϴ���str��\n %s \n",str1);
        if ((p = fopen("afterdel.txt", "w")) == NULL) {
            printf("�Ҳ���afterdel.txt�ļ�\n");
            return 0;
        }
        else {
        	//��str1�е��ַ�д��afterdel.txt�ļ��� 
            if (fputs(str1, p) != 0) {
                printf("Ԥ����ʧ�ܣ�\n");
            }
            else printf("Ԥ����ɹ���\n");
        }
        fclose(p);	
	}
	return 0;	
} 
//��������ǲ�����ĸ
bool judge_word(char x)
{
    if (x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z') {
        return true;
    }
    else return false;
}

//��������ǲ�������
bool judge_number(char x)
{
    if (x >= '0' && x <= '9') {
        return true;
    }
    else return false;
}

//������ַ��ǲ��ǽ��
bool judge_jiefu(char x)
{
    if (x == '(' || x == ')' || x == ',' || x == ';' || x == '{' || x == '}') {
        return true;
    }
    else return false;
}


//�Ӽ���
bool judge_yunsuanfu1(char x)
{
    if (x == '+' || x == '-' || x == '*')
    {
        return true;
    }
    else return false;
}

//���� ��ֵ������С�� ���ڵ��ڣ�С�ڵ��ڣ�����С��
bool judge_yunsuannfu2(char x)
{
    if (x == '=' || x == '>' || x == '<' || x == '&' || x == '||') {
        return true;
    }
    else return false;
}


//���ļ����һ������
int scan(FILE* fp)
{
    buffer = fgetc(fp);//��ȡһ���ַ�
    if (feof(fp)) {//��������
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
    //�������ĸ��ͷ��'_' ���ؼ��ֻ�����ͨ����
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
                aa = fseek(fp, -1, SEEK_CUR);//���ִ�гɹ���stream��ָ����fromwhereΪ��׼��ƫ��offset��ָ��ƫ���������ֽڵ�λ�ã���������0��
                return 3;
            }
        }
        aa = fseek(fp, -1, SEEK_CUR);
        return 1;
    }

    //��ʼ�ǼӼ��� һ��������4
    else if (judge_yunsuanfu1(buffer))
    {
        word += buffer;
        row++;
        return 4;
    }

    //��ʼ�����־�һ��������
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

    //������
    else if (judge_jiefu(buffer))
    {
        word += buffer;
        row++;
        return 6;
    }

    //���� <=��  >=��  <>��  == =�� <��>
    else if (judge_yunsuannfu2(buffer))
    {
        row++;
        word += buffer;
        if (buffer == '<')   //Ϊ�˼�����Ŀ�е�<> <=
        {
            buffer = fgetc(fp);
            if (buffer == '>' || buffer == '=')
            {
                word += buffer;
                row++;
                return 5;
            }
        }
        //����  >= ==
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

    //���ַ���/ �п����ǳ��� Ҳ�п�����ע��
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
	//1.���ñ�����
	set_reserve(); 
	
	//2.������ϴ
	processor();
	cout << "�� " << "afterdel.txt�ļ�\n" << endl;
	//3.���ļ�ѭ����ȡһ�������ж�����
	//4.flag�����ж����� 
	flag = 1;
    FILE* fp;
    if (!(fp = fopen("afterdel.txt", "r")))
    {
        cout << "û���ҵ�����ļ�������������\n " << endl;
        flag = 0;
    }
    while (flag == 1)
    {
        //flag2 ���ص�����
        flag2 = scan(fp);//�������ú�����ȡ����

        if (flag2 == 1)
        {
            cout << "type:1 identifier(��ʶ��)      " << word << endl;
            if (word.length() > 20)
                cout << "���Ȳ��ܳ���20" << endl;
                //begin()����string�е�һ��Ԫ������Ӧ��λ�á�
                //end()����string�����һ��Ԫ�صĺ�һ��λ�ã��������ַ���ĩβ��"\0"����⣺���ǲ�д"\0"�������Ǵ��ڡ�
				//ע�⣬�����ǿ�����⣬�����Ľ��Ϳ��ܲ������...���� 
            word.erase(word.begin(), word.end());
        }
         else if (flag2 == 2)
        {
            cout << "type:2 positive number�������� " << word << endl;
            //if(word[0]=='0')
            //cout<<"ERROR: The first digit cannot be 0!"<<endl;
            word.erase(word.begin(), word.end());
        }
        else if (flag2 == 3)
        {
            cout << "type:3 reserved word�������֣�   " << word << endl;
            word.erase(word.begin(), word.end());
        }
        else if (flag2 == 4)
        {
            cout << "type:4 unary_operator��һĿ�������  " << word << endl;
            word.erase(word.begin(), word.end());
        }
        else if (flag2 == 5)
        {
            cout << "type:5 double_operator����Ŀ������� " << word << endl;
            word.erase(word.begin(), word.end());
        }
        else if (flag2 == 6)
        {
            cout << "type:6 Separator���ָ�����       " << word << endl;
            word.erase(word.begin(), word.end());
        }
        //�Ƿ��ַ�
        else if (flag2 == -1)
        {
            cout << "Illegal character���Ƿ����ţ�      " << word << endl;
            word.erase(word.begin(), word.end());
        }
    }
	//4.�ر��ļ� 
	int a = fclose(fp);
    cout << "��e�ر�" << endl;
    char end;
    while (cin >> end && end != 'e') {
        cout << "ֻ��e���Թر�" << endl;
    }
    return 0;
} 

 
 