#include "./varType.h"

VarType * VarType::templateVarType( QObject *parent, const QString &type_name ) {
	VarType *result = new VarType( parent );
	result->unityTypeName = type_name;
	return result;
}
VarType::VarType( QObject *parent ) : QObject( parent ) {
	unityTypeName = typeid( *this ).name( );
}
