#ifndef PORTLINKTYPE_H_H_HEAD__FILE__
#define PORTLINKTYPE_H_H_HEAD__FILE__
#pragma once

class InputPort;
class OutputPort;
class Application;
class AppDirector;
class VarDirector;
class NodeDirector;
class PortLinkType {
protected:
	Application *application;
	AppDirector *appDirector;
	NodeDirector *nodeDirector;
	VarDirector *varDirector;
public:
	PortLinkType( ) { }
	virtual ~PortLinkType( ) { }
	virtual bool init( Application *application, NodeDirector *node_director, VarDirector *var_director, AppDirector *app_director );
	virtual bool linkPort(OutputPort* output_port, InputPort* input_port) ;
};

#endif // PORTLINKTYPE_H_H_HEAD__FILE__
