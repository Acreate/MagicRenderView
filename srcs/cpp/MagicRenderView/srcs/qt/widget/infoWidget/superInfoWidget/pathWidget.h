#ifndef PATHWIDGET_H_H_HEAD__FILE__
#define PATHWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class QLineEdit;
class StringTypeObject;
class PathWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< StringTypeObject > stringTypeObject;
	QLineEdit *pathText;
	QLineEdit *appendPathText;
public:
	PathWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );
	QString getText( ) const override;
	void setText( const QString &new_text ) const override;
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;
	std_shared_ptr<ITypeObject> getValue( ) const override;
	void setValue( const std_shared_ptr< ITypeObject > &value ) const override;
Q_SIGNALS:
	/// @brief 路径修改完毕之后触发该信号
	/// @param path 路径
	void pathChanged( const QString &path );
	/// @brief 路径追加名称后触发该信号
	/// @param path 追加路径
	void pathAppendNameChanged( const QString &path );

};

#endif // PATHWIDGET_H_H_HEAD__FILE__
