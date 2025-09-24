#include "./floatToString.h"

#include <QList>
#include <cstdint>

#include "../../I_Type.h"
bool FloatToString::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	ChackNeedType( QString, stringVar, double, doubelVar );
	*stringVar = stringVar->number( *doubelVar );
	return true;
}

bool FloatToString::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( QString, stringVar, double, doubelVar );

	stringVar->append( stringVar->number( *doubelVar ) );
	return true;
}
bool FloatToString::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( QString, stringVar, double, doubelVar );
	QString number = stringVar->number( *doubelVar );
	if( stringVar->endsWith( number ) == false )
		return true;
	*stringVar = stringVar->mid( 0, stringVar->size( ) - number.size( ) );
	return true;
}
bool FloatToString::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( QString, stringVar, double, doubelVar );

	int64_t var = ( int64_t ) *doubelVar;
	QStringList strBuff( var, *stringVar );

	*stringVar = strBuff.join( "" );

	return true;
}
bool FloatToString::devTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( QString, stringVar, double, doubelVar );
	*stringVar = stringVar->split( stringVar->number( *doubelVar ) ).join( "" );
	return true;
}
