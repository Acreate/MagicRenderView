#include "./nullptrType.h"

#include "floatType.h"
#include "intType.h"
#include "stringType.h"
NullptrType::NullptrType( QObject *parent ) : BaseVarType( parent ) {
	initTypeInfo = [this] {
		objTypeInfo.reset( new I_Type( typeid( *this ) ) );
		varTypeInfo.reset( new I_Type( typeid( nullptr ) ) );
		return true;
	};
	initTypeInfo( );
}
NullptrType::NullptrType( ) : NullptrType( nullptr ) { }
NullptrType::~NullptrType( ) {
}
