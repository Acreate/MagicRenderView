#include "./stringType.h"

#include "floatType.h"
#include "intType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
StringType::StringType( QObject *parent ) : BaseVarType( parent ) {
	initTypeInfo = [this] {
		var = new t_current_type( );
		objTypeInfo.reset( new I_Type( typeid( StringType ) ) );
		varTypeInfo.reset( new I_Type( typeid( t_current_type ) ) );
		deleteCall = [this] {
			if( var )
				delete ( t_current_type * ) var;
			var = nullptr;
		};
		return true;
	};
	initTypeInfo( );
}
