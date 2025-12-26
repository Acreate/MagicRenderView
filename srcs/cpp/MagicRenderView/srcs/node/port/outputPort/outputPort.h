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
class NodeRunInfo;
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
	friend class NodeBuilderTools;
	friend class NodeRunInfo;
	friend class NormalNodeEditorPropertyMenu;
protected:
	Application *instancePtr;
	VarDirector *varDirector;
protected:
	QString portName;
	QString varTypeName;
	void *varPtr;
	uint64_t generateCode;
protected:
	QLabel *ico;
	QLabel *showTitle;
	QHBoxLayout *mainLayout;
	Node *parentNode;
	QMenu *disLinkMenu;
private:
	std::vector< InputPort * > refInputPortVector;
protected:
	virtual bool emplaceBackInputPortRef( InputPort *input_port_ptr );
	virtual bool eraseInputPortRef( InputPort *input_port_ptr );
	virtual void clearInputPortRef();
public:
	OutputPort( const QString &name );
	~OutputPort( ) override;
	virtual bool hasInputPortRef( InputPort *input_port_ptr ) const;
	virtual bool init( Node *parent );
	virtual uint64_t getGenerateCode( ) const { return generateCode; }
	virtual NodeEnum::PortType getPortType( ) const =0;
	virtual const QString & getPortName( ) const { return portName; }
	virtual const QString & getVarTypeName( ) const { return varTypeName; }
	virtual void * getVarPtr( ) const { return varPtr; }
	virtual QPoint getLinkPoint( ) const;
	virtual Node * getParentNode( ) const { return parentNode; }
	virtual QMenu * getDisLinkMenu( ) const;
protected:
	void paintEvent( QPaintEvent *event ) override;
	bool event( QEvent *event ) override;
public:
	// 信号
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_node_port 释放对象指针
	/// @param srack_info 信号行
	void release_node_signal( OutputPort *release_node_port, const SrackInfo &srack_info );
	/// @brief 链接信号
	/// @param output_port 输出端
	/// @param ref_input_port 输入端
	void connect_output_port_signal( OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 断开信号
	/// @param output_port 输出端
	/// @param ref_input_port 输入端
	void dis_connect_output_port_signal( OutputPort *output_port, InputPort *ref_input_port );
};
#endif // OUTPUTPORT_H_H_HEAD__FILE__
