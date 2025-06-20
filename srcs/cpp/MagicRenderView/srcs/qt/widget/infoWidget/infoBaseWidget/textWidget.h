#ifndef TEXTWIDGET_H_H_HEAD__FILE__
#define TEXTWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "../IInfoWidget.h"

class QLineEdit;
class QLabel;
class TextWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	QLineEdit *edit;
public:
	TextWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );
	TextWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg , const QString& placeholder_text);
	QString getText( ) const override;
	void setText( const QString &new_text ) const override;
	void setTitle( const QString &new_title ) const override;
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;
Q_SIGNALS:
	void cursorPositionChanged( int oldPos, int newPos );
	void editingFinished( );
	void inputRejected( );
	void returnPressed( );
	void selectionChanged( );
	void textChanged( const QString &text );
	void textEdited( const QString &text );

};

#endif // TEXTWIDGET_H_H_HEAD__FILE__
