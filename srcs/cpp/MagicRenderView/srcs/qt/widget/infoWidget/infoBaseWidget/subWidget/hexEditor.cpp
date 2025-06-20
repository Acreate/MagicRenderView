﻿#include "./hexEditor.h"

#include <qevent.h>
HexEditor::HexEditor( QWidget *parent ) : QTextEdit( parent ) {
}

void HexEditor::setHex( const QByteArray &hex_text ) {
	currentText = hex_text;
	auto cursor = textCursor( );
	cursor.setPosition( currentText.length( ) );
	setText( hex_text );
	setTextCursor( cursor );
}
bool HexEditor::setString( const QString &hex_text ) {
	auto count = hex_text.length( );
	auto qchar = hex_text.data( );
	QChar zeroChar = '0';
	QChar overstepNumberChar = QChar( '9' + 1 );
	QChar aChar = 'A';
	QChar fChar = 'F';
	for( decltype(count) index = 0; index < count; ++index ) {
		QChar checkChar = qchar[ index ];
		if( checkChar < zeroChar )
			return false;
		if( checkChar < overstepNumberChar )
			continue;
		auto upper = checkChar.toUpper( );
		if( upper < aChar || upper > fChar )
			return false;
	}
	currentText = hex_text;
	auto cursor = textCursor( );
	cursor.setPosition( count );
	setText( hex_text );
	setTextCursor( cursor );
	return true;
}
void HexEditor::keyPressEvent( QKeyEvent *e ) {
	auto cursor = textCursor( );
	int anchor = cursor.anchor( );
	QString inputString = e->text( );
	bool isOk = false;
	auto converInt = inputString.toInt( &isOk );
	if( !isOk ) {
		auto upper = inputString.toUpper( )[ 0 ];
		if( upper < 'A' || upper > 'F' )
			return;
		// 字母
		currentText.insert( anchor, upper );
	} else // 数字
		currentText.insert( anchor, QString::number( converInt ) );
	setText( currentText );
	cursor.setPosition( anchor + 1 );
	setTextCursor( cursor );
}
void HexEditor::leaveEvent( QEvent *event ) {
	QTextEdit::leaveEvent( event );
	emit editorFinish( currentText );
}
void HexEditor::focusOutEvent( QFocusEvent *e ) {
	QTextEdit::focusOutEvent( e );
	emit editorFinish( currentText );
}
void HexEditor::keyReleaseEvent( QKeyEvent *e ) {
	QTextEdit::keyReleaseEvent( e );
	int key = e->key( );
	if( key == Qt::Key_Escape || key == Qt::Key_Return )
		emit editorFinish( currentText );
}
