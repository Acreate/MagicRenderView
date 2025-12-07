#ifndef OUTPUTPORT_H_H_HEAD__FILE__
#define OUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <QWidget>

#include <enums/nodeEnum.h>

class QHBoxLayout;
class QLabel;
class SrackInfo;
class InputPort;
class Application;
class VarDirector;
class Node;
class OutputPort : public QWidget {
	Q_OBJECT;
private:
	friend class Node;
	friend class NodeRefLinkInfo;
	friend class NodePortLinkInfo;
	friend class InputportLinkOutputPortInfo;
	friend class NodePortLinkActionPair;
	friend class InputPort;
	friend class NodeDirector;
	friend class NodeStack;
	friend class NodeRefLinkInfoTools;
	friend class NodeBuilderStream;
	friend class NodeBuilderTools;
protected:
	Application *instancePtr;
	VarDirector *varDirector;
protected:
	QString portName;
	QString varTypeName;
	void *varPtr;
protected:
	QLabel *ico;
	QLabel *showTitle;
	QHBoxLayout *mainLayout;
	Node *parentNode;
	QMenu *disLinkMenu;
public:
	OutputPort( const QString &name );
	~OutputPort( ) override;
	virtual bool init( Node *parent );
	virtual NodeEnum::PortType getPortType( ) const =0;
	virtual const QString & getPortName( ) const { return portName; }
	virtual const QString & getVarTypeName( ) const { return varTypeName; }
	virtual void * getVarPtr( ) const { return varPtr; }
	virtual QPoint getLinkPoint( ) const;
	virtual Node * getParentNode( ) const { return parentNode; }
	virtual QMenu * getDisLinkMenu( ) const { return disLinkMenu; }
	// 信号
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_node_port 释放对象指针
	/// @param srack_info 信号行
	void release_node_signal( OutputPort *release_node_port, const SrackInfo &srack_info );
};
#endif // OUTPUTPORT_H_H_HEAD__FILE__
