#include "./calculateDiv.h"

#include "../../stacks/varStack/IVarStack.h"

#include "../../types/baseType/floatTypeObject.h"
#include "../../types/baseType/intTypeObject.h"
#include "../../types/baseType/stringTypeObject.h"
#include "../../types/lineType/vectorTypeObject.h"
namespace ifunction {

	static void div( const IVarStack &var_stack, const IFunctionDeclaration &i_function_declaration ) {

		std_shared_ptr< FloatTypeObject > resultFloatTypeObject = var_stack.appendStorageVar< FloatTypeObject >( i_function_declaration.getReturnValueName( ) );
		double var = 0;
		auto paramInfos = i_function_declaration.getParamInfos( );
		if( paramInfos.size( ) == 0 )
			return;
		auto sharedPtr = paramInfos.data( )[ 0 ];
		auto paramName = sharedPtr.get( )->second;
		auto typeObject = var_stack.getStorageVar( paramName );
		auto element = typeObject.get( );
		auto vectorTypeObject = qobject_cast< VectorTypeObject * >( element );
		if( *vectorTypeObject == nullptr )
			return;
		size_t count = vectorTypeObject->count( );
		if( count == 0 )
			return;

		typeObject = vectorTypeObject->data( )[ 0 ];
		element = typeObject.get( );
		auto intTypeObject = qobject_cast< IntTypeObject * >( element );
		if( intTypeObject )
			var = intTypeObject->getVal( );
		else {
			auto floatTypeObject = qobject_cast< FloatTypeObject * >( element );
			if( floatTypeObject )
				var = floatTypeObject->getVal( );
			else {
				auto stringTypeObject = qobject_cast< StringTypeObject * >( element );
				if( stringTypeObject )
					var = stringTypeObject->toString( ).toDouble( );
			}
		}

		if( count == 1 || var == 0 ) {
			resultFloatTypeObject->setVal( var );
			return;
		}

		auto vectrPtr = vectorTypeObject->data( );
		for( size_t index = 1; index < count; ++index ) {
			auto shared = vectrPtr[ index ];
			element = shared.get( );
			intTypeObject = qobject_cast< IntTypeObject * >( element );
			if( intTypeObject ) {
				auto val = intTypeObject->getVal( );
				if( val != 0 )
					var = var / val;
				continue;
			}
			auto floatTypeObject = qobject_cast< FloatTypeObject * >( element );
			if( floatTypeObject ) {
				auto val = floatTypeObject->getVal( );
				if( var != 0 )
					var = var / val;
				continue;
			}

			auto stringTypeObject = qobject_cast< StringTypeObject * >( element );
			if( stringTypeObject ) {
				auto val = stringTypeObject->toString( ).toDouble( );
				if( val != 0 )
					var = var / val;
				continue;
			}
		}
		resultFloatTypeObject->setVal( var );
		return;
	}
}
CalculateDiv::CalculateDiv( ) : IFunctionDeclaration( "double div(double[] div_var_list)", &ifunction::div ) {

}
