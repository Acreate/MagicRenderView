#include "./intType.h"

#include "floatType.h"
#include "stringType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
IntType::IntType( QObject *parent ) : BaseVarType( parent ) {

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
