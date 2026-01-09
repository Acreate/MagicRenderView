#ifndef BEGINNODEEDITOR_H_H_HEAD__FILE__
#define BEGINNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class QVBoxLayout;
class BeginNodeItem;
class BeginNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	Node *beginNodeRefLinkInfo;
	std::vector< Node * > beginNodeRefLinkVector;
	std::vector< Node * > processNodeRefLinkVector;
	std::vector< Node * > endNodeRefLinkVector;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	BeginNodeItem *beginItem;
	BeginNodeItem *processItem;
	BeginNodeItem *endItem;
	NodeInfoWidget *leftWidget;
	NodeInfoWidget *rightWidget;
public:
	BeginNodeEditor( NodeInfoWidget *parent );
	~BeginNodeEditor( ) override;
	bool initNode( Node *init_node ) override;
protected:
	virtual bool findRefBeginNode( Node *start_find_current_node, Node * &result_begin_node );
	virtual bool analysisNodeRef( Node *begin_node_ref_link_info, std::vector< Node * > &result_node_ref_link_vector );
	virtual bool analysisOutputPortRefNodeVector( Node *foreach_output_port_node, std::vector< Node * > &result_node_ref_link_vector );
	virtual bool analysisInputPortRefNodeVector( Node *foreach_output_port_node, std::vector< Node * > &result_node_ref_link_vector );
	virtual bool sortProcessNodeRefArray( const std::vector< Node * >::pointer &sort_target_array_ptr, const size_t &sort_target_array_count );
protected:
	void releaseResource( ) override;
public:
Q_SIGNALS:
	void clickNodeItem( Node *click_node );
};

#endif // BEGINNODEEDITOR_H_H_HEAD__FILE__
