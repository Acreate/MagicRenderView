#ifndef HEXEDITOR_H_H_HEAD__FILE__
#define HEXEDITOR_H_H_HEAD__FILE__
#pragma once
#include <QTextEdit>

#include <alias/type_alias.h>

class HexEditor : public QTextEdit {
	Q_OBJECT;
protected:
	QString currentText;
public:
	HexEditor( QWidget *parent = nullptr );
	virtual const QString & getCurrentText( ) const { return currentText; }
	virtual void setCurrentText( const QString &current_text ) { currentText = current_text; }
protected:
	void keyPressEvent( QKeyEvent *e ) override;
	void leaveEvent( QEvent *event ) override;
	void focusOutEvent( QFocusEvent *e ) override;
	void keyReleaseEvent( QKeyEvent *e ) override;
Q_SIGNALS:
	void editorFinish( const QString &text );
};

#endif // HEXEDITOR_H_H_HEAD__FILE__
