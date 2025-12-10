#ifndef GENERATEITEMWIDGET_H_H_HEAD__FILE__
#define GENERATEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>
class QLineEdit;
class QPushButton;
class QLabel;
class GenerateItemWidget : public QWidget {
	Q_OBJECT;
public:
	QLabel *showIndexInfo;
	QLineEdit *editorVarInfo;
	QPushButton *removeButton;
	QPushButton *changeButton;
	QPushButton *restoryButton;
	QString infoFormmattion;
	size_t index;
	QString varValue;
protected:
	virtual void updateInfoString( );
public:
	GenerateItemWidget( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void setInfo( const size_t &index, const QString &var_value );
Q_SIGNALS:
	/// @brief 点击删除时发生该信号
	/// @param signal_ptr 信号对象指针
	/// @param index 当前序列号
	/// @param var_value 当前值
	void clickRemoveItemBtn( GenerateItemWidget *signal_ptr, const size_t &index, const QString &var_value );
	/// @brief 点击更改变量发生信号
	/// @param signal_ptr 信号对象指针
	/// @param index 当前序列号
	/// @param old_var_value 旧值
	/// @param new_var_value 新值
	void changeVar( GenerateItemWidget *signal_ptr, const size_t &index, const QString &old_var_value, const QString &new_var_value );
	/// @brief 点击还原变量发生信号
	/// @param signal_ptr 信号对象指针
	/// @param index 当前序列号
	/// @param restory_var_value 还原值
	/// @param current_var_value 当前值
	void restoryVar( GenerateItemWidget *signal_ptr, const size_t &index, const QString &restory_var_value, const QString &current_var_value );
};

#endif // GENERATEITEMWIDGET_H_H_HEAD__FILE__
