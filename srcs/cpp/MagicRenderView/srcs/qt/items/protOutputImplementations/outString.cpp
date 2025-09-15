#include "./outString.h"

#include <qt/varType/varType.h>
OutString::OutString( ) {
	var = VarType::templateVarType< QString >( );
}
