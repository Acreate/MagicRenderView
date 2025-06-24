#ifndef VECTORWIDGET_H_H_HEAD__FILE__
#define VECTORWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class VectorWidget : public IInfoWidget{
	Q_OBJECT;
public:
	VectorWidget( const std_function<std_shared_ptr<IInfoWidgetStack>()> &get_stack_function, QWidget *parent, const QString &title_msg );
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;
	
};

#endif // VECTORWIDGET_H_H_HEAD__FILE__
