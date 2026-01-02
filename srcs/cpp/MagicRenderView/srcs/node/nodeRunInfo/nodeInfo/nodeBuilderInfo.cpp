#include "nodeBuilderInfo.h"

#include "../../node/node.h"
#include "../port/inputPort/inputPortBuilderInfo.h"
#include "../port/outputPort/outputPortBuilderInfo.h"
NodeBuilderInfo::NodeBuilderInfo( Node *node ) : QObject( node ), node( node ) {

}
bool NodeBuilderInfo::init( const UCallFunctionAlias &node_call_fucntion ) {
	nodeCallFunction = node_call_fucntion;
	return true;
}
bool NodeBuilderInfo::call( std::vector< NodeBuilderInfo * > &result_suggestion_next_builder_vector ) {
	if( nodeCallFunction == nullptr )
		return false;
	std::vector< InputPortBuilderInfo * > inputPortBuilderInfoVector;
	std::vector< OutputPortBuilderInfo * > outputPortBuilderInfoVector;
	node->getInputPortBuilderInfoVector( inputPortBuilderInfoVector );
	node->getOutputPortBuilderInfoVector( outputPortBuilderInfoVector );
	return nodeCallFunction( inputPortBuilderInfoVector, outputPortBuilderInfoVector, result_suggestion_next_builder_vector );
}
void OutputPortBuilderInfoTools::getValueInfo( OutputPortBuilderInfo *output_port_builder_info, VarDirector *&result_var_director, void *&result_value_ptr ) {
	result_var_director = output_port_builder_info->varDirector;
	result_value_ptr = output_port_builder_info->varValuePtr;
}
void InputPortBuilderInfoTools::getValueInfo( InputPortBuilderInfo *input_port_builder_info, VarDirector *&result_var_director, void *&result_value_ptr ) {
	result_value_ptr = input_port_builder_info->varValuePtr;
	result_var_director = input_port_builder_info->varDirector;
}
