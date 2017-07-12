#ifndef CALCULATORMAINWINDOW_H
#define CALCULATORMAINWINDOW_H

#include<QMainWindow>
#include<QTextEdit>

namespace Ui {
class CalculatorMainWindow;
}

class CalculatorMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit CalculatorMainWindow(QWidget *parent = 0);
	~CalculatorMainWindow();

private slots:
	void clear();//清空所有数据，重置界面显示
	void clear_equation();//清空所有内部数据，不改变界面显示
	void backspace();
	void equal();
	void input_0();
	void input_1();
	void input_2();
	void input_3();
	void input_4();
	void input_5();
	void input_6();
	void input_7();
	void input_8();
	void input_9();
	void input_point();
	void input_plus();
	void input_minus();
	void input_times();
	void input_divide();
	void input_left();
	void input_right();


private:
	Ui::CalculatorMainWindow *ui;

	const int MAX_TOP_LENGTH = 22;//上文本框最大字数
	const int MAX_BOTTOM_LENGTH = 21;//下文本框最大字数
	const int PRECISION = 10;//double转QString有效数字位数

	/*注：由于×和÷是双字节字符，在运算符类型判断的时候造成麻烦，所以分成两个*/
	QString equation_for_show;//屏幕显示算式，显示×和÷
	QString equation;//内部运算算式，显示*和/

	void keyPressEvent(QKeyEvent * e);//监控键盘按键
	double calculate(QString & equation);//主运算函数
	void clear_top() const;//清空界面上上文本框的文本，并不改变数据
	void bottom_append(QString c);//在下文本框内追加文字，改变数据
	void inherit_last_result();//继承上一次的运算结果

	double last_num;//上一次运算的最后一个运算数
	QChar last_sig;//上一次运算的最后一个运算符号
	double last_result;//上一次运算结果

	void check_erase_0();//检测是否需要覆盖0
	void check_erase_signal();//检测是否需要覆盖运算符
	void check_erase_point();//检测是否需要抹掉小数点
};

#endif // CALCULATORMAINWINDOW_H
