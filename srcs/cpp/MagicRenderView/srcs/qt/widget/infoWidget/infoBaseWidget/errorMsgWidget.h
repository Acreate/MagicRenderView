#ifndef ERRORMSGWIDGET_H_H_HEAD__FILE__
#define ERRORMSGWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../IInfoWidget.h"
class QLineEdit;
class QLabel;

class ErrorMsgWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< QString > text;
	std_shared_ptr< QString > placeholder;
public:
	ErrorMsgWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &error_msg );
	QString getText( ) const override {
		return *text;
	}
	bool setText( const QString &new_text ) const override;
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override {
		return *placeholder;
	}
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
};

#endif // ERRORMSGWIDGET_H_H_HEAD__FILE__
