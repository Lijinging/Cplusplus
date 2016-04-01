#include<iostream>
#include<string>
using namespace std;

string big_integer_add(string a, string b);
string big_integer_sub(string a, string b);
int big_integer_compare(string str1, string str2);
string big_integer_mul(string str1, string str2);
void big_integer_div(string str1, string str2, string &quotient, string &residue);

void show(string a)
{
	cout << "----------------------" << endl;
	for (auto i : a)
		cout << i << "\t";
	cout << endl;
	cout << "----------------------" << endl;
}

/*******************************************
�������Ƚ�
���룺�������������ɸ���
�����	1��a>b
0: a=b
-1: a<b
*******************************************/
int big_integer_compare(string str1, string str2)
{
	if (str1 == "-0") str1 = "0";
	if (str2 == "-0") str2 = "0";
	if (str1[0]!='-' && str2[0]!='-')
	{
		if (str1.length() > str2.length()) return 1;
		else if (str1.length() < str2.length())  return -1;
		else return str1.compare(str2);
	}
	else if (str1[0] != '-' && str2[0] == '-') return 1;
	else if (str1[0] == '-' && str2[0] != '-') return -1;
	else return (-1)*str1.compare(str2);
}

/*******************************************
�������ӷ�
���룺�������������ɸ���
�������string������֮��
*******************************************/
string big_integer_add(string a, string b)
{
	bool isNeg = false;
	if (a[0] == '-' && b[0] == '-')
		isNeg = true;
	else if (a[0] == '-' && b[0] != '-')
		return big_integer_sub(b, a.substr(1, a.size()));
	else if (a[0] != '-' && b[0] == '-')
		return big_integer_sub(a, b.substr(1, b.size()));

	string ans;
	int carry;
	int i, j, k;
	int add1, add2, sum;
	i = a.size() - 1;
	j = b.size() - 1;
	k = i > j ? i : j;
	if (i > j) ans = a; else ans = b;//ʹans�к��ʵĴ洢�ռ�
	for (carry = 0; k >= 0; i--, j--, k--)
	{
		add1 = i < 0 ? 0 : a[i] - '0';
		add2 = j < 0 ? 0 : b[j] - '0';
		sum = add2 + add1 + carry >= 10 ? add1 + add2 + carry - 10 : add1 + add2 + carry;
		carry = add1 + add2 + carry >= 10 ? 1 : 0;
		ans[k] = sum + '0';
	}
	if (carry) ans = "1" + ans;
	if (isNeg) ans = "-" + ans;
	return ans;
}


/*******************************************
����������
���룺����������(�ɸ�)
�������string������֮��
*******************************************/
string big_integer_sub(string a, string b)
{
	if (a[0] == '-' && b[0] == '-')
	{
		string tmp = a.substr(1, a.size());
		a = b.substr(1, b.size());
		b = tmp;
	}
	else if (a[0] == '-' && b[0] != '-')
		return "-" + big_integer_add(a.substr(1, a.size()), b);
	else if (a[0] != '-' && b[0] == '-')
		return big_integer_add(a, b.substr(1, b.size()));

	string ans;
	bool isNeg = false;
	int compare = big_integer_compare(b, a);
	if (compare == 1)
	{
		string tmp = a;
		a = b;
		b = tmp;
		isNeg = true;
	}
	else if (compare == 0)
		return "0";
	int a_len = a.size();
	int b_len = b.size();
	int tmp = a_len - b_len;
	int cf = 0;
	for (int i = b_len - 1; i >= 0; i--)
	{
		if (a[tmp + i] < b[i] + cf)
		{
			ans = char(a[tmp + i] - b[i] - cf + '0' + 10) + ans;
			cf = 1;
		}
		else
		{
			ans = char(a[tmp + i] - b[i] - cf + '0') + ans;
			cf = 0;
		}
	}
	for (int i = tmp - 1; i >= 0; i--)
	{
		if (a[i] - cf > '0')
		{
			ans = char(a[i] - cf) + ans;
			cf = 0;
		}
		else
		{
			ans = char(a[i] - cf + 10) + ans;
			cf = 1;
		}
	}
	ans.erase(0, ans.find_first_not_of('0'));//ȥ������ж����ǰ��0
	if (isNeg) ans = "-" + ans;
	return ans;
}


