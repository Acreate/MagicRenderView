#ifndef IINFOWIDGET_H_H_HEAD__FILE__
#define IINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class ITypeObject;
class IInfoWidgetStack;
class QVBoxLayout;
class QLabel;
class IInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< IInfoWidgetStack > infoWidgetSharedStack;
	std_function< std_shared_ptr< IInfoWidgetStack > ( ) > getStackFunction;
protected:
	QLabel *title;
	QVBoxLayout *mainLayout;
public:
	IInfoWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );
	virtual QString getTitle( ) const;

	virtual QString getText( ) const = 0;
	virtual void setText( const QString &new_text ) const = 0;
	virtual void setTitle( const QString &new_title ) const = 0;
	virtual void setPlaceholderText( const QString &placeholder_text ) const = 0;
	virtual QString getPlaceholderText( ) const = 0;

	/// @brief 获取创建该变量的堆栈对象指针
	/// @return 创建该变量的堆栈对象指针
	virtual std_shared_ptr< IInfoWidgetStack > getStack( ) const {
		if( getStackFunction )
			return getStackFunction( );
		return nullptr;
	}
	virtual const std_shared_ptr< ITypeObject > & getValue( ) const;
	virtual void setValue( const std_shared_ptr< ITypeObject > &value ) const { }
protected:
	void paintEvent( QPaintEvent *event ) override;
Q_SIGNALS:
	/// @brief 值修改完毕会触发该信号
	void valueChanged( );
};

#endif // IINFOWIDGET_H_H_HEAD__FILE__
