#include "calculatormainwindow.h"
#include "ui_calculatormainwindow.h"
#include<QKeyEvent>
#include<QDebug>
#include<QString>
#include<QVector>

static bool isSignal(QChar c);//判断c是不是运算符

CalculatorMainWindow::CalculatorMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CalculatorMainWindow)
{
	ui->setupUi(this);

	/*初始化数据*/
	equation = equation_for_show = "0";
	ui->bottom_output->setText(equation_for_show);
	ui->top_output->setMaxLength(MAX_TOP_LENGTH);
	ui->bottom_output->setMaxLength(MAX_BOTTOM_LENGTH);
	last_num = 0;
	last_sig = '+';
	last_result = 0;

	/*QSS设置*/
	setStyleSheet(
				"QMainWindow{background-color: rgb(76,74,72);}"
				"QPushButton{border:1px hidden;border-radius:10px;padding:2px 4px;color:rgb(200,200,200);font-size:25px;}"
				"QPushButton:hover{background-color: rgb(136,134,132);}"
				"QPushButton:pressed{border:1px inset rgb(106,104,102);font-size: 23px}"
				"#output_frame{background-color: rgb(106,104,102);border:1px solid gray;border-radius:20px;padding: 2px 10px;}"
				"#top_output,#bottom_output{background: transparent;}"
				"#top_output{color:rgb(190,190,190);}"
				);

	/*槽关联*/
	connect(ui->clearButton,&QPushButton::clicked,this,clear);
	connect(ui->backspaceButton,&QPushButton::clicked,this,backspace);
	connect(ui->button0,&QPushButton::clicked,this,input_0);
	connect(ui->button1,&QPushButton::clicked,this,input_1);
	connect(ui->button2,&QPushButton::clicked,this,input_2);
	connect(ui->button3,&QPushButton::clicked,this,input_3);
	connect(ui->button4,&QPushButton::clicked,this,input_4);
	connect(ui->button5,&QPushButton::clicked,this,input_5);
	connect(ui->button6,&QPushButton::clicked,this,input_6);
	connect(ui->button7,&QPushButton::clicked,this,input_7);
	connect(ui->button8,&QPushButton::clicked,this,input_8);
	connect(ui->button9,&QPushButton::clicked,this,input_9);
	connect(ui->plusButton,&QPushButton::clicked,this,input_plus);
	connect(ui->minusButton,&QPushButton::clicked,this,input_minus);
	connect(ui->timeButton,&QPushButton::clicked,this,input_times);
	connect(ui->devideButton,&QPushButton::clicked,this,input_divide);
	connect(ui->pointButton,&QPushButton::clicked,this,input_point);
	connect(ui->leftButton,&QPushButton::clicked,this,input_left);
	connect(ui->rightButton,&QPushButton::clicked,this,input_right);
	connect(ui->equalButton,&QPushButton::clicked,this,equal);
}

CalculatorMainWindow::~CalculatorMainWindow()
{
	delete ui;
}

void CalculatorMainWindow::clear_top() const
{
	ui->top_output->setText("");
}

void CalculatorMainWindow::bottom_append(QString c)
{
	equation_for_show += c;
	equation += c;
	ui->bottom_output->setText(equation_for_show);
}

void CalculatorMainWindow::inherit_last_result()
{
	if(equation == "0")
	{
		equation = QString::number(last_result,'g',PRECISION);
		equation_for_show = QString::number(last_result,'g',PRECISION);
	}
}

void CalculatorMainWindow::check_erase_0()
{
	if(equation == "0" || (equation[equation.size()-1] == '0'&&isSignal(equation[equation.size()-2])))
	{
		equation_for_show.resize(equation.size()-1);
		equation.resize(equation.size()-1);
	}
}

void CalculatorMainWindow::check_erase_signal()
{
	if(isSignal(equation[equation.size()-1]))
	{
		equation_for_show.resize(equation.size()-1);
		equation.resize(equation.size()-1);
	}
}

void CalculatorMainWindow::check_erase_point()
{
	if(equation[equation.size()-1] == '.')
		backspace();
}

