#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once

#include <enums/nodeEnum.h>

#include "../widget/mainWidget.h"

class NodeInfoWidget;
class NodePortLinkActionPair;
class DrawLinkWidget;
class SrackInfo;
class NodeRefLinkInfo;
class DrawNodeWidget;
namespace path {
	class pathTree;
}
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
	MainWindow *mainWindow;
	MainWidget *mainWidget;
	DrawNodeWidget *drawNodeWidget;
	DrawLinkWidget *drawLinkWidget;
	std::vector< std::pair< QString, std::function< Node*( const QString & ) > > > createNodeVector;
	std::vector< NodeRefLinkInfo * > refNodeVector;
	std::vector< NodePortLinkActionPair * > linkActionMap;
	std::vector< NodeInfoWidget * > nodeInfoWidgets;
protected:
	virtual void releaseMenuResources( );
	virtual void releaseNodeResources( );
	virtual void releaseNodeInfoWidgetResources( );
	virtual bool initDrawLinkWidget( QString &result_error_msg );
	virtual bool initNodeInfoWidget( QString &result_error_msg );
	virtual bool findNodeInputPort( InputPort *&result_input_port_ptr, const uint64_t &node_id_key, const QString &input_port_name, const std::pair< uint64_t, Node * > *source_data, const size_t &source_count );
	virtual bool findNodeOutputPort( OutputPort *&result_output_port_ptr, const uint64_t &node_id_key, const QString &output_port_name, const std::pair< uint64_t, Node * > *source_data, const size_t &source_count );
public:
	NodeDirector( QObject *parent = nullptr );
	~NodeDirector( ) override;
	/// @brief 初始化管理对象
	/// @return 失败返回 false
	virtual bool init( );
	/// @brief 显示匹配的信息窗口
	/// @param association_node 关联节点
	/// @return 成功显示返回 true
	virtual bool showNodeWidgeInfo( Node *association_node );
	/// @brief 获取节点创建菜单
	/// @return 失败返回 nullptr
	virtual QMenu * getNodeCreateMenu( ) const { return nodeCreateMenu; }
	/// @brief 使用节点名称创建节点
	/// @param node_type_name 节点名称
	/// @param main_widget 显示窗口
	/// @return 失败返回 nullptr
	virtual Node * createNode( const QString &node_type_name, MainWidget *main_widget );
	/// @brief 链接端口
	/// @param output_port 输出端口
	/// @param input_port 输入端口
	/// @return 失败返回 false
	virtual bool linkPort( OutputPort *output_port, InputPort *input_port );
	/// @brief 取消链接
	/// @param output_port 输出端口
	/// @param input_port 输入端口
	/// @return 失败返回 false
	virtual bool disLinkPort( OutputPort *output_port, InputPort *input_port );
	/// @brief 绘制连接
	/// @param draw_link_widget 绘制对象
	virtual void drawLinkLines( QPainter &draw_link_widget );
	/// @brief 节点转换到数据序列
	/// @param result_vector_data 转换存储的数据序列对象
	/// @return 失败返回 false
	virtual bool toUint8VectorData( std::vector< uint8_t > &result_vector_data );
	/// @brief 从数据回复节点
	/// @param result_use_count 使用数据量
	/// @param source_array_ptr 数据起始地址
	/// @param source_array_count 数据最大数量
	/// @return 失败返回 false
	virtual bool formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count );
protected:
	virtual QMenu * fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr, std::list< std::pair< QString, QAction * > > &result_action_map );
	virtual bool fromPathTreeGenerateCreateaAction( path::pathTree *path_tree, QMenu *parent_menu, std::list< std::pair< QString, QAction * > > &result_action_map );
	virtual bool connectNodeAction( NodeStack *node_stack_ptr, const std::list< std::pair< QString, QAction * > > &action_map );
	virtual bool connectCreateNodeAction( NodeStack *node_stack_ptr, QAction *connect_qaction_ptr, QActionTriggered connect_qaction_fun_ptr, const QString &node_type_name, const std::function< Node *( const QString & ) > &action_click_function );
	virtual void removeRefNodeVectorAtNode( Node *remove_node );
	virtual void appendRefNodeVectorAtNode( NodeRefLinkInfo *append_node_ref_link_info );
	virtual size_t removePortLinkAction( InputPort *input_port );
	virtual size_t removePortLinkAction( OutputPort *output_port );
	virtual size_t removePortLinkAction( InputPort *input_port, OutputPort *output_port );
	virtual size_t addEndPortLinkAction( InputPort *input_port, OutputPort *output_port, QAction *input_port_link_action, QAction *output_port_link_action );
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
	virtual void finishCreateNode( NodeRefLinkInfo *finish_node );
	virtual void releaseNodeLink( NodeRefLinkInfo *signal_obj_ptr, NodeRefLinkInfo *release_output_node_ref_obj_ptr, const SrackInfo &srack_info );
	virtual void createNodeLink( NodeRefLinkInfo *signal_obj_ptr, NodeRefLinkInfo *create_output_node_ref_obj_ptr, const SrackInfo &srack_info );
	virtual void releasePortLink( InputPort *input_port, OutputPort *release_output_port, const SrackInfo &srack_info );
	virtual void createPortLink( InputPort *input_port, OutputPort *bind_output_port, const SrackInfo &srack_info );
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
	void finish_release_port_link_signal( NodeDirector *signal_obj_ptr, InputPort *signal_port, OutputPort *target_prot, const SrackInfo &srack_info );
	/// @brief 节点端口发生链接时，产生该信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_port 链接的源端口对象指针
	/// @param target_prot 链接的目标端口对象指针
	/// @param srack_info 堆栈信息
	void finish_create_port_link_signal( NodeDirector *signal_obj_ptr, InputPort *signal_port, OutputPort *target_prot, const SrackInfo &srack_info );
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
