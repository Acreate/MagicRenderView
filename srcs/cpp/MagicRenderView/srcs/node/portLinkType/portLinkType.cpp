#include "portLinkType.h"

#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"
bool PortLinkType::init( Application *application, NodeDirector *node_director, VarDirector *var_director, AppDirector *app_director ) {
	this->application = application;
	appDirector = app_director;
	varDirector = var_director;
	nodeDirector = node_director;
	return true;
}
bool PortLinkType::linkPort( OutputPort *output_port, InputPort *input_port ) {
	if( output_port->hasInputPortRef( input_port ) )
		return true;
	auto outputPortType = output_port->getPortType( );
	auto inputPortType = input_port->getPortType( );
	if( inputPortType != outputPortType )
		if( outputPortType != NodeEnum::PortType::Generate )
			return false;
	if( output_port->getVarTypeName( ) != input_port->getVarTypeName( ) )
		return false;
	
	input_port->emplaceBackOutputPortRef( output_port );
	return true;
}
