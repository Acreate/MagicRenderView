#include "./inputString.h"

#include <qt/varType/varType.h>
InputString::InputString( ) {
	var = VarType::templateVarType< QString >( );
}
