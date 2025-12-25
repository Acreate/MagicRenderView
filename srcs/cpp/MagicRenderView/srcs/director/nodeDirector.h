#ifndef NODEDIRECTOR_H_H_HEAD__FILE__
#define NODEDIRECTOR_H_H_HEAD__FILE__
#pragma once

#include <enums/nodeEnum.h>

#include "../enums/widgetEnum.h"
#include "../tools/aliasType.h"

#include "../widget/mainWidget.h"

class MenuDirector;
class NormalNodeEditorPropertyMenu;
class NormalGenerateNodeMenu;
class NodeRunInfo;
class NodeHistory;
class NodeInfoWidget;
class DrawLinkWidget;
class DrawHighlightWidget;
class SrackInfo;
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
	Application *instancePtr;
	PrinterDirector *printerDirector;
	VarDirector *varDirector;
	VarDirector *nodeVarDirector;
	MenuDirector *menuDirector;
	NormalGenerateNodeMenu *normalGenerateNodeMenu;
	NormalNodeEditorPropertyMenu *normalNodeEditorPropertyMenu;
	MainWindow *mainWindow;
	MainWidget *mainWidget;
	NodeInfoWidget *currentShowWidget;
	std::vector< Node * > nodeArchiveVector;
	std::vector< NodeInfoWidget * > nodeInfoWidgets;
	size_t nodeHistoryIndex;
	std::vector< NodeHistory * > nodeHistorys;
protected:
	virtual void releaseObjResources( );
	virtual void releaseMenuResources( );
	virtual void releaseNodeResources( );
	virtual void releaseNodeInfoWidgetResources( );
	virtual void releaseNodeHistoryResources( );
	/// @brief 初始化节点渲染节点窗口
	/// @param result_error_msg 错误信息
	/// @return 失败返回 false 并且返回错误信息到 result_error_msg 参数
	virtual bool initNodeRenderGraphWidget( QString &result_error_msg );
	virtual bool initNodeInfoWidget( QString &result_error_msg );
	virtual bool findNodeInputPort( InputPort *&result_input_port_ptr, const uint64_t &node_id_key, const QString &input_port_name, const std::pair< uint64_t, Node * > *source_data, const size_t &source_count );
	virtual bool findNodeOutputPort( OutputPort *&result_output_port_ptr, const uint64_t &node_id_key, const QString &output_port_name, const std::pair< uint64_t, Node * > *source_data, const size_t &source_count );
	virtual bool portConnectLink( Node *output_node_ref, OutputPort *output_port, InputPort *input_port );
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
	/// @brief 显示匹配的信息窗口
	/// @param association_node 关联节点
	/// @return 成功显示返回 true
	virtual NodeInfoWidget * getNodeWidgeInfo( Node *association_node );
	/// @brief 获取节点创建菜单
	/// @return 节点创建菜单
	virtual NormalGenerateNodeMenu * getNormalGenerateNodeMenu( ) const { return normalGenerateNodeMenu; }
	/// @brief 获取节点编辑菜单
	/// @return 节点编辑菜单
	virtual NormalNodeEditorPropertyMenu * getNormalNodeEditorPropertyMenu( ) const { return normalNodeEditorPropertyMenu; }
	/// @brief 使用节点名称创建节点
	/// @param node_type_name 节点名称
	/// @return 失败返回 nullptr
	virtual Node * createNode( const QString &node_type_name );
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
	/// @brief 取消历史操作
	/// @return 失败返回 nullptr
	virtual bool cancelNodeHistory( );
	/// @brief 获取当前节点显示详情信息窗口
	/// @return 不存在显示窗口返回 nullptr
	virtual NodeInfoWidget * getCurrentShowWidget( ) const { return currentShowWidget; }
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
	/// @brief 获取最大的渲染大小
	/// @return 最大的渲染大小
	virtual QSize getMaxNodeRenderSize( ) const;
	virtual NodeRunInfo * builderCurrentAllNode( MainWidget *parent );
	virtual Node * getNode( const uint64_t &node_generator_code ) const;