void CalculatorMainWindow::clear()
{
	clear_equation();
	ui->bottom_output->setText(equation_for_show);
	clear_top();

	last_num = 0;
	last_sig = '+';
	last_result = 0;
}

void CalculatorMainWindow::clear_equation()
{
	equation = "0";
	equation_for_show = "0";
}

void CalculatorMainWindow::backspace()
{
	if(equation.size()>1)
	{
		equation_for_show.resize(equation.size()-1);
		equation.resize(equation.size()-1);
		ui->bottom_output->setText(equation_for_show);
	}
	else if(equation.size()==1)
	{
		equation=equation_for_show= "0";
		ui->bottom_output->setText(equation_for_show);
	}
}

void CalculatorMainWindow::input_0()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	for(int i=equation.size()-1;i>=0;i--)
	{
		if(i == 0 && equation != "0")//只有一个运算数且不是0
		{
			bottom_append("0");
			break;
		}
		else if(equation[i] == '.')//如果前面有小数点，则无条件允许输入
		{
			bottom_append("0");
			break;
		}
		else if(isSignal(equation[i]))//遇到运算符
		{
			if(equation[i+1] != '0')//运算符后面的第一个数不为0则可以输入0
			{
				bottom_append("0");
				break;
			}
		}
	}
}

void CalculatorMainWindow::input_1()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	check_erase_0();
	clear_top();
	bottom_append("1");
}

void CalculatorMainWindow::input_2()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	check_erase_0();
	clear_top();
	bottom_append("2");
}

void CalculatorMainWindow::input_3()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	check_erase_0();
	clear_top();
	bottom_append("3");
}

void CalculatorMainWindow::input_4()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	check_erase_0();
	clear_top();
	bottom_append("4");
}

void CalculatorMainWindow::input_5()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	check_erase_0();
	clear_top();
	bottom_append("5");
}

void CalculatorMainWindow::input_6()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	check_erase_0();
	clear_top();
	bottom_append("6");
}

void CalculatorMainWindow::input_7()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	check_erase_0();
	clear_top();
	bottom_append("7");
}

void CalculatorMainWindow::input_8()
{

	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	check_erase_0();
	clear_top();
	bottom_append("8");
}

void CalculatorMainWindow::input_9()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	check_erase_0();
	clear_top();
	bottom_append("9");
}

void CalculatorMainWindow::input_plus()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	inherit_last_result();
	check_erase_signal();
	check_erase_point();
	if(equation == "0")//充当正负号
	{
		equation.clear();
		equation_for_show.clear();
	}
	clear_top();
	bottom_append("+");
}

void CalculatorMainWindow::input_minus()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	inherit_last_result();
	check_erase_signal();
	check_erase_point();
	if(equation == "0")//充当正负号
	{
		equation.clear();
		equation_for_show.clear();
	}
	clear_top();
	bottom_append("-");
}

void CalculatorMainWindow::input_times()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	inherit_last_result();
	check_erase_signal();
	check_erase_point();
	clear_top();
	equation_for_show += "×";
	equation += "*";
	ui->bottom_output->setText(equation_for_show);
}

void CalculatorMainWindow::input_divide()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	inherit_last_result();
	check_erase_signal();
	check_erase_point();
	clear_top();
	equation_for_show += "÷";
	equation += "/";
	ui->bottom_output->setText(equation_for_show);
}

void CalculatorMainWindow::input_point()
{
	inherit_last_result();
	for(int i=equation.size()-1;i>=0;i--)//检测当前数中是否已经有了小数点
		if(equation[i] == '.')//如果有，不响应
			return;
		else if(isSignal(equation[i]))//如果遇到运算符或者到0，则可以继续
			break;

	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	else if(equation.size() == 0)
	{
		equation_for_show += "0";
		equation+="0";
	}
	else if(equation[equation.size()-1]>'9' || equation[equation.size()-1]<'0' || isSignal(equation[equation.size()-1]))
	{
		equation_for_show += "0";
		equation+="0";
	}
	clear_top();
	equation_for_show += ".";
	equation += ".";
	ui->bottom_output->setText(equation_for_show);
}

