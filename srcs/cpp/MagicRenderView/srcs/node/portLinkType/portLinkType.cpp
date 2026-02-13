#include "portLinkType.h"

#include "../../director/varDirector.h"

#include "../node/node.h"

#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"
bool PortLinkType::init( Application *application, NodeDirector *node_director, VarDirector *var_director, AppDirector *app_director ) {
	this->application = application;
	appDirector = app_director;
	varDirector = var_director;
	nodeDirector = node_director;

	if( var_director->getTypeName( typeid( void * ), anyVarStringName ) == false )
		return false;
	return true;
}
bool PortLinkType::linkPort( OutputPort *output_port, InputPort *input_port ) {
	if( output_port->hasInputPortRef( input_port ) )
		return true;
	OutputPort **outputData;
	size_t index;
	size_t count;
	size_t inputRefIndex;
	size_t inputRefCount;
	InputPort **inputRefData;
	auto inputPortType = input_port->getPortType( );
	auto outputPortType = output_port->getPortType( );
	switch( inputPortType ) {
		case NodeEnum::PortType::Point :
			count = output_port->parentNode->outputPortVector.size( );
			outputData = output_port->parentNode->outputPortVector.data( );
			for( index = 0; index < count; ++index )
				outputData[ index ]->clearInputPortRef( );
			break;
		default :
			// 端口类型是否匹配
			if( linkPortTypeComp( output_port, outputPortType, input_port, inputPortType ) == false )
				return false;// 不允许多输入通道，则清空旧的输出端应用
			if( input_port->isMultiple( ) == false )
				input_port->clearOutputPortRef( );
			// 不允许多输出通道，则清空旧的输入端引用
			if( output_port->isMultiple( ) == false )
				output_port->clearInputPortRef( );
			else { // 检测是否存在 Point 
				count = output_port->parentNode->outputPortVector.size( );
				outputData = output_port->parentNode->outputPortVector.data( );
				for( index = 0; index < count; ++index ) {
					inputRefCount = outputData[ index ]->refInputPortVector.size( );
					inputRefData = outputData[ index ]->refInputPortVector.data( );
					for( inputRefIndex = 0; inputRefIndex < inputRefCount; ++inputRefIndex ) {
						outputPortType = inputRefData[ index ]->getPortType( );
						if( outputPortType == NodeEnum::PortType::Point ) {
							output_port->clearInputPortRef( );
							break;
						}
					}
					if( inputRefIndex < inputRefCount )
						break;
				}
			}
	}

	input_port->emplaceBackOutputPortRef( output_port );
	return true;
}
bool PortLinkType::linkPortTypeComp( OutputPort *output_port, const NodeEnum::PortType &output_port_type, InputPort *input_port, const NodeEnum::PortType &input_port_type ) {
	if( output_port_type == NodeEnum::PortType::AnyVar )
		if( input_port_type == NodeEnum::PortType::Unity || input_port_type == NodeEnum::PortType::Array )
			return true;
	if( input_port_type == NodeEnum::PortType::AnyVar )
		if( output_port_type == NodeEnum::PortType::Unity || output_port_type == NodeEnum::PortType::Array )
			return true;

	if( output_port_type != input_port_type )
		return false; // 端口不匹配，返回 false

	QString outputPortTypeName = output_port->getVarTypeName( );
	QString inputPortTypeName = input_port->getVarTypeName( );
	// 类型不匹配，返回 false
	if( outputPortTypeName != inputPortTypeName )
		return false;
	return true;
}
