#include "./floatType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"

FloatType::FloatType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
}

void * FloatType::getVarPtr( ) const {
	return var;
}
