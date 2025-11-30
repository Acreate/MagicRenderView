#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <enums/nodeEnum.h>

class SrackInfo;
class NodeRefLinkInfo;
class DrawNodeWidget;
namespace path {
	class pathTree;
}
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
	std::vector< std::pair< QString, std::function< Node*( const QString & ) > > > createNodeVector;
	std::vector< std::pair< Node *, NodeRefLinkInfo * > * > refNodeVector;
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
	void releaseResources( );
	~NodeDirector( ) override;
	virtual bool init( );
	virtual QMenu * getNodeCreateMenu( ) const { return nodeCreateMenu; }
	virtual Node * createNode( const QString &node_type_name, DrawNodeWidget *draw_node_widget );
	virtual NodeClickInfo * getNodeAtPos( const QPoint &point );
protected:
	virtual QMenu * fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr, std::list< std::pair< QString, QAction * > > &result_action_map );
	virtual bool fromPathTreeGenerateCreateaAction( path::pathTree *path_tree, QMenu *parent_menu, std::list< std::pair< QString, QAction * > > &result_action_map );
	virtual bool connectNodeAction( NodeStack *node_stack_ptr, const std::list< std::pair< QString, QAction * > > &action_map );
	virtual bool connectCreateNodeAction( NodeStack *node_stack_ptr, QAction *connect_qaction_ptr, QActionTriggered connect_qaction_fun_ptr, const QString &node_type_name, const std::function< Node *( const QString & ) > &action_click_function );
	virtual void connectNodeSignals( Node *connect_obj_ptr );
	virtual void removeRefNodeVectorAtNode( Node *remove_node );
	virtual void appendRefNodeVectorAtNode( Node *append_node, NodeRefLinkInfo *append_node_ref_link_info );
protected:
	/// @brief 释放对象产生信号
	/// @param release_node 释放对象指针
	/// @param srack_info 信号行
	virtual void releaseNode( Node *release_node, const SrackInfo &srack_info );
	/// @brief 节点错误信号
	/// @param error_node 错误节点
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	/// @param srack_info 堆栈信息
	virtual void errorRunNode( Node *error_node, NodeEnum::ErrorType error_type, const QString &error_msg, const SrackInfo &srack_info );
	/// @brief 建议节点信号
	/// @param advise_node 建议节点
	/// @param advise_type 建议类型
	/// @param advise_msg 建议消息
	/// @param srack_info 堆栈信息
	virtual void adviseRunNode( Node *advise_node, NodeEnum::AdviseType advise_type, const QString &advise_msg, const SrackInfo &srack_info );
	/// @brief 节点完成运行信号
	/// @param finish_node 完成节点
	/// @param srack_info 堆栈信息
	virtual void finishRunNode( Node *finish_node, const SrackInfo &srack_info );
Q_SIGNALS:
	/// @brief 节点被释放信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param release_node 释放指针
	/// @param srack_info 堆栈信息
	void release_node_signal( NodeDirector *signal_obj_ptr, Node *release_node, const SrackInfo &srack_info );
	/// @brief 节点端口发生释放时，产生该信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_port 释放的源端口对象指针
	/// @param target_prot 释放的目标端口对象指针
	/// @param srack_info 堆栈信息
	void finish_release_node_port_link_signal( NodeDirector *signal_obj_ptr, InputPort *signal_port, OutputPort *target_prot, const SrackInfo &srack_info );
	/// @brief 节点端口发生链接时，产生该信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_port 链接的源端口对象指针
	/// @param target_prot 链接的目标端口对象指针
	/// @param srack_info 堆栈信息
	void finish_create_node_port_link_signal( NodeDirector *signal_obj_ptr, InputPort *signal_port, OutputPort *target_prot, const SrackInfo &srack_info );
	/// @brief 节点依赖发生释放时候，产生该信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_node 依赖节点
	/// @param ref_node 被删除的依赖
	/// @param srack_info 堆栈信息
	void finish_release_ref_node_signal( NodeDirector *signal_obj_ptr, Node *signal_node, Node *ref_node, const SrackInfo &srack_info );
	/// @brief 节点依赖发生增持时候，产生该信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_node 依赖节点
	/// @param ref_node 被增持的依赖
	/// @param srack_info 堆栈信息
	void finish_create_ref_node_signal( NodeDirector *signal_obj_ptr, Node *signal_node, Node *ref_node, const SrackInfo &srack_info );
	/// @brief 节点错误信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param error_node 错误节点
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	/// @param srack_info 堆栈信息
	void error_run_node_signal( NodeDirector *signal_obj_ptr, Node *error_node, NodeEnum::ErrorType error_type, const QString &error_msg, const SrackInfo &srack_info );
	/// @brief 建议节点信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param advise_node 建议节点
	/// @param advise_type 建议类型
	/// @param advise_msg 建议消息
	/// @param srack_info 堆栈信息
	void advise_run_node_signal( NodeDirector *signal_obj_ptr, Node *advise_node, NodeEnum::AdviseType advise_type, const QString &advise_msg, const SrackInfo &srack_info );
	/// @brief 节点完成运行信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param finish_node 完成节点
	/// @param srack_info 堆栈信息
	void finish_run_node_signal( NodeDirector *signal_obj_ptr, Node *finish_node, const SrackInfo &srack_info );
	/// @brief 成功创建节点信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param create_node 创建对象
	/// @param srack_info 堆栈信息
	void finish_create_node_signal( NodeDirector *signal_obj_ptr, Node *create_node, const SrackInfo &srack_info );
	/// @brief 节点创建失败信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param create_name 节点名称
	/// @param error_type_info 错误类型
	/// @param error_msg 失败信息
	/// @param srack_info 堆栈信息
	void error_create_node_signal( NodeDirector *signal_obj_ptr, const QString &create_name, NodeEnum::CreateType error_type_info, const QString &error_msg, const SrackInfo &srack_info );
};

#endif // NODEDIRECTOR_H_H_HEAD__FILE__
