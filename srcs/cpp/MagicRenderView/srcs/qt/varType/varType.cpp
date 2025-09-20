#include "./varType.h"

#include "../generate/varTypeGenerate.h"

VarType::VarType( QObject *parent ) : QObject( parent ) {
	unityTypeName = typeid( *this ).name( );
}
size_t VarType::resetToGenerateCode( ) {
	generateCode = VarTypeGenerate::genVarTypeCode( this );
	return generateCode;
}
