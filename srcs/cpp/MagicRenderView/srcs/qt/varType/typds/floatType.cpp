#include "./floatType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
#include "intType.h"
#include "stringType.h"
#include <QDebug>

#include "../../tools/tools.h"
FloatType::FloatType( QObject *parent ) : BaseVarType( parent ) {

	initTypeInfo = [this] {
		var = new t_current_type( );
		objTypeInfo.reset( new I_Type( typeid( *this ) ) );
		varTypeInfo.reset( new I_Type( typeid( t_current_type ) ) );
		deleteCall = [this] {
			delete ( t_current_type * ) var;
		};
		return true;
	};
	initTypeInfo( );
}
FloatType::FloatType( ) : FloatType( nullptr ) { }
FloatType::~FloatType( ) {
}
FloatType::FloatType( const FloatType &other ) : BaseVarType { other }, var { new t_current_type( *other.var ) } { }
