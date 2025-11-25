#include "typeEnum.h"

#include <QMetaEnum>
bool TypeEnum::converEnum( const QString &enum_string, Type &result_enum_type_var ) {
	QMetaEnum metaEnum = QMetaEnum::fromType< Type >( );
	auto optional = metaEnum.keyToValue64( enum_string.toLocal8Bit( ) );
	if( optional.has_value( ) == false )
		return false;
	auto *varPtr = optional.operator->( );
	result_enum_type_var = ( Type ) *varPtr;
	switch( result_enum_type_var ) {
		case Type::Unity :
		case Type::Array :
		case Type::Struct :
		case Type::Pair :
			break;
		default :
			return false;
	}
	return true;
}
bool TypeEnum::converQString( const Type &enum_type_var, QString &result_enum_string ) {
	switch( enum_type_var ) {
		case Type::Unity :
			result_enum_string = "Unity";
			break;
		case Type::Array :
			result_enum_string = "Array";
			break;
		case Type::Struct :
			result_enum_string = "Struct";
			break;
		case Type::Pair :
			result_enum_string = "Pair";
			break;
		default :
			return false;
	}
	return true;
}
