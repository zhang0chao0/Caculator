
// CaculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Caculator.h"
#include "CaculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Resource.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
//**************包含函数atof()，将字符转化为浮点数
#include <math.h>
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCaculatorDlg 对话框



CCaculatorDlg::CCaculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCaculatorDlg::IDD, pParent)
	, m_input(_T(""))
	, sum(0)
	, copy_str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCaculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_input);
	DDX_Text(pDX, IDC_EDIT2, sum);
}

BEGIN_MESSAGE_MAP(CCaculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCaculatorDlg::On_0)
	ON_BN_CLICKED(IDC_BUTTON8, &CCaculatorDlg::On_point)
	ON_BN_CLICKED(IDC_BUTTON2, &CCaculatorDlg::On_1)
	ON_BN_CLICKED(IDC_BUTTON7, &CCaculatorDlg::On_2)
	ON_BN_CLICKED(IDC_BUTTON4, &CCaculatorDlg::On_3)
	ON_BN_CLICKED(IDC_BUTTON5, &CCaculatorDlg::On_4)
	ON_BN_CLICKED(IDC_BUTTON10, &CCaculatorDlg::On_5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCaculatorDlg::On_6)
	ON_BN_CLICKED(IDC_BUTTON11, &CCaculatorDlg::On_7)
	ON_BN_CLICKED(IDC_BUTTON13, &CCaculatorDlg::On_8)
	ON_BN_CLICKED(IDC_BUTTON12, &CCaculatorDlg::On_9)
	ON_BN_CLICKED(IDC_BUTTON15, &CCaculatorDlg::On_add)
	ON_BN_CLICKED(IDC_BUTTON14, &CCaculatorDlg::On_sub)
	ON_BN_CLICKED(IDC_BUTTON9, &CCaculatorDlg::On_mux)
	ON_BN_CLICKED(IDC_BUTTON16, &CCaculatorDlg::On_delive)
	ON_BN_CLICKED(IDC_BUTTON18, &CCaculatorDlg::On_remainer)
	ON_BN_CLICKED(IDC_BUTTON19, &CCaculatorDlg::On_light)
	ON_BN_CLICKED(IDC_BUTTON23, &CCaculatorDlg::On_right)
	ON_BN_CLICKED(IDC_BUTTON27, &CCaculatorDlg::On_tui)
	ON_BN_CLICKED(IDC_BUTTON26, &CCaculatorDlg::On_delete)
	ON_BN_CLICKED(IDC_BUTTON3, &CCaculatorDlg::On_equal)
	ON_BN_CLICKED(IDC_BUTTON17, &CCaculatorDlg::On_sin)
	ON_BN_CLICKED(IDC_BUTTON21, &CCaculatorDlg::On_cos)
	ON_BN_CLICKED(IDC_BUTTON24, &CCaculatorDlg::On_tan)
	ON_BN_CLICKED(IDC_BUTTON22, &CCaculatorDlg::On_sqrt)
	ON_BN_CLICKED(IDC_BUTTON25, &CCaculatorDlg::On_N)
	ON_BN_CLICKED(IDC_BUTTON20, &CCaculatorDlg::On_P)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_0_32771, &CCaculatorDlg::On032771)
	ON_COMMAND(ID_0_32772, &CCaculatorDlg::On032772)
END_MESSAGE_MAP()


// CCaculatorDlg 消息处理程序

BOOL CCaculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCaculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCaculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCaculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCaculatorDlg::On_0()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("0");
	UpdateData(false);
}


void CCaculatorDlg::On_point()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_input.IsEmpty())
		return;
	//***************************浅度判断，.前面只可能是数字
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (!(temp >= '0'&&temp <= '9'))
			return;
	}
	//***************************深度判断，一个数字不可能有两个小数点
	int len = m_input.GetLength();
	while (len)
	{
		if (m_input[len - 1] == '+' || m_input[len - 1] == '-' || m_input[len - 1] == '*' ||
			m_input[len - 1] == '%' || m_input[len - 1] == '/'
			|| m_input[len - 1] == 'N' || m_input[len - 1] == 'P')
			break;
		if (m_input[len-1] == '.')
			return;
		len--;
	}
	m_input += _T(".");
	UpdateData(false);
}


void CCaculatorDlg::On_1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("1");
	UpdateData(false);
}


void CCaculatorDlg::On_2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("2");
	UpdateData(false);
}


void CCaculatorDlg::On_3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("3");
	UpdateData(false);
}



