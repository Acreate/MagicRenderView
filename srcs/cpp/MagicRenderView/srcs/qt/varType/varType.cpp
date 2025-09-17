#include "./varType.h"


VarType::VarType( QObject *parent ) : QObject( parent ) {
	unityTypeName = typeid( *this ).name( );
}