/*******************************************
�������˷�
���룺����������(�ɸ�)
�������string������֮��
*******************************************/
string big_integer_mul(string str1, string str2)
{
	string str;

	bool isNeg = false;
	if (str1[0] == '-')
	{
		str1 = str1.substr(1, str1.size());
		isNeg = !isNeg;
	}
	if (str2[0] == '-')
	{
		str2 = str2.substr(2, str2.size());
		isNeg = !isNeg;
	}


	int len1 = str1.length();
	int len2 = str2.length();
	string tempstr;
	for (int i = len2 - 1; i >= 0; i--)
	{
		tempstr = "";
		int temp = str2[i] - '0';
		int t = 0;
		int cf = 0;
		if (temp != 0)
		{
			for (int j = 1; j <= len2 - 1 - i; j++)
				tempstr += "0";
			for (int j = len1 - 1; j >= 0; j--)
			{
				t = (temp*(str1[j] - '0') + cf) % 10;
				cf = (temp*(str1[j] - '0') + cf) / 10;
				tempstr = char(t + '0') + tempstr;
			}
			if (cf != 0) tempstr = char(cf + '0') + tempstr;
		}
		str = big_integer_add(str, tempstr);
	}
	str.erase(0, str.find_first_not_of('0'));
	if (isNeg) str = "-" + str;
	return str;
}

//�߾��ȳ���
//���������������Ϊquotient,����Ϊresidue
//��Ҫ�߾��ȼ����ͳ˷�
void big_integer_div(string str1, string str2, string &quotient, string &residue)
{
	bool isNeg = false;
	if (str1[0] == '-')
	{
		str1 = str1.substr(1, str1.size());
		isNeg = !isNeg;
	}
	if (str2[0] == '-')
	{
		str2 = str2.substr(2, str2.size());
		isNeg = !isNeg;
	}

	quotient = residue = "";//���
	if (str2 == "0")//�жϳ����Ƿ�Ϊ0
	{
		quotient = residue = "ERROR";
		return;
	}
	if (str1 == "0")//�жϱ������Ƿ�Ϊ0
	{
		quotient = residue = "0";
		return;
	}
	int res = big_integer_compare(str1, str2);
	if (res < 0)
	{
		quotient = "0";
		residue = str1;
		return;
	}
	else if (res == 0)
	{
		quotient = "1";
		residue = "0";
		return;
	}
	else
	{
		int len1 = str1.length();
		int len2 = str2.length();
		string tempstr;
		tempstr.append(str1, 0, len2 - 1);
		for (int i = len2 - 1; i < len1; i++)
		{
			tempstr = tempstr + str1[i];
			tempstr.erase(0, tempstr.find_first_not_of('0'));
			if (tempstr.empty())
				tempstr = "0";
			for (char ch = '9'; ch >= '0'; ch--)//����
			{
				string str, tmp;
				str = str + ch;
				tmp = big_integer_mul(str2, str);
				if (big_integer_compare(tmp, tempstr) <= 0)//���̳ɹ�
				{
					quotient = quotient + ch;
					tempstr = big_integer_sub(tempstr, tmp);
					break;
				}
			}
		}
		residue = tempstr;
	}
	quotient.erase(0, quotient.find_first_not_of('0'));
	if (quotient.empty()) quotient = "0";
	if (isNeg)
	{
		quotient = "-" + quotient;
		residue = "-" + residue;
	}

}

void solve_auto(string str1, string str2)
{
	string quotient, residue;
	cout << "---------------------------------" << endl;
	cout << "a+b=" << big_integer_add(str1, str2) << endl;
	cout << "a-b=" << big_integer_sub(str1, str2) << endl;
	cout << "a*b=" << big_integer_mul(str1, str2) << endl;
	big_integer_div(str1, str2, quotient, residue);
	if (residue=="0")	cout << "a/b=" << quotient << endl;
	else				cout << "a/b=" << quotient << "......" << residue << endl;
	cout << "---------------------------------" << endl;
}

int main()
{
	string a, b;
	string ans;
	while (cin >> a >> b)
	{
// 		a.erase(0, a.find_first_not_of('0'));
// 		a.erase(0, a.find_first_not_of('0'));
 		solve_auto(a, b);
// 		
// 		cout << big_integer_compare(a, b) << endl;
// 		ans = big_integer_sub(a, b);
// 		cout << ans << endl;
	}
	return 0;
}