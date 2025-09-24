#include "./intToString.h"

#include <QList>
#include <QString>
#include <cstdint>

#include "../../I_Type.h"
bool IntToString::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	ChackNeedType( QString, stringVar, int64_t, intVar );

	*stringVar = stringVar->number( *intVar );
	return true;
}
bool IntToString::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( QString, stringVar, int64_t, intVar );

	stringVar->append( stringVar->number( *intVar ) );
	return true;
}
bool IntToString::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( QString, stringVar, int64_t, intVar );
	QString number = stringVar->number( *intVar );
	if( stringVar->endsWith( number ) == false )
		return true;
	*stringVar = stringVar->mid( 0, stringVar->size( ) - number.size( ) );
	return true;
}
bool IntToString::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( QString, stringVar, int64_t, intVar );

	int64_t var = *intVar;
	QStringList strBuff( var, *stringVar );

	*stringVar = strBuff.join( "" );

	return true;
}
bool IntToString::devTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( QString, stringVar, int64_t, intVar );
	*stringVar = stringVar->split( stringVar->number( *intVar ) ).join( "" );
	return true;
}
