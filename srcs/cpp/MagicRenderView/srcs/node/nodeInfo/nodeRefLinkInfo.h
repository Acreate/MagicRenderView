#ifndef NODEREFLINKINFO_H_H_HEAD__FILE__
#define NODEREFLINKINFO_H_H_HEAD__FILE__
#pragma once
#include <vector>

#include "../node/pointNode.h"

class DrawNodeWidget;
class DrawLinkWidget;
class NodePortLinkInfo;
class OutputPort;
class InputPort;
class Node;
class NodeRefLinkInfo : public QObject {
	Q_OBJECT;
	friend class NodePortLinkInfo;
	friend class NodeDirector;
	friend class NodeRefLinkInfoTools;
protected:
	/// @brief 匹配节点
	Node *currentNode;
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
	/// @brief 节点操作菜单
	QMenu *managementLinkMenu;
protected:
	virtual void linkRelease( NodeRefLinkInfo *release_target_node_ref_link_info );
	virtual void removeInputNodeRef( NodeRefLinkInfo *remove );
	virtual void removeOutputNodeRef( NodeRefLinkInfo *remove );
public:
	NodeRefLinkInfo( Node *current_node );
	~NodeRefLinkInfo( ) override;
	virtual bool appendInputRef( OutputPort *output_port, NodeRefLinkInfo *in_put_ref, InputPort *input_port );
	virtual bool removeInputRef( OutputPort *output_port, NodeRefLinkInfo *in_put_ref, InputPort *input_port );
	virtual bool hasLinkInfo( OutputPort *output_port, InputPort *input_port );
	virtual DrawLinkWidget * getDrawLinkWidget( ) const { return drawLinkWidget; }
	virtual DrawNodeWidget * getDrawNodeWidget( ) const { return drawNodeWidget; }
	virtual Node * getCurrentNode( ) const { return currentNode; }
	virtual QMenu * getManagementLinkMenu( ) const { return managementLinkMenu; }
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_node 释放对象指针
	/// @param srack_info 信号行
	void release_NodeRefLinkInfo_signal( NodeRefLinkInfo *release_node, const SrackInfo &srack_info );
};
class NodeRefLinkInfoTools {
	friend class NodeDirector;
	friend class NodePortLinkInfo;
	friend class MainWidget;
	friend class NodeDirector;
	static void setDrawLinkWidget( NodeRefLinkInfo *set_obj, DrawLinkWidget *draw_link_widget ) {
		set_obj->drawLinkWidget = draw_link_widget;
	}
	static void setDrawNodeWidget( NodeRefLinkInfo *set_obj, DrawNodeWidget *draw_node_widget ) {
		set_obj->drawNodeWidget = draw_node_widget;

	}
};
#endif // NODEREFLINKINFO_H_H_HEAD__FILE__
