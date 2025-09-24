#include "./nullptrType.h"

#include "floatType.h"
#include "intType.h"
#include "stringType.h"
NullptrType::NullptrType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( nullptr ) ) ) ) {

	I_Type *typeInfo = initTypeInfo( );
}
NullptrType::NullptrType( ) : NullptrType( nullptr ) { }
NullptrType::NullptrType( const NullptrType &other ) : BaseVarType { other } { }
NullptrType::~NullptrType( ) {
}