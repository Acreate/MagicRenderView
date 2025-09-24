#include "./intType.h"

#include "floatType.h"
#include "stringType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
IntType::IntType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
	I_Type *typeInfo = initTypeInfo( );
}
