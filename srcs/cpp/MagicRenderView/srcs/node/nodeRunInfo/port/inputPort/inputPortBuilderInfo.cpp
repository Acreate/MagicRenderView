#include "inputPortBuilderInfo.h"

#include "../../../port/inputPort/inputPort.h"
InputPortBuilderInfo::InputPortBuilderInfo( InputPort *input_port ) : QObject( input_port ), inputPort( input_port ) {
}
bool InputPortBuilderInfo::init( const UCallFunctionAlias &input_port_call_function ) {
	inputPortCallFunction = input_port_call_function;
	return true;
}
bool InputPortBuilderInfo::call( std::vector< NodeBuilderInfo * > &result_suggestion_next_builder_vector ) {
	if( inputPortCallFunction == nullptr )
		return false;
	return inputPortCallFunction( this, result_suggestion_next_builder_vector );
}
