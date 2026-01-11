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
	// 接口类型可以任意链接
	if( outputPortType == NodeEnum::PortType::InterFace || inputPortType == NodeEnum::PortType::InterFace )
		return true;

	// 输出端是开始，输入端是生成
	if( outputPortType == NodeEnum::PortType::Begin && inputPortType == NodeEnum::PortType::Generate )
		return true;
	if( outputPortType == NodeEnum::PortType::AnyVar )
		return true;
	if( inputPortType == NodeEnum::PortType::AnyVar )
		return true;
	
	// 不是缓冲节点
	if( inputPortType != NodeEnum::PortType::Cache )
		// 非生成输出节点
		if( outputPortType != NodeEnum::PortType::Generate )
			if( outputPortType != inputPortType )
				return false; // 端口不匹配，返回 false

	QString outputPortTypeName = output_port->getVarTypeName( );
	QString inputPortTypeName = input_port->getVarTypeName( );

	// 类型不匹配，返回 false
	if( outputPortTypeName != inputPortTypeName )
		return false;
	return true;
}
