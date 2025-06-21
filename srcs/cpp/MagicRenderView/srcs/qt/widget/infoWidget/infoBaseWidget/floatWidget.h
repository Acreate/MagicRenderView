#ifndef FLOATWIDGET_H_H_HEAD__FILE__
#define FLOATWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class QLineEdit;
class FloatTypeObject;
class FloatWidget : public IInfoWidget{
	Q_OBJECT;
protected:
	std_shared_ptr<FloatTypeObject> value;
	QLineEdit* lineEdit;
public:
	FloatWidget( const std_function<std_shared_ptr<IInfoWidgetStack>()> &get_stack_function, QWidget *parent, const QString &title_msg );
	QString getText( ) const override;
	void setText( const QString &new_text ) const override;
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;
	std_shared_ptr<ITypeObject> getValue( ) const override;
	void setValue( const std_shared_ptr<ITypeObject> &value ) const override;
};

#endif // FLOATWIDGET_H_H_HEAD__FILE__
