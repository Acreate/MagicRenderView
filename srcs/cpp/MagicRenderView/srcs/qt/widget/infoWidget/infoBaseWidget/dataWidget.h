#ifndef DATAWIDGET_H_H_HEAD__FILE__
#define DATAWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class HexEditor;
class DataTypeObject;
class QTextEdit;
class DataWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	HexEditor *edit;
	std_shared_ptr< DataTypeObject > dataTypeObject;
public:
	DataWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );
	QString getText( ) const override;
	void setText( const QString &new_text ) const override;
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;
	std_shared_ptr< ITypeObject > getValue( ) const override;
	void setValue( const std_shared_ptr< ITypeObject > &value ) const override;
};

#endif // DATAWIDGET_H_H_HEAD__FILE__
