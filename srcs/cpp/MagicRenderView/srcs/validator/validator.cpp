#include "validator.h"
QValidator::State Validator::validate( QString &input, int &pos ) const {
	qsizetype len = pos;
	auto data = input.data( );
	qsizetype index = 0;
	qsizetype buffIndex;
	QChar *buff;
	for( ; index < len; ++index )
		if( checkCharValidator( data[ index ] ) == false ) {
			pos = index;
			len = input.size( );
			if( len > maxLen )
				len = maxLen;
			index = 0;
			buff = new QChar[ len ];
			buffIndex = 0;
			for( ; index < len; ++index )
				if( checkCharValidator( data[ index ] ) == false )
					continue;
				else {
					buff[ buffIndex ] = data[ index ];
					++buffIndex;
				}
			input = QString( buff, buffIndex );
			delete [] buff;
			break;
		}
	return Acceptable;
}