void CCaculatorDlg::On_4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("4");
	UpdateData(false);
}


void CCaculatorDlg::On_5()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("5");
	UpdateData(false);
}


void CCaculatorDlg::On_6()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("6");
	UpdateData(false);
}



void CCaculatorDlg::On_7()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("7");
	UpdateData(false);
}


void CCaculatorDlg::On_8()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("8");
	UpdateData(false);
}


void CCaculatorDlg::On_9()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == ')')
			return;
	}
	m_input += _T("9");
	UpdateData(false);
}


void CCaculatorDlg::On_add()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_input.IsEmpty())
		return;
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == '+' || temp == '-' || temp == '*' || temp == '/' 
			|| temp == '%' || temp == '.' || temp == 'N' || temp == 'P' || temp == '(')
			return;
	}
	m_input += _T("+");
	UpdateData(false);
}



void CCaculatorDlg::On_sub()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_input.IsEmpty())
		return;
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == '+' || temp == '-' || temp == '*' || temp == '/' 
			|| temp == '%' || temp == '.' || temp == 'N' || temp == 'P' || temp == '(')
			return;
	}
	m_input += _T("-");
	UpdateData(false);
}


void CCaculatorDlg::On_mux()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_input.IsEmpty())
		return;
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == '+' || temp == '-' || temp == '*' || temp == '/' 
			|| temp == '%' || temp == '.' || temp == 'N' || temp == 'P' || temp == '(')
			return;
	}
	m_input += _T("*");
	UpdateData(false);
}


void CCaculatorDlg::On_delive()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_input.IsEmpty())
		return;
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == '+' || temp == '-' || temp == '*' || temp == '/'
			|| temp == '%' || temp == '.' || temp == 'N' || temp == 'P' || temp == '(')
			return;
	}
	m_input += _T("/");
	UpdateData(false);
}



void CCaculatorDlg::On_remainer()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_input.IsEmpty())
		return;
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == '+' || temp == '-' || temp == '*' || temp == '/' || 
			temp == '%' || temp == '.' || temp == 'N' || temp == 'P' || temp == '(')
			return;
	}
	m_input += _T("%");
	UpdateData(false);
}


void CCaculatorDlg::On_light()
{
	// TODO:  在此添加控件通知处理程序代码
	//*****************左括号左边不能是数字或者点
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (((temp >= '0'&&temp <= '9') || temp == '.'))
			return;
	}
	m_input += _T("(");
	UpdateData(false);
}


void CCaculatorDlg::On_right()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (!(temp >= '0'&&temp <= '9'))
			return;
	}
	if (m_input.IsEmpty())
		return;
	m_input += _T(")");
	UpdateData(false);
}


void CCaculatorDlg::On_tui()
{
	// TODO:  在此添加控件通知处理程序代码
	this->erase(m_input);
}


void CCaculatorDlg::On_delete()
{
	// TODO:  在此添加控件通知处理程序代码
	m_input = _T("");
	UpdateData(false);
}

//********************判断常见的错误，如括号匹配
bool CCaculatorDlg::judge(CString &s)
{
	int len = s.GetLength();
	//********************1.尾字符
	if (s[len - 1] == '+' || s[len - 1] == '-' || s[len - 1] == '*' || 
		s[len - 1] == '%' || s[len - 1] == '/' || s[len - 1] == '.'
		|| s[len-1] == 'N' || s[len-1] == 'P')
		return false;
	//*********************2.括号匹配
	Stack<int> temp;
	int j;
	for (int i = 0; i <len; i++)
	{
		if (s[i] == '(')
			temp.Push(s[i]);
		else if (s[i] == ')')
		if (!temp.Pop(j))      //弹栈不成功
		{
			//cout << "错误，左括号缺失！" << endl;
			::MessageBox(NULL,L"左括号缺失！",L"错误",MB_OK);
			return false;
		}
	}
	if (!temp.IsEmpty())
	{
		//cout << "错误，右括号缺失！" << endl;
		::MessageBox(NULL, L"右括号缺失！", L"错误", MB_OK);
		return false;
	}
	return true;
}