protected:
	virtual bool connectNodeAction( NodeStack *node_stack_ptr, const std::list< std::pair< QString, QAction * > > &action_map );
	virtual bool connectCreateNodeAction( NodeStack *node_stack_ptr, QAction *connect_qaction_ptr, QActionTriggered connect_qaction_fun_ptr, const QString &node_type_name, const std::function< Node *( const QString & ) > &action_click_function );
	virtual void removeRefNodeVectorAtNode( Node *remove_node );
	virtual Node * appendRefNodeVectorAtNode( const QString &append_node_name, Node *append_node );
	virtual size_t removePortLinkAction( InputPort *input_port );
	virtual size_t removePortLinkAction( OutputPort *output_port );
	virtual size_t removePortLinkAction( InputPort *input_port, OutputPort *output_port );
	virtual size_t addEndPortLinkAction( InputPort *input_port, OutputPort *output_port, QAction *input_port_link_action, QAction *output_port_link_action );
	virtual bool appendNodeInfoWidget( NodeInfoWidget *append_node_info_widget_ptr );
	/// @brief 删除历史坐标后续的所有对象
	virtual void removeHistorIndexEnd( );
	virtual void appendHistorIndexEnd( const std::function< NodeHistory *( ) > &current_history, const std::function< NodeHistory *( ) > &cancel_history );
	virtual bool appendNodeToArchiveVector( Node *update_generate_code );
	virtual bool sortArchiveCode( QString & error_msg );
