#ifndef JUMPNODEEDITOR_H_H_HEAD__FILE__
#define JUMPNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class JumpNodeWidgetItem;
class QVBoxLayout;
class NodeRefLinkInfo;
class JumpNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	std::vector< NodeRefLinkInfo * > beginNodeRefLinkVector;
	std::vector< NodeRefLinkInfo * > processNodeRefLinkVector;
	std::vector< NodeRefLinkInfo * > endNodeRefLinkVector;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	std::vector< JumpNodeWidgetItem * > unionJumpNodeVector;
protected:
	void releaseResource( ) override;
	virtual bool createJumpItem( Node *node_ref_link_info );
public:
	JumpNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	
public:
	class JumpWidgetInfoTools {
	protected:
		/// @brief 匹配输入的节点路径
		/// @param analysis_node_ref_link_info 查找的路径
		/// @param result_input_node_ref_map 输入依赖列表
		/// @param result_node_ref_link_vector 返回路径列表
		/// @return 失败返回 false
		static bool findPoint( Node *analysis_node_ref_link_info, std::vector< std::pair< Node *, Node * > > &result_input_node_ref_map, std::vector< Node * > &result_node_ref_link_vector );
	public:
		/// @brief 填充依赖到指定序列当中，
		/// @param analysis_node_ref_link_info 依据的依赖对象
		/// @param result_node_ref_link_vector 填充依赖返回(输入/输出)
		static bool analysisJumpNodeRef( Node *analysis_node_ref_link_info, std::vector< std::vector< Node * > > &result_node_ref_link_vector );
	};

	class PointWidgetInfoTools {
	public:
		/// @brief 解析节点输出依赖，从而获取 Jump 节点
		/// @param analysis_node_ref_link_info 解析节点
		/// @param result_node_ref_link_vector 返回 Jump 节点列表
		/// @return 不存在返回 false
		static bool findJumNodeRef( Node * analysis_node_ref_link_info, std::vector< Node * > &result_node_ref_link_vector );
	};
	
};

#endif // JUMPNODEEDITOR_H_H_HEAD__FILE__