void CalculatorMainWindow::input_left()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	inherit_last_result();
	check_erase_0();
	clear_top();
	equation_for_show += "(";
	equation += "(";
	ui->bottom_output->setText(equation_for_show);
}

void CalculatorMainWindow::input_right()
{
	if(equation.size() == MAX_BOTTOM_LENGTH)
		return;
	inherit_last_result();
	if(equation == "0")
	{
		equation_for_show.resize(equation.size()-1);
		equation.resize(equation.size()-1);
	}
	else if(equation_for_show[equation.size()-1] == '(')
	{
		equation_for_show += "0";
		equation += "0";
	}
	clear_top();
	equation_for_show += ")";
	equation += ")";
	ui->bottom_output->setText(equation_for_show);
}

void CalculatorMainWindow::keyPressEvent(QKeyEvent * e)
{
	switch(e->key())
	{
		case '0':
		{
			input_0();
			break;
		}
		case '1':
		{
			input_1();
			break;
		}
		case '2':
		{
			input_2();
			break;
		}
		case '3':
		{
			input_3();
			break;
		}
		case '4':
		{
			input_4();
			break;
		}
		case '5':
		{
			input_5();
			break;
		}
		case '6':
		{
			input_6();
			break;
		}
		case '7':
		{
			input_7();
			break;
		}
		case '8':
		{
			input_8();
			break;
		}
		case '9':
		{
			input_9();
			break;
		}
		case '+':
		{
			input_plus();
			break;
		}
		case '-':
		{
			input_minus();
			break;
		}
		case '*':
		{
			input_times();
			break;
		}
		case '/':
		{
			input_divide();
			break;
		}
		case '.':
		{
			input_point();
			break;
		}
		case 16777220:
		case 16777221:
		{
			equal();
			break;
		}
		case 16777219:
		{
			backspace();
			break;
		}
		case '(':
		{
			input_left();
			break;
		}
		case ')':
		{
			input_right();
			break;
		}
	}
}

