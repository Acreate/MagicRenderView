#ifndef STRINGWIDGET_H_H_HEAD__FILE__
#define STRINGWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class QHBoxLayout;
class StringTypeObject;
class QTextEdit;
class StringWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	QTextEdit *textEdit;
	std_shared_ptr< StringTypeObject > editString;
public:
	StringWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );
	~StringWidget( ) override;
	virtual QString getText( ) const;
	virtual bool setText( const QString &new_text ) const;
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;
	std_shared_ptr< ITypeObject > getValue( ) const override;
	bool setValue( const std_shared_ptr< ITypeObject > &value ) const override;
};

#endif // STRINGWIDGET_H_H_HEAD__FILE__
