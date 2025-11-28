#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <enums/nodeEnum.h>

class NodeClickInfo;
class OutputPort;
class QAction;
class InputPort;
class VarDirector;
class PrinterDirector;
class Node;
class NodeStack;
class QMenu;
class Application;
class NodeDirector : public QObject {
	Q_OBJECT;
private:
	friend class Application;
	using QActionTriggered = void(QAction::*)( bool );
protected:
	QMenu *nodeCreateMenu;
	std::vector< NodeStack * > nodeStacks;
	Application *instancePtr;
	PrinterDirector *printerDirector;
	VarDirector *varDirector;
	VarDirector *nodeVarDirector;
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
	NodeDirector( QObject *parent = nullptr );
	void releaseMenu( );
	~NodeDirector( ) override;
	virtual bool init( );
	virtual QMenu * getNodeCreateMenu( ) const { return nodeCreateMenu; }
	virtual Node * createNode( const QString &stack_name, const QString &node_type_name );
	virtual NodeClickInfo * getNodeAtPos( const QPoint &point );
protected:
	bool fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr );
	bool createMenuAtNodeType( NodeStack *node_stack_ptr, const QString &node_type_name, const std::function< Node *( ) > &action_click_function );
	bool connectCreateNodeAction( NodeStack *node_stack_ptr, QAction *connect_qaction_ptr, QActionTriggered connect_qaction_fun_ptr, const QString &node_type_name, const std::function< Node *( ) > &action_click_function );
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
	/// @brief 成功创建节点信号
	/// @param create_name 节点名称
	void finish_create_signal( const QString &create_name );
	/// @brief 节点创建失败信号
	/// @param create_name 节点名称
	/// @param error_type_info 错误类型
	/// @param error_msg 失败信息
	void error_create_signal( const QString &create_name, NodeEnum::CreateType error_type_info, const QString &error_msg );
};

#endif // NODEDIRECTOR_H_H_HEAD__FILE__
