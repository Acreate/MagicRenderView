#include "./baseVarType.h"

#include "../I_Del.h"
#include "../I_New.h"
#include "../I_Conver.h"
#include "../I_Var.h"

BaseVarType::BaseVarType( QObject *parent, const std_vector< std_shared_ptr< I_Conver > > &conver_vector, const std_shared_ptr< I_New > &new_fcuntion, const std_shared_ptr< I_Del > &del_fcuntion ) : QObject( parent ),
	converVector( conver_vector ),
	newFcuntion( new_fcuntion ),
	delFcuntion( del_fcuntion ), typeInfo( nullptr ) {
	newFcuntion.get( )->newObj( &var );

}
BaseVarType::BaseVarType( const std_vector< std_shared_ptr< I_Conver > > &conver_vector, const std_shared_ptr< I_New > &new_fcuntion, const std_shared_ptr< I_Del > &del_fcuntion ) : BaseVarType( nullptr, conver_vector, new_fcuntion, del_fcuntion ) { }
bool BaseVarType::setVar( const I_Var *target_data ) {
	size_t count = converVector.size( );
	auto data = converVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].get( )->converTarget( target_data ) ) {
			bool fillTarget = data[ index ].get( )->fillTarget( var, target_data );
			if( fillTarget == false ) // 失败继续下一次
				continue;
			return fillTarget;
		}
	return false;
}
bool BaseVarType::setVar( const BaseVarType *target_data ) {
	size_t count = converVector.size( );
	if( count == 0 )
		return false;
	auto data = converVector.data( );
	auto target_var_ptr = target_data->var;
	auto element = data[ 0 ].get( );
	for( size_t index = 0; index < count; index += 1, element = data[ index ].get( ) )
		if( element->converTarget( target_var_ptr ) ) {
			bool fillTarget = element->fillTarget( var, target_var_ptr );
			if( fillTarget == false ) // 失败继续下一次
				continue;
			return fillTarget;
		}
	return false;
}
const I_Type & BaseVarType::getTypeInfo( ) const {
	return *typeInfo.get( );
}
BaseVarType::BaseVarType( const BaseVarType &other ) : QObject { other.parent( ) },
	converVector { other.converVector },
	newFcuntion { other.newFcuntion },
	delFcuntion { other.delFcuntion } {
	newFcuntion.get( )->newObj( &var );
	setVar( other.var );
	typeInfo = other.typeInfo;
}
BaseVarType & BaseVarType::operator=( const BaseVarType &other ) {
	if( this == &other )
		return *this;
	if( *var != *other.var )
		return *this;
	setParent( other.parent( ) );
	converVector = other.converVector;
	setVar( other.var );
	typeInfo = other.typeInfo;
	return *this;
}
BaseVarType::~BaseVarType( ) {
	delFcuntion.get( )->delObj( &var );
}
