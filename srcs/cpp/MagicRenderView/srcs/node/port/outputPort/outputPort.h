#ifndef OUTPUTPORT_H_H_HEAD__FILE__
#define OUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include <QObject>

#include <enums/nodeEnum.h>

class InputPort;
class Application;
class VarDirector;
class Node;
class OutputPort : public QObject {
	Q_OBJECT;
private:
	friend class Node;
	friend class InputPort;
	friend class NodeDirector;
	friend class NodeStack;
protected:
	Application *instancePtr;
	VarDirector *varDirector;
protected:
	QString name;
	Node *node;
	QString varTypeName;
	void *varPtr;
public:
	OutputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QObject *parent = nullptr );
	~OutputPort( ) override;
	virtual bool init( ) =0;
	virtual NodeEnum::PortType getPortType( ) const =0;
Q_SIGNALS:
	/// @brief 节点被释放信号
	/// @param release_node 释放指针
	void release_node_signal( OutputPort *release_node );
};
#endif // OUTPUTPORT_H_H_HEAD__FILE__