//**************************将中缀式转化为后缀式
void CCaculatorDlg::transfer(CString &s)
{
	ofstream fout;
	fout.open("1.txt", ios::out);
	int len = s.GetLength();
	Stack<char>myStack;
	for (int i = 0; i <len - 1; i++)        //除了最后一个字符暂且不判断
	{
		//***************1.是数字，不做处理
		if ((s[i] >='0'&&s[i] <= '9') || s[i] == '.')
		{
			fout <<(char)s[i];             //不知道为什么系统自动给我转成了ASCLL码的十进制
			if (s[i + 1]<'0'&&s[i + 1]>'9')
			{
				fout << " ";
				continue;
			}
			continue;
		}
		//***************2.是')'，弹栈至不为'('
		else if (')' == s[i])
		{
			char temp;
			myStack.Pop(temp);
			while ('(' != temp)
			{
				fout << temp;
				myStack.Pop(temp);
			}
		}
		//***************3.'+','-'直接弹栈,除非为空或遇'('
		else if ('+' == s[i] || '-' == s[i])
		{
			if (myStack.IsEmpty())
				myStack.Push(s[i]);
			else
			{
				char temp;
				do
				{
					myStack.Pop(temp);
					if ('(' == temp)          //如果是(,再压栈回去
						myStack.Push(temp);
					else
						fout << temp;
				} while (!myStack.IsEmpty() && '(' != temp);
				//***********如果栈不为空或者不为(,弹栈
				//***************弹栈结束了进栈
				myStack.Push(s[i]);
			}
		}
		//***************4.*,/,P
		else if ('*' == s[i] || '/' == s[i] || '%' == s[i]||s[i]=='P')
		{
			if (myStack.IsEmpty())
				myStack.Push(s[i]);
			else
			{
				char temp;
				do
				{
					myStack.Pop(temp);
					if ('(' == temp || '+' == temp || '-' == temp)          //如果是,再压栈回去
						myStack.Push(temp);
					else
						fout << temp;
				} while (!myStack.IsEmpty() && ('(' != temp) && ('+' != temp) && ('-' != temp));
				myStack.Push(s[i]);
			}
		}
		//**************************左括号直接压栈
		else if ('(' == s[i])
			myStack.Push(s[i]);
		//***************************************************补充
		//************负号直接压栈，它前面只可能是左括号
		else if ('N' == s[i])
			myStack.Push(s[i]);

		fout << " ";         //输出空格便于区分
	}
	//********************************最后一个字符
	if (s[len - 1] == ')')
	{
		char temp;
		myStack.Pop(temp);
		while ('(' != temp)
		{
			fout << temp;
			myStack.Pop(temp);
		}
	}
	else if (s[len - 1] >= '0'&&s[len - 1] <= '9')
		fout << (char)s[len- 1];
	//********************************最后弹出剩余的字符
	while (!myStack.IsEmpty())
	{
		char temp;
		myStack.Pop(temp);
		fout << temp;
	}
	fout.close();
}


void CCaculatorDlg::On_equal()
{
	if (m_input.IsEmpty())
		return;
	// TODO:  在此添加控件通知处理程序代码
	if (!judge(m_input))
	{
		::MessageBox(NULL, L"输入计算式有误！", L"错误", MB_OK);
		return;
	}
	this->transfer(m_input);
	//**************************开始计算
	Stack<double> stack2;
	stack2.Push(0);              //可以计算负数
	ifstream fin;
	fin.open("1.txt", ios::in);
	char a[500];
	char str[50];                //用于记录数字
	memset(str, '\0', 50);
	int j = 0;
	fin.getline(a, 100);
	int len = strlen(a);
	sum = 0;
	double add1, add2;           //待计算的两数
	int temp1, temp2;            //计算取余只能是整数
	//*********************为什么case里面不能定义变量
	for (int i = 0; i < len; i++)
	{
		//***************************操作数
		if ((a[i] >= '0'&&a[i] <= '9') || a[i] == '.')
		{
			str[j++] = a[i];       //把数字或点先保存起来
			//当它的下一项不在是数字也不是小数点，开始转化，后缀式的最后不可能是数字，所以不会越界
			if (!((a[i + 1] >= '0'&&a[i + 1] <= '9') || a[i + 1] == '.'))
			{
				//*****************字符转化为浮点数，压栈
				double temp = atof(str);
				stack2.Push(temp);
				j = 0;
				memset(str, '\0', 50);      //初始化数组
			}
			continue;
		}
		//***************************运算符
		switch (a[i])
		{
		case '+':
			stack2.Pop(add2);
			stack2.Pop(add1);
			sum = add1 + add2;
			stack2.Push(sum);
			break;
		case '-':
			stack2.Pop(add2);
			stack2.Pop(add1);
			sum = add1 - add2;
			stack2.Push(sum);
			break;
		case '*':
			stack2.Pop(add2);
			stack2.Pop(add1);
			sum = add1 * add2;
			stack2.Push(sum);
			break;
		case '/':
			stack2.Pop(add2);
			stack2.Pop(add1);
			if (add2 == 0)
			{
				//cout << "除数不能为0！" << endl;
				::MessageBox(NULL, L"除数不能为0！", L"错误", MB_OK);
				return;
			}
			sum = add1 / add2;
			stack2.Push(sum);
			break;
		case '%':
			stack2.Pop(add2);
			stack2.Pop(add1);
			temp1 = (int)add1;
			temp2 = (int)add2;
			sum = temp1%temp2;
			stack2.Push(sum);
			break;
		case ' ':
			continue;
			//******************************************补充
		case 'N':
			stack2.Pop(add1);
			sum = 0 - add1;
			stack2.Push(sum);
			break;
		case 'P':
			stack2.Pop(add2);
			stack2.Pop(add1);
			sum = pow(add1,add2);
			stack2.Push(sum);
			break;
		default:
			break;
		}
	}
	//cout << "计算之和：" << sum << endl;
	//***************若光数字，没有运算符，那数字还在栈中
	/*if (stack2.IsEmpty())
		return;*/
	stack2.Pop(sum);
	UpdateData(false);
	fin.close();
	copy_str = m_input;
	m_input = _T("");
}

