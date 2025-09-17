#include "./varTypeGenerate.h"

#include "../../varType/varType.h"
VarType * VarTypeGenerate::templateVarType( QObject *parent, const QString &type_name ) {
	VarType *result = new VarType( parent );
	result->unityTypeName = type_name;
	return result;
}
