#ifndef INPUTPORT_H_H_HEAD__FILE__
#define INPUTPORT_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QWidget>

#include <enums/nodeEnum.h>
class SrackInfo;
class QHBoxLayout;
class QLabel;
class Application;
class VarDirector;
class OutputPort;
class NodePortLinkInfo;
class Node;
class NodeRunInfo;
class InputPort : public QWidget {
	Q_OBJECT;
private:
	friend class Node;
	friend class NodeRefLinkInfo;
	friend class NodePortLinkInfo;
	friend class NodePortLinkActionPair;
	friend class InputportLinkOutputPortInfo;
	friend class OutputPort;
	friend class NodeDirector;
	friend class NodeStack;
	friend class NodeRefLinkInfoTools;
	friend class NodeBuilderTools;
	friend class NodeRunInfo;
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
private:
	std::vector< OutputPort * > refOutputPortVector;
protected:
	virtual bool emplaceBackOutputPortRef( OutputPort *output_port_ptr );
	virtual bool eraseOutputPortRef( OutputPort *output_port_ptr );
	virtual void clearOutputPortRef( );
public:
	InputPort( const QString &name );
	virtual bool init( Node *parent );
	~InputPort( ) override;
	virtual NodeEnum::PortType getPortType( ) const =0;
	virtual const QString & getPortName( ) const { return portName; }
	virtual const QString & getVarTypeName( ) const { return varTypeName; }
	virtual void * getVarPtr( ) const { return varPtr; }
	virtual QPoint getLinkPoint( ) const;
	virtual Node * getParentNode( ) const { return parentNode; }
	virtual QMenu * getDisLinkMenu( ) const;
	virtual bool setValue( VarDirector *var_director, void *var_ptr ) { return false; }
protected:
	void paintEvent( QPaintEvent *event ) override;
	bool event( QEvent *event ) override;
public:
	// 信号
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_node_port 释放对象指针
	/// @param srack_info 信号行
	void release_node_signal( InputPort *release_node_port, const SrackInfo &srack_info );
	/// @brief 链接信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void connect_input_port_signal( InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 断开信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void dis_connect_input_port_signal( InputPort *input_port, OutputPort *ref_output_port );
};

#endif // INPUTPORT_H_H_HEAD__FILE__