//**************************擦除一个字符
void CCaculatorDlg::erase(CString &s)
{
	//*****************已经为空就不需要清空了
	if (s.IsEmpty())
		return;
	int len = s.GetLength();
	s = s.Left(len-1);
	//s[len - 1] = '\0';
	UpdateData(false);
}


void CCaculatorDlg::On_sin()
{
	// TODO:  在此添加控件通知处理程序代码
	//******************CString转double
	//double temp = _wtof(m_input);
	this->On_equal();
	sum = sin(sum);
	m_input = copy_str;             
	m_input = _T("sin(")+m_input+_T(")");
	UpdateData(false);
	copy_str = _T("");
	m_input = _T("");
	//sum = 0;
}


void CCaculatorDlg::On_cos()
{
	// TODO:  在此添加控件通知处理程序代码
	this->On_equal();
	sum = cos(sum);
	m_input = copy_str;
	m_input = _T("cos(") + m_input + _T(")");
	UpdateData(false);
	copy_str = _T("");
	m_input = _T("");
}


void CCaculatorDlg::On_tan()
{
	// TODO:  在此添加控件通知处理程序代码
	this->On_equal();
	sum = tan(sum);
	m_input = copy_str;
	m_input = _T("tan(") + m_input + _T(")");
	UpdateData(false);
	copy_str = _T("");
	m_input = _T("");
}


void CCaculatorDlg::On_sqrt()
{
	// TODO:  在此添加控件通知处理程序代码
	this->On_equal();
	sum = sqrt(sum);
	m_input = copy_str;
	m_input = _T("sqrt(") + m_input + _T(")");
	UpdateData(false);
	copy_str = _T("");
	m_input = _T("");
}


void CCaculatorDlg::On_N()
{
	// TODO:  在此添加控件通知处理程序代码
	//****************负号
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (temp == 'N')
			this->erase(m_input);
		if (temp != '(')
			return;
	}
	m_input += _T("N");
	UpdateData(false);
}


void CCaculatorDlg::On_P()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_input.IsEmpty())
		return;
	if (!m_input.IsEmpty())
	{
		char temp = m_input[m_input.GetLength() - 1];
		if (!(temp>='0'&&temp<='9'))
			return;
	}
	m_input += _T("P");
	UpdateData(false);
}


//*************************************右键菜单
void CCaculatorDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CMenu menu, *pSubMenu;
	menu.LoadMenuW(IDR_MENU1);
	pSubMenu = menu.GetSubMenu(0);
	GetCursorPos(&point);                                            //得到光标处
	pSubMenu->TrackPopupMenu(nFlags, point.x, point.y, this);        //确保右键点击在哪菜单出现在哪
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CCaculatorDlg::On032771()
{
	// TODO:  在此添加命令处理程序代码
	::MessageBox(NULL,L"2015/10/18",L"TIME",MB_OK);
}


void CCaculatorDlg::On032772()
{
	// TODO:  在此添加命令处理程序代码
	::MessageBox(NULL, L"帅气的超超", L"AUTHOR", MB_OK);
}




