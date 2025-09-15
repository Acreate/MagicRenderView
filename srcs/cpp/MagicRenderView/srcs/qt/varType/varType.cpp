#include "./varType.h"

#include "../items/nodeItemWidget.h"
VarType * VarType::templateVarType( NodeItemWidget *parent, const QString &type_name ) {
	VarType *result = new VarType( parent );
	result->unityTypeName = type_name;
	return result;
}
VarType::VarType( NodeItemWidget *parent ) : QObject( parent ) {
	unityTypeName = typeid( *this ).name( );
}
