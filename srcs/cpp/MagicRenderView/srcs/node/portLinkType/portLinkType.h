#ifndef PORTLINKTYPE_H_H_HEAD__FILE__
#define PORTLINKTYPE_H_H_HEAD__FILE__
#pragma once
#include <QString>

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
	QString anyVarStringName;
public:
	PortLinkType( ) { }
	virtual ~PortLinkType( ) { }
	virtual bool init( Application *application, NodeDirector *node_director, VarDirector *var_director, AppDirector *app_director );
	/// @brief 链接两个端口，该操作会产生端口引用
	/// @param output_port 输出端口
	/// @param input_port 输入端口
	/// @return 链接成功返回 true
	virtual bool linkPort( OutputPort *output_port, InputPort *input_port );
	/// @brief 匹配两个端口，该操作不影响端口引用
	/// @param output_port 输出端口
	/// @param input_port 输入端口
	/// @return 匹配成功返回 true
	virtual bool linkPortTypeComp( OutputPort *output_port, InputPort *input_port );
};

#endif // PORTLINKTYPE_H_H_HEAD__FILE__
