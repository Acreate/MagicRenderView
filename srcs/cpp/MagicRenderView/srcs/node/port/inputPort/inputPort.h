#ifndef INPUTPORT_H_H_HEAD__FILE__
#define INPUTPORT_H_H_HEAD__FILE__
#pragma once
#include <QObject>
class Application;
class VarDirector;
class OutputPort;
class NodePortLinkInfo;
class Node;
class InputPort : public QObject {
	Q_OBJECT;
private:
	friend class Node;
	friend class OutputPort;
protected:
	Application *instancePtr;
	VarDirector *varDirector;
protected:
	QString name;
	Node *node;
	QString varTypeName;
	void *varPtr;
	std::vector< OutputPort * > linkThisOutputPortVector;
public:
	InputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QObject *parent = nullptr );
	virtual bool refOutputPortHasNode( Node *output_port_node );
	virtual bool refOutputPortHasPort( OutputPort *output_port );
	virtual bool link( OutputPort *output_port_obj_port );
	virtual bool unlink( OutputPort *output_port_obj_port );
	virtual const QString & getVarTypeName( ) const { return varTypeName; }
	virtual const QString & getName( ) const { return name; }
	virtual void * getVarPtr( ) const { return varPtr; }
	virtual Node * getNode( ) const { return node; }
	~InputPort( ) override;
Q_SIGNALS:
	/// @brief 节点被释放信号
	/// @param release_node 释放指针
	void release_node_signal( InputPort *release_node );
	/// @brief 节点端口发生释放时，产生该信号
	/// @param signal_port 释放的源端口对象指针
	/// @param target_prot 释放的目标端口对象指针
	void release_link_signal( InputPort *signal_port, OutputPort *target_prot );
	/// @brief 节点端口发生链接时，产生该信号
	/// @param signal_port 链接的源端口对象指针
	/// @param target_prot 链接的目标端口对象指针
	void create_link_signal( InputPort *signal_port, OutputPort *target_prot );
};

#endif // INPUTPORT_H_H_HEAD__FILE__
