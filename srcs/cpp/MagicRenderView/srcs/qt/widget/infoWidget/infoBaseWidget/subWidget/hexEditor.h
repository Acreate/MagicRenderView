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
	virtual const QString & getCurrentHexText( ) const { return currentText; }
	virtual bool setString( const QString &hex_text );
	virtual bool setHex( const QByteArray &hex_text );
	
	virtual bool setHex( const std_vector<uchar> &data_vector );
	virtual bool setHex( const std_vector<char> &data_vector );
	virtual bool setHex( const int64_t &number_value ) ;
	virtual bool setHex( const double &number_value );
protected:
	void keyPressEvent( QKeyEvent *e ) override;
	void leaveEvent( QEvent *event ) override;
	void focusOutEvent( QFocusEvent *e ) override;
	void keyReleaseEvent( QKeyEvent *e ) override;
Q_SIGNALS:
	void editorFinish( const QString &text );
};

#endif // HEXEDITOR_H_H_HEAD__FILE__
