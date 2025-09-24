#include "./stringType.h"

#include "floatType.h"
#include "intType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
StringType::StringType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
	I_Type *typeInfo = initTypeInfo( );
}
