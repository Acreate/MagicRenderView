#include "outputPortBuilderInfo.h"

#include "../../../port/outputPort/outputPort.h"
OutputPortBuilderInfo::OutputPortBuilderInfo( OutputPort *output_port ) : QObject( output_port ), outputPort( output_port ) {

}
bool OutputPortBuilderInfo::init( const UCallFunctionAlias &output_port_call_function ) {
	outputPortCallFunction = output_port_call_function;
	return true;
}
bool OutputPortBuilderInfo::call( std::vector< NodeBuilderInfo * > &result_suggestion_next_builder_vector ) {
	if( outputPortCallFunction == nullptr )
		return false;
	return outputPortCallFunction( this, result_suggestion_next_builder_vector );
}