double CalculatorMainWindow::calculate(QString & equation)
{
	const QChar TIMES = '*';
	const QChar DIVIDE ='/';
	const QChar PLUS = '+';
	const QChar MINUS = '-';
	/*查找是否有省略乘号情况*/
	int pos = 0;
	while (pos != -1)
	{
		if (pos > 0)
			if ((equation[pos - 1] >= '0' && equation[pos - 1] <= '9') || equation[pos - 1] == ')')
			{
				equation.insert(pos, '*');
				pos += 2;
			}
		pos++;
		pos = equation.indexOf('(', pos);
	}
	pos = 0;
	while (pos != -1)
	{
		if (pos > 0 && pos<equation.size() - 1)
			if ((equation[pos + 1] >= '0' && equation[pos + 1] <= '9') || equation[pos + 1] == '(')
			{
				equation.insert(pos+1, '*');
				pos += 2;
			}
		pos++;
		pos = equation.indexOf(')', pos);
	}

	/*缺失最后一个操作数则抛出错误*/
	if(isSignal(equation[equation.size()-1]))
		throw "缺少运算数";

	/*如果只输入小数点没有小数，则认为没有输入小数点*/
	check_erase_point();

	/*如果第一个字符为+则去掉*/
	if(equation[0] == '+')
	{
		equation.remove(0,1);
		equation_for_show.remove(0,1);
	}

	/*根据算式中是否还有括号判断不同的路径*/
	auto first_left = equation.indexOf('(');
	auto last_right = equation.lastIndexOf(')');
	if (first_left == last_right)//如果算式当中已经没有括号
	{
		double result;
		double num1, num2, temp_result;
		QVector<QChar> sigs;
		QVector<double> nums;
		QString current_num;
		for (auto i : equation)
			if (i == TIMES || i == DIVIDE || i == PLUS || i == MINUS)
			{
				if (current_num.size() == 0)
				{
					if (i == PLUS || i == MINUS)
						current_num.push_back(i);
					else
						throw "运算符错误";
				}
				else
				{
					sigs.push_back(i);
					nums.push_back(current_num.toDouble());
					current_num.clear();
				}
			}
			else if ((i >= '0'&&i <= '9') || i == '.')
			{
				current_num += i;
			}
		nums.push_back(current_num.toDouble());//最后一个数

		for (int i = 0; i < sigs.size(); i++)
		{
			if (sigs[i] == TIMES)
			{
				num1 = nums[i];
				num2 = nums[i + 1];
				temp_result = num1*num2;
				last_num = nums[i+1];
				last_sig = sigs[i];
				nums.remove(i, 2);
				sigs.remove(i);
				nums.insert(nums.begin() + i, temp_result);
				i--;
			}
			else if (sigs[i] == DIVIDE)
			{
				num1 = nums[i];
				num2 = nums[i + 1];
				temp_result = num1 / num2;
				last_num = nums[i+1];
				last_sig = sigs[i];
				nums.remove(i, 2);
				sigs.remove(i);
				nums.insert(nums.begin() + i, temp_result);
				i--;
			}
		}
		result = nums[0];
		for (int i = 0; i < nums.size() - 1; i++)
			if (sigs[i] == PLUS)
				result += nums[i + 1];
			else if (sigs[i] == MINUS)
				result -= nums[i + 1];
		if(nums.size()>1)//如果还有加减法运算
		{
			last_num = nums[nums.size() - 1];//记录最后一个操作数
			last_sig = sigs[nums.size() - 2];//记录最后一个操作运算符
		}
		return result;
	}
	else if (first_left == -1)//括号不配对情况
	{
		//equation.remove(equation.lastIndexOf(')'), 1);
		throw "括号不成对";
	}
	else if (last_right == -1)
	{
		//equation.remove(equation.indexOf('('), 1);
		throw "括号不成对";
	}
	else//抹掉括号
	{
		int left, right, left_2, right_2;
		left = equation.indexOf('(');
		right = equation.lastIndexOf(')');
		left_2 = equation.lastIndexOf('(');
		right_2 = equation.indexOf(')');
		if (left_2 >= left && right_2 <= right && left_2 < right_2)//只有嵌套括号
		{
			QString sub_str = equation.mid(first_left + 1, last_right - first_left - 1);
			double sub_result = calculate(sub_str);
			equation.replace(first_left, last_right - first_left + 1, QString::number(sub_result,'g',PRECISION));
			return calculate(equation);
		}
		else//有分离括号
		{
			left = equation.lastIndexOf('(');//找到最右边的左括号
			right = equation.mid(left, equation.size()).indexOf(')') + left;//最右边的左括号后的最左边的右括号
			//此时left和right之间有单位算式
			QString sub_str = equation.mid(left + 1, right - left - 1);
			double sub_result = calculate(sub_str);
			equation.replace(left, right - left + 1, QString::number(sub_result,'g',PRECISION));
			return calculate(equation);
		}
	}
}

void CalculatorMainWindow::equal()
{
	double result = 0;
	try{
		if(equation != "0")
		{
			result = calculate(equation);
			ui->bottom_output->setText(QString::number(result ,'g',PRECISION));
			ui->top_output->setText(equation_for_show + "=");
			clear_equation();
			last_result = result;
		}
		else
		{
			clear_top();
			if(last_sig == '+')
			{
				last_result+=last_num;
			}
			else if(last_sig == '-')
			{
				last_result-=last_num;
			}
			else if(last_sig == '*')
			{
				last_result*=last_num;
			}
			else if(last_sig == '/')
			{
				last_result/=last_num;
			}
			ui->top_output->setText(QString("PREV")+last_sig+QString::number(last_num,'g',PRECISION));
			ui->bottom_output->setText(QString::number(last_result,'g',PRECISION));
		}
	}
	catch(const char * c)
	{
		ui->bottom_output->setText(QString(c));
		clear_equation();
	}
}

static bool isSignal(QChar c)
{
	return (c=='+'||c=='-'||c=='*'||c=='/');
}
