#include "./floatType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
#include "intType.h"
#include "stringType.h"
#include <QDebug>

#include "../../tools/tools.h"
FloatType::FloatType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
	I_Type *typeInfo = initTypeInfo( );
}
FloatType::FloatType( ) : FloatType( nullptr ) { }
FloatType::~FloatType( ) {
	delete var;
}
FloatType::FloatType( const FloatType &other ) : BaseVarType { other }, var { new t_current_type( *other.var ) } { }
