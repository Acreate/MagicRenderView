﻿#include "./rebuildToData.h"

namespace ifunction {
	static std_shared_ptr< ITypeObject > rebuildToData( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}

RebuildToData::RebuildToData( ): IFunctionDeclaration( "string rebuildToData(void* ptr)", &ifunction::rebuildToData ) {
}
