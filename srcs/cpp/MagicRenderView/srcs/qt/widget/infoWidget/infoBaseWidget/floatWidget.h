#ifndef FLOATWIDGET_H_H_HEAD__FILE__
#define FLOATWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class FloatWidget : public IInfoWidget{
	Q_OBJECT;
public:
	FloatWidget( const std_function<std_shared_ptr<IInfoWidgetStack>()> &get_stack_function, QWidget *parent, const QString &title_msg )
		: IInfoWidget( get_stack_function, parent, title_msg ) { }
	QString getText( ) const override;
	void setText( const QString &new_text ) const override;
	void setTitle( const QString &new_title ) const override;
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;
};

#endif // FLOATWIDGET_H_H_HEAD__FILE__
