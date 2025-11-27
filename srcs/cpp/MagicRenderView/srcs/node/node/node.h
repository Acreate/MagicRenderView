#ifndef NODE_H_H_HEAD__FILE__
#define NODE_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "../../enums/nodeEnum.h"

#define Def_Satatic_NodeTypeName( _Type_Name ) static QString nodeTypeName( ) { return _Type_Name; }
class VarDirector;
class Application;
class NodePortLinkInfo;
class NodeRefLinkInfo;
class InputPort;
class OutputPort;
class NodeClickInfo;
class NodeDirector;
class Node : public QWidget {
	Q_OBJECT;
	friend class NodeDirector;
protected:
	Application *instancePtr;
	VarDirector *varDirector;
protected:
	NodeClickInfo *nodeClickInfo;
	std::vector< InputPort * > inputPortVector;
	std::vector< OutputPort * > outputPortVector;
	std::vector< Node * > *inputNodeVector;
	std::vector< Node * > *outputNodeVector;
protected:
	/// @brief 节点端口发生释放时，产生该信号
	/// @param signal_port 释放的源端口对象指针
	/// @param target_prot 释放的目标端口对象指针
	virtual void releaseLink( InputPort *signal_port, OutputPort *target_prot );
	/// @brief 节点端口发生链接时，产生该信号
	/// @param signal_port 链接的源端口对象指针
	/// @param target_prot 链接的目标端口对象指针
	virtual void createLink( InputPort *signal_port, OutputPort *target_prot );
public:
	~Node( ) override;
	Node( QWidget *parent, const Qt::WindowFlags &f );
	virtual NodeClickInfo * getNodeClickInfo( ) const { return nodeClickInfo; }
protected:
	/// @brief 尝试删除输入依赖目标，当目标仍然存在依赖时，删除失败，并且返回 false
	/// @param remove_target_ref_node 删除的目标
	/// @return true 表示成功删除
	virtual bool removeRefInputPortNode( Node *remove_target_ref_node );
	/// @brief 尝试删除输出依赖目标，当目标仍然存在依赖时，删除失败，并且返回 false
	/// @param remove_target_ref_node 删除的目标
	/// @return true 表示成功删除
	virtual bool removeRefOutputPortNode( Node *remove_target_ref_node );
	/// @brief 检查 this 的输入端口是否存在指定的节点 OutputPort 依赖
	/// @param output_port_ref_node 检查的输入节点
	/// @return true 表示 this 存在 output_port_ref_node 节点 OutputPort 依赖
	virtual bool inputPortHasRefNode( Node *output_port_ref_node );
	/// @brief 检查 this 的输入端口是否存在指定的节点 InputPort 依赖
	/// @param input_port_ref_node 检查的输入节点
	/// @return true 表示 this 存在 input_port_ref_node 节点 InputPort 依赖
	virtual bool outputPortHasRefNode( Node *input_port_ref_node );
	virtual void setNodeClickInfo( OutputPort *const output_port );
	virtual void setNodeClickInfo( InputPort *const input_port );
	virtual void clearNodeClickInfo( );
	virtual void setNodeTitleClickInfo( );
	virtual void setNodeOtherClickInfo( );
public:
	virtual bool init( QWidget *parent );
	virtual InputPort * getInputPort( const QString &port_name ) const;
	virtual OutputPort * getOutputPort( const QString &port_name ) const;
protected:
	void paintEvent( QPaintEvent *event ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "未实现" ) );
Q_SIGNALS:
	/// @brief 节点被释放信号
	/// @param release_node 释放指针
	void release_node_signal( Node *release_node );
	/// @brief 节点端口发生释放时，产生该信号
	/// @param signal_port 释放的源端口对象指针
	/// @param target_prot 释放的目标端口对象指针
	void release_link_signal( OutputPort *signal_port, InputPort *target_prot );
	/// @brief 节点端口发生链接时，产生该信号
	/// @param signal_port 链接的源端口对象指针
	/// @param target_prot 链接的目标端口对象指针
	void create_link_signal( OutputPort *signal_port, InputPort *target_prot );
	/// @brief 节点错误信号
	/// @param error_node 错误节点
	/// @param code_line 信号发生行号
	/// @param code_file_name 信号发生文件
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	void error_node_signal( Node *error_node, size_t code_line, const QString &code_file_name, NodeEnum::ErrorType error_type, const QString &error_msg );
	/// @brief 建议节点信号
	/// @param advise_node 建议节点
	/// @param code_line 信号发生行号
	/// @param code_file_name 信号发生文件
	/// @param advise_type 建议类型
	/// @param advise_msg 建议消息
	void advise_node_signal( Node *advise_node, size_t code_line, const QString &code_file_name, NodeEnum::AdviseType advise_type, const QString &advise_msg );
	/// @brief 节点完成运行信号
	/// @param finish_node 完成节点
	/// @param code_line 信号发生行号
	/// @param code_file_name 信号发生文件
	void finish_node_signal( Node *finish_node, size_t code_line, const QString &code_file_name );
};

#endif // NODE_H_H_HEAD__FILE__
