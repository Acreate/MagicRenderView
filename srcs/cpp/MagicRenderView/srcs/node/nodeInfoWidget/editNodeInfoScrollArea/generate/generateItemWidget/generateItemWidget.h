#ifndef GENERATEITEMWIDGET_H_H_HEAD__FILE__
#define GENERATEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QLabel;
class GenerateItemWidget : public QWidget {
	Q_OBJECT;
public:
	QLabel *showIndexInfo;
	QLabel *dragLabel;
	QLineEdit *editorVarInfo;
	QMenu *managementMenu;
	QString infoFormmattion;
	size_t index;
	QString varValue;
	QHBoxLayout *mainLayout;
	QMenu *popMenu;
public:
	GenerateItemWidget( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void setInfo( const size_t &index, const QString &var_value );
	virtual bool isDragWidgetPos( const QPoint &pos );
	virtual QMenu * getPopMenu( ) const { return popMenu; }
Q_SIGNALS:
	/// @brief 点击删除时发生该信号
	/// @param signal_ptr 信号对象指针
	void removeVar( GenerateItemWidget *signal_ptr );
	/// @brief 点击更改变量发生信号
	/// @param signal_ptr 信号对象指针
	void changeVar( GenerateItemWidget *signal_ptr );
	/// @brief 点击还原变量发生信号
	/// @param signal_ptr 信号对象指针
	void restoryVar( GenerateItemWidget *signal_ptr );
};

#endif // GENERATEITEMWIDGET_H_H_HEAD__FILE__
