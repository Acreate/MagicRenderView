#include "I_Serialization‌.h"

#include "I_Type.h"

#include "../application/application.h"

#define emplaceTypeMap( type, ... ) \
	typeMap.emplace_back( typeid( type ), std_vector< QString > { typeid( type ).name(  ),#type, __VA_ARGS__ } );

I_Serialization‌::I_Serialization‌( const type_info &set_type_info ) : typeInfo( set_type_info ) {

	applicationInstancePtr = Application::getApplicationInstancePtr( );

	varInstance = applicationInstancePtr->getVarGenerate( );
	emplaceTypeMap( uint8_t );
	emplaceTypeMap( uint16_t );
	emplaceTypeMap( uint32_t );
	emplaceTypeMap( uint64_t );
	emplaceTypeMap( int8_t );
	emplaceTypeMap( int16_t );
	emplaceTypeMap( int32_t );
	emplaceTypeMap( int64_t );
	emplaceTypeMap( QString );
	emplaceTypeMap( std::string );
	emplaceTypeMap( std::wstring );
	emplaceTypeMap( float, "float32", "float_" );
	emplaceTypeMap( double, "float64", "double_" );
}
bool I_Serialization‌::getTypeInfo( const QString &type_name, I_Type *result_type ) const {
	size_t count = typeMap.size( );
	if( count == 0 )
		return false;
	auto data = typeMap.data( );
	for( size_t index = 0; index < count; ++index )
		for( auto &item : data[ index ].second )
			if( item == type_name ) {
				*result_type = I_Type( data[ index ].first, result_type->getPtr( ), result_type->getDeleteVarPtr( ) );
				return true;
			}
	return false;
}
