#ifndef OUTPUTPORT_H_H_HEAD__FILE__
#define OUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include <QObject>
class InputPort;
class Application;
class VarDirector;
class Node;
class OutputPort : public QObject {
	Q_OBJECT;
private:
	friend class Node;
	friend class InputPort;
protected:
	Application *instancePtr;
	VarDirector *varDirector;
protected:
	QString name;
	Node *node;
	QString varTypeName;
	void *varPtr;
	std::vector< InputPort * > linkThisInputPortVector;
public:
	OutputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QObject *parent = nullptr );
	~OutputPort( ) override;
	virtual bool link( InputPort *input_port_obj_port );
	virtual bool unlink( InputPort *input_port_obj_port );
	virtual bool refInputPortHasNode( Node *input_port_node );
	virtual bool refInputPortHasPort( InputPort *input_port );
	virtual const QString & getName( ) const { return name; }
	virtual void * getVarPtr( ) const { return varPtr; }
	virtual Node * getNode( ) const { return node; }
	virtual const QString & getVarTypeName( ) const { return varTypeName; }
Q_SIGNALS:
	/// @brief 节点被释放信号
	/// @param release_node 释放指针
	void release_node_signal( OutputPort *release_node );
	/// @brief 节点端口发生释放时，产生该信号
	/// @param signal_port 释放的源端口对象指针
	/// @param target_prot 释放的目标端口对象指针
	void release_link_signal( OutputPort *signal_port, InputPort *target_prot );
	/// @brief 节点端口发生链接时，产生该信号
	/// @param signal_port 链接的源端口对象指针
	/// @param target_prot 链接的目标端口对象指针
	void create_link_signal( OutputPort *signal_port, InputPort *target_prot );
};
#endif // OUTPUTPORT_H_H_HEAD__FILE__
