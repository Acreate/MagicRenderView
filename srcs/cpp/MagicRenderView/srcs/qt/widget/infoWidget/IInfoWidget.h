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
	std_function< bool( ITypeObject * ) > checkObj;
	std_shared_ptr< IInfoWidgetStack > infoWidgetSharedStack;
	std_shared_ptr< ITypeObject > synObjPtr;
	std_function< std_shared_ptr< IInfoWidgetStack > ( ) > getStackFunction;
protected:
	QLabel *title;
	QVBoxLayout *mainLayout;
public:
	IInfoWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );
	virtual QString getTitle( ) const;
	virtual void setTitle( const QString &new_title ) const;
	virtual void setPlaceholderText( const QString &placeholder_text ) const;
	virtual QString getPlaceholderText( ) const;
	virtual const std_function< bool( ITypeObject * ) > & getCheckObj( ) const { return checkObj; }
	virtual void setCheckObj( const std_function< bool( ITypeObject * ) > &check_obj ) { checkObj = check_obj; }
	/// @brief 获取创建该变量的堆栈对象指针
	/// @return 创建该变量的堆栈对象指针
	virtual std_shared_ptr< IInfoWidgetStack > getStack( ) const {
		if( getStackFunction )
			return getStackFunction( );
		return nullptr;
	}
	virtual std_shared_ptr< ITypeObject > getValue( ) const;
	virtual bool setValue( const std_shared_ptr< ITypeObject > &value ) const { return false; }
	virtual void setSynObj( const std_shared_ptr< ITypeObject > &value ) {
		synObjPtr = value;
	}
	virtual std_shared_ptr< ITypeObject > getSynObj( ) const {
		return synObjPtr;
	}
protected:
	void paintEvent( QPaintEvent *event ) override;
Q_SIGNALS:
	/// @brief 值修改完毕会触发该信号
	void valueChanged( );
};

#endif // IINFOWIDGET_H_H_HEAD__FILE__
