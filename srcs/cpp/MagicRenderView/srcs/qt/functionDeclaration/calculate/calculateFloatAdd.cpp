#include "./calculateFloatAdd.h"

#include "../../stacks/varStack/IVarStack.h"

#include "../../types/baseType/floatTypeObject.h"
#include "../../types/baseType/intTypeObject.h"
#include "../../types/baseType/stringTypeObject.h"
#include "../../types/lineType/vectorTypeObject.h"
namespace ifunction {
	static std_shared_ptr< ITypeObject > floatAdd( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		std_shared_ptr< FloatTypeObject > resultFloatTypeObject = local_var_stack.appendStorageVar< FloatTypeObject >( i_function_declaration.getReturnValueName( ) );
		double var = 0;
		resultFloatTypeObject->setVal( var );
		auto paramInfos = i_function_declaration.getParamInfos( );
		if( paramInfos.size( ) == 0 )
			return resultFloatTypeObject;
		auto sharedPtr = paramInfos.data( )[ 0 ];
		auto paramName = sharedPtr.get( )->second;
		auto typeObject = local_var_stack.getStorageVar( paramName );
		auto element = typeObject.get( );
		auto vectorTypeObject = qobject_cast< VectorTypeObject * >( element );
		if( *vectorTypeObject == nullptr )
			return resultFloatTypeObject;
		size_t count = vectorTypeObject->count( );
		if( count == 0 )
			return resultFloatTypeObject;

		auto vectrPtr = vectorTypeObject->data( );
		for( size_t index = 0; index < count; ++index ) {
			auto shared = vectrPtr[ index ];
			element = shared.get( );
			auto intTypeObject = qobject_cast< IntTypeObject * >( element );
			if( intTypeObject ) {
				var = var + intTypeObject->getVal( );
				continue;
			}
			auto floatTypeObject = qobject_cast< FloatTypeObject * >( element );
			if( floatTypeObject ) {
				var = var + floatTypeObject->getVal( );
				continue;
			}

			auto stringTypeObject = qobject_cast< StringTypeObject * >( element );
			if( stringTypeObject ) {
				var = var + stringTypeObject->toString( ).toDouble( );
				continue;
			}
		}
		resultFloatTypeObject->setVal( var );
		return resultFloatTypeObject;
	}
}
CalculateFloatAdd::CalculateFloatAdd( ): IFunctionDeclaration( "float floatAdd(float[] add_var_list)", &ifunction::floatAdd ) { }
