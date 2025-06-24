#include "./hexEditor.h"

#include <qevent.h>

#include "../../../../serialize/ISerialize.h"
HexEditor::HexEditor( QWidget *parent ) : QTextEdit( parent ) {
}

bool HexEditor::setHex( const QByteArray &hex_text ) {
	currentText = hex_text;
	setText( hex_text );
	update( );
	auto count = currentText.length( );
	auto cursor = textCursor( );
	cursor.setPosition( count );
	setTextCursor( cursor );
	return true;
}

template< typename TData_type >
	requires requires ( const TData_type &t_data, char d_data ) {
		sizeof( d_data ) == sizeof( t_data );
	}
bool copyToQByteArray( const std_vector< TData_type > &source_vector, QByteArray &dest_byte_Array ) {
	size_t qsizetype = source_vector.size( );
	const TData_type *copySource = source_vector.data( );
	QStringList stringList;
	for( size_t index = 0; index < qsizetype; ++index )
		stringList.append( QString( "%1" ).arg( ( int ) ( copySource[ index ] ), 2, 16, QLatin1Char( '0' ) ) );
	QString string = stringList.join( "" );
	dest_byte_Array = string.toUpper( ).toUtf8( );
	return true;
}

bool HexEditor::setHex( const std_vector< uchar > &data_vector ) {
	QByteArray byteArray;
	if( copyToQByteArray( data_vector, byteArray ) )
		setHex( byteArray );
	else
		return false;
	return true;
}
bool HexEditor::setHex( const std_vector< char > &data_vector ) {
	QByteArray byteArray;
	if( copyToQByteArray( data_vector, byteArray ) )
		setHex( byteArray );
	else
		return false;
	return true;
}
bool HexEditor::setHex( const int64_t &number_value ) {
	return setHex( ISerialize::toData( number_value ) );
}
bool HexEditor::setHex( const double &number_value ) {
	return setHex( ISerialize::toData( number_value ) );
}
std_vector< uchar > HexEditor::toUcharVector( bool mod_is_suffix_data_var ) const {
	std_vector< uchar > result;
	qsizetype count = currentText.size( );
	if( count == 0 )
		return result;
	auto dataPtr = currentText.data( );
	qint64 newSize = count / 2;
	QString buff;
	buff.resize( 2 );
	auto converDataPtr = buff.data( );
	bool isToOk = false;
	uint uInt;
	qint64 getDataPtrIndex;
	for( decltype(count) index = 0; index < newSize; ++index ) {
		getDataPtrIndex = index * 2;
		converDataPtr[ 0 ] = dataPtr[ getDataPtrIndex ];
		converDataPtr[ 1 ] = dataPtr[ getDataPtrIndex + 1 ];
		uInt = buff.toUInt( &isToOk, 16 );
		if( isToOk == false ) {
			tools::debug::printError( "无法转换到数据类型，请使用 toString 进行字面量获取，并且检查返回字符串" );
			result.clear( );
			return result;
		}
		result.emplace_back( uInt );
	}
	newSize = count % 2;
	// 处理多余的字符
	if( newSize == 1 )
		if( mod_is_suffix_data_var ) {
			converDataPtr[ 0 ] = '0';
			converDataPtr[ 1 ] = dataPtr[ count - 1 ];
			uInt = buff.toUInt( &isToOk, 16 );
			if( isToOk == false ) {
				tools::debug::printError( "无法转换到数据类型，请使用 toString 进行字面量获取，并且检查返回字符串" );
				result.clear( );
				return result;
			}
			result.emplace_back( uInt );
		} else {
			converDataPtr[ 1 ] = '0';
			converDataPtr[ 0 ] = dataPtr[ count - 1 ];
			uInt = buff.toUInt( &isToOk, 16 );
			if( isToOk == false ) {
				tools::debug::printError( "无法转换到数据类型，请使用 toString 进行字面量获取，并且检查返回字符串" );
				result.clear( );
				return result;
			}
			result.emplace_back( uInt );
		}
	return result;
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
	update( );
	setTextCursor( cursor );
	return true;
}
void HexEditor::keyPressEvent( QKeyEvent *e ) {
	QString inputString = e->text( );
	inputString = inputString.trimmed( );
	if( inputString.isEmpty( ) )
		return;
	auto cursor = textCursor( );
	int anchor = cursor.anchor( );
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
	update( );
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
	else if( key == Qt::Key_Backspace ) {
		auto cursor = textCursor( );
		int anchor = cursor.anchor( );
		anchor -= 1;
		currentText.erase( currentText.begin( ) + anchor );
		setText( currentText );
		update( );
		cursor.setPosition( anchor );
		setTextCursor( cursor );
		return;
	} else if( key == Qt::Key_Left ) {
		auto cursor = textCursor( );
		int anchor = cursor.anchor( );
		anchor -= 1;
		cursor.setPosition( anchor );
		setTextCursor( cursor );
		return;
	} else if( key == Qt::Key_Right ) {
		auto cursor = textCursor( );
		int anchor = cursor.anchor( );
		anchor += 1;
		qsizetype count = currentText.size( ) + 1; // 指向末尾
		if( anchor == count )
			return;
		cursor.setPosition( anchor );
		setTextCursor( cursor );
		return;
	}
}
