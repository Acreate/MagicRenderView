#include "portLinkType.h"

#include "../../director/varDirector.h"
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
	// 端口类型是否匹配
	if( linkPortTypeComp( output_port, input_port ) == false )
		return false;
	// 不允许多输入通道，则清空旧的输出端应用
	if( input_port->isMultiple( ) == false )
		input_port->clearOutputPortRef( );
	// 不允许多输出通道，则清空旧的输入端引用
	if( output_port->isMultiple( ) == false )
		output_port->clearInputPortRef( );
	input_port->emplaceBackOutputPortRef( output_port );
	return true;
}
bool PortLinkType::linkPortTypeComp( OutputPort *output_port, InputPort *input_port ) {
	auto inputPortType = input_port->getPortType( );
	auto outputPortType = output_port->getPortType( );

	if( outputPortType == NodeEnum::PortType::AnyVar )
		if( inputPortType == NodeEnum::PortType::Unity || inputPortType == NodeEnum::PortType::Array )
			return true;
	if( inputPortType == NodeEnum::PortType::AnyVar )
		if( outputPortType == NodeEnum::PortType::Unity || outputPortType == NodeEnum::PortType::Array )
			return true;

	if( outputPortType != inputPortType )
		return false; // 端口不匹配，返回 false

	QString outputPortTypeName = output_port->getVarTypeName( );
	QString inputPortTypeName = input_port->getVarTypeName( );
	// 类型不匹配，返回 false
	if( outputPortTypeName != inputPortTypeName )
		return false;
	return true;
}
