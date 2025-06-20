#ifndef IINFOWIDGET_H_H_HEAD__FILE__
#define IINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

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
};

#endif // IINFOWIDGET_H_H_HEAD__FILE__
