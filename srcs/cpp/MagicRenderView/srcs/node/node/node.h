#ifndef NODE_H_H_HEAD__FILE__
#define NODE_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
#include <typeinfo>

#include <enums/nodeEnum.h>

#define Def_Satatic_NodeTypeName( _Type_Name ) static QString nodeTypeName( ) { return _Type_Name; }
class SrackInfo;
class NodeRunFunctionTypeInfo;
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
	friend class NodeStack;
protected:
	using NodeFunctionResultType = void;
	using NodeFunctionType = std::function< NodeFunctionResultType( VarDirector * ) >;
protected:
	Application *instancePtr;
	VarDirector *varDirector;
	NodeDirector *nodeDirector;
	std::vector< InputPort * > inputPortVector;
	std::vector< OutputPort * > outputPortVector;
	NodeRefLinkInfo *nodeRefLinkInfoPtr;
	VarDirector *nodeVarDirector;
	NodeFunctionType nodeFunction;
public:
	~Node( ) override;
	Node( QWidget *parent, const Qt::WindowFlags &f );
	virtual bool init( QWidget *parent, NodeRefLinkInfo *node_ref_link_info );
	virtual InputPort * getInputPort( const QString &port_name ) const;
	virtual OutputPort * getOutputPort( const QString &port_name ) const;
	virtual const NodeRefLinkInfo & getNodeRefLinkInfoPtr( ) const { return *nodeRefLinkInfoPtr; }
	virtual bool updateLayout( ) = 0;
	virtual NodeEnum::NodeType getNodeType( ) const = 0;
protected:
	/// @brief 增加一个输入端口
	/// @param input_port 输入端
	/// @return 失败返回 false
	virtual bool appendInputPort( InputPort *input_port );
	/// @brief 增加一个输出端口
	/// @param output_port 输出端口
	/// @return 失败返回 false
	virtual bool appendOutputPort( OutputPort *output_port );
protected:
	void paintEvent( QPaintEvent *event ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "未实现" ) );
	// 信号
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_node 释放对象指针
	/// @param srack_info 信号行
	void release_node_signal( Node *release_node, const SrackInfo &srack_info );
	/// @brief 节点错误信号
	/// @param error_node 错误节点
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	/// @param srack_info 堆栈信息
	void error_run_node_signal( Node *error_node, NodeEnum::ErrorType error_type, const QString &error_msg, const SrackInfo &srack_info );
	/// @brief 建议节点信号
	/// @param advise_node 建议节点
	/// @param advise_type 建议类型
	/// @param advise_msg 建议消息
	/// @param srack_info 堆栈信息
	void advise_run_node_signal( Node *advise_node, NodeEnum::AdviseType advise_type, const QString &advise_msg, const SrackInfo &srack_info );
	/// @brief 节点完成运行信号
	/// @param finish_node 完成节点
	/// @param srack_info 堆栈信息
	void finish_run_node_signal( Node *finish_node, const SrackInfo &srack_info );
};

#endif // NODE_H_H_HEAD__FILE__
