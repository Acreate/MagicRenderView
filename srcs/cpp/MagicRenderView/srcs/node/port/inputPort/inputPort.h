#ifndef INPUTPORT_H_H_HEAD__FILE__
#define INPUTPORT_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QWidget>

#include <enums/nodeEnum.h>
class Application;
class VarDirector;
class OutputPort;
class NodePortLinkInfo;
class Node;
class InputPort : public QWidget {
	Q_OBJECT;
private:
	friend class Node;
	friend class OutputPort;
	friend class NodeDirector;
	friend class NodeStack;
protected:
	Application *instancePtr;
	VarDirector *varDirector;
	QString name;
	Node *node;
	QString varTypeName;
	void *varPtr;
	std::vector< OutputPort * > linkThisOutputPortVector;
public:
	InputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QWidget *parent = nullptr );
	virtual bool init( ) = 0;
	~InputPort( ) override;
	virtual NodeEnum::PortType getPortType( ) const =0;
Q_SIGNALS:
	/// @brief 节点被释放信号
	/// @param release_node 释放指针
	void release_node_signal( InputPort *release_node );
};

#endif // INPUTPORT_H_H_HEAD__FILE__
