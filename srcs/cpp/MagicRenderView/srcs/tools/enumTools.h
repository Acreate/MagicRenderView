#ifndef ENUMTOOLS_H_H_HEAD__FILE__
#define ENUMTOOLS_H_H_HEAD__FILE__

#include <QMetaEnum>
namespace EnumTools {

	template< typename TNodeEnum >
	bool converToEnum( const QString &enum_string, TNodeEnum &result_enum_type_var ) {
		QMetaEnum metaEnum = QMetaEnum::fromType< TNodeEnum >( );
		auto optional = metaEnum.keyToValue64( enum_string.toLocal8Bit( ) );
		if( optional.has_value( ) == false )
			return false;
		auto *varPtr = optional.operator->( );
		result_enum_type_var = ( TNodeEnum ) *varPtr;
		return true;
	}

	template< typename TNodeEnum >
	bool converToString( const TNodeEnum &enum_type_var, QString &result_enum_string ) {
		QMetaEnum metaEnum = QMetaEnum::fromType< TNodeEnum >( );
		quint64 var;
		if constexpr( sizeof( TNodeEnum ) == sizeof( quint64 ) )
			var = ( quint64 ) enum_type_var;
		else if constexpr( sizeof( TNodeEnum ) == sizeof( quint32 ) )
			var = ( quint32 ) enum_type_var;
		else if constexpr( sizeof( TNodeEnum ) == sizeof( quint16 ) )
			var = ( quint16 ) enum_type_var;
		else if constexpr( sizeof( TNodeEnum ) == sizeof( quint8 ) )
			var = ( quint8 ) enum_type_var;
		else
			return false;
		int keyCount = metaEnum.keyCount( );
		int index = 0;
		for( ; index < keyCount; ++index )
			if( metaEnum.value64( index ) == var ) {
				result_enum_string = QString::fromLocal8Bit( metaEnum.valueToKey( index ) );
				return true;
			}
		return false;
	}
}

#endif // ENUMTOOLS_H_H_HEAD__FILE__
