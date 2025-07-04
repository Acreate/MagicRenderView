﻿#ifndef INTWIDGET_H_H_HEAD__FILE__
#define INTWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class QLineEdit;
class IntTypeObject;
class IntWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< IntTypeObject > value;
	QLineEdit *lineEdit;
public:
	IntWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );
	virtual int64_t getInt( ) const;
	virtual void setInt( const int64_t &new_value );
	virtual void setFloat( const double &new_value ) {
		setInt( ( int64_t ) new_value );
	}
	virtual void setFloat( const float &new_value ) {
		setInt( ( int64_t ) new_value );
	}
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;
	std_shared_ptr< ITypeObject > getValue( ) const override;
	bool setValue( const std_shared_ptr< ITypeObject > &value ) const override;
};

#endif // INTWIDGET_H_H_HEAD__FILE__