protected:
	/// @brief 释放对象产生信号
	/// @param release_node 释放对象指针
	/// @param srack_info 信号行
	virtual void releaseNode( Node *release_node, const SrackInfo &srack_info );
	/// @brief 节点错误信号
	/// @param error_node 原始信号对象
	/// @param org_srack_info 原始对象堆栈信号信息
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	virtual void errorRunNode( Node *error_node, const SrackInfo &org_srack_info, NodeEnum::ErrorType error_type, const QString &error_msg );
	/// @brief 建议节点信号
	/// @param advise_node 原始信号对象
	/// @param org_srack_info 原始对象堆栈信号信息
	/// @param advise_node 建议节点
	/// @param advise_type 建议类型
	/// @param advise_msg 建议消息
	virtual void adviseRunNode( Node *advise_node, const SrackInfo &org_srack_info, NodeEnum::AdviseType advise_type, const QString &advise_msg );
	/// @brief 节点完成运行信号
	/// @param finish_node 原始信号对象
	/// @param org_srack_info 原始对象堆栈信号信息
	virtual void finishRunNode( Node *finish_node, const SrackInfo &org_srack_info );
	virtual void finishCreateNode( Node *finish_node );
	/// @brief 产生链接节点引用
	/// @param output_port_node 输出节点
	/// @param ref_input_port_node 输入节点
	void connectRefInputPortNodeSlot( Node *output_port_node, Node *ref_input_port_node );
	/// @brief 断开链接节点引用
	/// @param output_port 输出节点
	/// @param ref_input_port 输入节点
	void disConnectRefInputPortNodeSlot( Node *output_port, Node *ref_input_port );
	/// @brief 产生链接节点引用
	/// @param input_port_node 输入节点
	/// @param ref_output_port 输出节点
	void connectRefOutputPortNodeSlot( Node *input_port_node, Node *ref_output_port );
	/// @brief 断开链接节点引用
	/// @param input_port_node 输入节点
	/// @param ref_output_port 输出节点
	void disConnectRefOutputPortNodeSlot( Node *input_port_node, Node *ref_output_port );
	/// @brief 链接信号
	/// @param output_port 输出端
	/// @param ref_input_port 输入端
	void connectOutputPortSlot( OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 断开信号
	/// @param output_port 输出端
	/// @param ref_input_port 输入端
	void disConnectOutputPortSlot( OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 链接信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void connectInputPortSlot( InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 断开信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void disConnectInputPortSlot( InputPort *input_port, OutputPort *ref_output_port );
	virtual void nodeRunInfoClear( NodeRunInfo *clear_obj, const SrackInfo &srack_info );
	void createNodeSlot( NormalGenerateNodeMenu *signal_obj_ptr, QAction *create_item, const QString &create_node_name, const NormalGenerateNodeMenuType::TCreateNodeFunction &create_node_function );
Q_SIGNALS:
	/// @brief 节点被释放信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param release_node 释放指针
	/// @param srack_info 堆栈信息
	void release_node_signal( NodeDirector *signal_obj_ptr, Node *release_node, const SrackInfo &srack_info );
	/// @brief 产生链接节点引用
	/// @param signal_obj_ptr 信号对象指针
	/// @param output_port_node 输出节点
	/// @param ref_input_port_node 输入节点
	void connect_ref_input_port_node_signal( NodeDirector *signal_obj_ptr, Node *output_port_node, Node *ref_input_port_node );
	/// @brief 断开链接节点引用
	/// @param signal_obj_ptr 信号对象指针
	/// @param output_port 输出节点
	/// @param ref_input_port 输入节点
	void dis_connect_ref_input_port_node_signal( NodeDirector *signal_obj_ptr, Node *output_port, Node *ref_input_port );
	/// @brief 产生链接节点引用
	/// @param signal_obj_ptr 信号对象指针
	/// @param input_port_node 输入节点
	/// @param ref_output_port 输出节点
	void connect_ref_output_port_node_signal( NodeDirector *signal_obj_ptr, Node *input_port_node, Node *ref_output_port );
	/// @brief 断开链接节点引用
	/// @param signal_obj_ptr 信号对象指针
	/// @param input_port_node 输入节点
	/// @param ref_output_port 输出节点
	void dis_connect_ref_output_port_node_signal( NodeDirector *signal_obj_ptr, Node *input_port_node, Node *ref_output_port );
	/// @brief 链接信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param output_port 输出端
	/// @param ref_input_port 输入端
	void connect_output_port_signal( NodeDirector *signal_obj_ptr, OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 断开信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param output_port 输出端
	/// @param ref_input_port 输入端
	void dis_connect_output_port_signal( NodeDirector *signal_obj_ptr, OutputPort *output_port, InputPort *ref_input_port );
	/// @brief 链接信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void connect_input_port_signal( NodeDirector *signal_obj_ptr, InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 断开信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void dis_connect_input_port_signal( NodeDirector *signal_obj_ptr, InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 节点错误信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_srack_info 当前信号产生堆栈信息
	/// @param error_node 原始信号对象
	/// @param org_srack_info 原始对象堆栈信号信息
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	void error_run_node_signal( NodeDirector *signal_obj_ptr, const SrackInfo &signal_srack_info, Node *error_node, const SrackInfo &org_srack_info, NodeEnum::ErrorType error_type, const QString &error_msg );
	/// @brief 建议节点信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_srack_info 当前信号产生堆栈信息
	/// @param advise_node 原始信号对象
	/// @param org_srack_info 原始对象堆栈信号信息
	/// @param advise_type 建议类型
	/// @param advise_msg 建议消息
	void advise_run_node_signal( NodeDirector *signal_obj_ptr, const SrackInfo &signal_srack_info, Node *advise_node, const SrackInfo &org_srack_info, NodeEnum::AdviseType advise_type, const QString &advise_msg );
	/// @brief 节点完成运行信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_srack_info 当前信号产生堆栈信息
	/// @param finish_node 原始信号对象
	/// @param org_srack_info 原始对象堆栈信号信息
	void finish_run_node_signal( NodeDirector *signal_obj_ptr, const SrackInfo &signal_srack_info, Node *finish_node, const SrackInfo &org_srack_info );
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
	/// @brief 编译对象清理信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param srack_info 信号堆栈
	/// @param clear_obj 原始信号
	/// @param org_srack_info 原始信号堆栈
	void node_run_info_clear_signal( NodeDirector *signal_obj_ptr, const SrackInfo &srack_info, NodeRunInfo *clear_obj, const SrackInfo &org_srack_info );
};

#endif // NODEDIRECTOR_H_H_HEAD__FILE__
