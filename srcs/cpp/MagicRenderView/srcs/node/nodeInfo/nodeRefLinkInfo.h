#ifndef NODEREFLINKINFO_H_H_HEAD__FILE__
#define NODEREFLINKINFO_H_H_HEAD__FILE__
#pragma once
#include <vector>

#include "../node/pointNode.h"

class DrawHighlightWidget;
class DrawNodeWidget;
class DrawLinkWidget;
class NodePortLinkInfo;
class OutputPort;
class InputPort;
class Node;
class NodeRunInfo;
class NodeRefLinkInfo : public QObject {
	Q_OBJECT;
	friend class NodePortLinkInfo;
	friend class NodeDirector;
	friend class NodeRefLinkInfoTools;
	friend class NodeBuilderTools;
	friend class NodeRunInfo;
protected:
	/// @brief 匹配节点
	Node *currentNode;
	/// @brief 节点绘制后期特效
	DrawHighlightWidget *drawHighlightWidget;
	/// @brief 节点绘制连接窗口
	DrawLinkWidget *drawLinkWidget;
	/// @brief 节点绘制节点窗口
	DrawNodeWidget *drawNodeWidget;
	/// @brief 该节点的输入端口依赖
	NodePortLinkInfo *nodePortLinkInfo;
	/// @brief 保存输入到该节点的依赖节点
	std::vector< NodeRefLinkInfo * > refInputVector;
	/// @brief 保存输出到该节点的依赖节点
	std::vector< NodeRefLinkInfo * > refOutputVector;
protected:
	virtual void clearInfo( );
public:
	NodeRefLinkInfo( Node *current_node );
	~NodeRefLinkInfo( ) override;
	/// @brief 在输入依赖当中，是否已经存在该依赖。
	/// @param node_ref_link_info 检查依赖
	/// @return 存在依赖，则返回 true
	virtual bool hasInputRefNode( NodeRefLinkInfo *node_ref_link_info );
	/// @brief 输入接口连接到输出接口
	/// @param input_port 当前对象节点的输入接口
	/// @param output_port 目标节点的输出接口
	/// @return 成功返回 true
	virtual bool appendInputRef( InputPort *input_port, OutputPort *output_port );
	/// @brief 输入接口断开输出接口
	/// @param input_port 当前对象节点的输入接口
	/// @param output_port 目标节点的输出接口
	/// @return 成功返回 true
	virtual bool removeInputRef( InputPort *input_port, OutputPort *output_port );
	/// @brief 移除输出依赖
	/// @param remove_target 移除目标
	/// @return 成功返回 true
	virtual bool removeInputNodeRef( NodeRefLinkInfo *remove_target );
	/// @brief 移除输入依赖
	/// @param remove_target 移除目标
	/// @return 成功返回 true
	virtual bool removeOutputNodeRef( NodeRefLinkInfo *remove_target );
	/// @brief 检查是否存在输入依赖
	/// @param in_put_ref 检测输入依赖
	/// @return 存在输入依赖，返回 true
	virtual bool hasInputNodeRef( NodeRefLinkInfo *in_put_ref );
	virtual bool hasPortRef( InputPort *input_port, OutputPort *output_port );
	virtual DrawLinkWidget * getDrawLinkWidget( ) const { return drawLinkWidget; }
	virtual DrawNodeWidget * getDrawNodeWidget( ) const { return drawNodeWidget; }
	virtual DrawHighlightWidget * getDrawHighlightWidget( ) const { return drawHighlightWidget; }
	virtual Node * getCurrentNode( ) const { return currentNode; }
Q_SIGNALS:
	void release_node_link_signal( NodeRefLinkInfo *signal_obj_ptr, NodeRefLinkInfo *release_output_node_ref_obj_ptr, const SrackInfo &srack_info );
	void create_node_link_signal( NodeRefLinkInfo *signal_obj_ptr, NodeRefLinkInfo *create_output_node_ref_obj_ptr, const SrackInfo &srack_info );
	void release_port_link_signal( InputPort *input_port, OutputPort *release_output_port, const SrackInfo &srack_info );
	void create_port_link_signal( InputPort *input_port, OutputPort *bind_output_port, const SrackInfo &srack_info );
};
class NodeRefLinkInfoTools {
	friend class NodeDirector;
	friend class NodePortLinkInfo;
	friend class MainWidget;
	friend class NodeDirector;
	static void setDrawHighlightWidget( NodeRefLinkInfo *set_obj, DrawHighlightWidget *draw_highlight_widget ) {
		set_obj->drawHighlightWidget = draw_highlight_widget;
	}
	static void setDrawLinkWidget( NodeRefLinkInfo *set_obj, DrawLinkWidget *draw_link_widget ) {
		set_obj->drawLinkWidget = draw_link_widget;
	}
	static void setDrawNodeWidget( NodeRefLinkInfo *set_obj, DrawNodeWidget *draw_node_widget ) {
		set_obj->drawNodeWidget = draw_node_widget;

	}
};
#endif // NODEREFLINKINFO_H_H_HEAD__FILE__
