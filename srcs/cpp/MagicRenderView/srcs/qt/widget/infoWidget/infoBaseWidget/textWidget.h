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
	TextWidget( QWidget *parent, const QString &title_msg );
	virtual QString getText( ) const;
	virtual void setText( const QString &new_text ) const;
	virtual void setTitle( const QString &new_title ) const;
	virtual void setPlaceholderText( const QString &placeholder_text ) const;
	virtual QString getPlaceholderText( ) const;
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
