#ifndef NODE_H_H_HEAD__FILE__
#define NODE_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
#include <typeinfo>

#include <enums/nodeEnum.h>

#define Def_Satatic_NodeTypeName( _Type_Name ) static QString nodeTypeName( ) { return _Type_Name; }
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
	Application *instancePtr;
	VarDirector *varDirector;
	NodeDirector *nodeDirector;
private:
	NodeClickInfo *nodeClickInfo;
	std::vector< InputPort * > inputPortVector;
	std::vector< OutputPort * > outputPortVector;
	std::vector< Node * > inputNodeVector;
	std::vector< Node * > outputNodeVector;
	VarDirector *nodeVarDirector;
protected:
	VarDirector *nodeFunctionVarDirector;
	using NodeFunctionResultType = void ;
	using NodeFunctionType = std::function< NodeFunctionResultType( ) >;
	NodeFunctionType nodeFunction;
protected:
	/// @brief 删除输入依赖节点
	/// @param remove_target 输入依赖节点
	virtual void removeInputNode( Node *remove_target );
public:
	~Node( ) override;
	Node( QWidget *parent, const Qt::WindowFlags &f );
	virtual NodeClickInfo * getNodeClickInfo( ) const { return nodeClickInfo; }
	virtual bool init( QWidget *parent );
	virtual bool runFunction(  ) const;
	virtual InputPort * getInputPort( const QString &port_name ) const;
	virtual OutputPort * getOutputPort( const QString &port_name ) const;
	virtual bool updateLayout( ) = 0;
protected:
	/// @brief 增加一个输入端口
	/// @param input_port 输入端
	/// @return 失败返回 false
	virtual bool appendInputPort( InputPort *input_port );
	/// @brief 增加一个输出端口
	/// @param output_port 输出端口
	/// @return 失败返回 false
	virtual bool appendOutputPort( OutputPort *output_port );
	virtual void setNodeClickInfo( OutputPort *const output_port );
	virtual void setNodeClickInfo( InputPort *const input_port );
	virtual void clearNodeClickInfo( );
	virtual void setNodeTitleClickInfo( );
	virtual void setNodeOtherClickInfo( );
	virtual void * createVar( const QString &type_name );
	virtual void * createVar( const std::type_info &std_type_info );
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
	void release_link_signal( InputPort *signal_port, OutputPort *target_prot );
	/// @brief 节点端口发生链接时，产生该信号
	/// @param signal_port 链接的源端口对象指针
	/// @param target_prot 链接的目标端口对象指针
	void create_link_signal( InputPort *signal_port, OutputPort *target_prot );
	/// @brief 节点依赖发生释放时候，产生该信号
	/// @param signal_node 依赖节点
	/// @param ref_node 被删除的依赖
	void release_ref_node_signal( Node *signal_node, Node *ref_node );
	/// @brief 节点依赖发生增持时候，产生该信号
	/// @param signal_node 依赖节点
	/// @param ref_node 被增持的依赖
	void create_ref_node_signal( Node *signal_node, Node *ref_node );
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
