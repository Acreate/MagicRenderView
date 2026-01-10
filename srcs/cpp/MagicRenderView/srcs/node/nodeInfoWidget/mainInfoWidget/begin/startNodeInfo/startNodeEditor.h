#ifndef STARTNODEEDITOR_H_H_HEAD__FILE__
#define STARTNODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../../editorNodeInfoScrollArea.h"

class StartNode;
class StartNodeItem;
class QVBoxLayout;
class StartNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	Node *beginNodePtr;
	std::vector< Node * > beginNodeRefLinkVector;
	std::vector< Node * > processNodeRefLinkVector;
	std::vector< Node * > endNodeRefLinkVector;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	StartNodeItem *beginItem;
	StartNodeItem *processItem;
	StartNodeItem *endItem;
public:
	StartNodeEditor( NodeInfoWidget *parent );
	~StartNodeEditor( ) override;
	bool initNode( Node *init_node ) override;
protected:
	virtual bool findRefBeginNode( Node *start_find_current_node, Node * &result_begin_node );
	virtual bool analysisNodeRef( Node *begin_node_ref_link_info, std::vector< Node * > &result_node_ref_link_vector );
	virtual bool analysisOutputPortRefNodeVector( Node *foreach_output_port_node, std::vector< Node * > &result_node_ref_link_vector );
	virtual bool analysisInputPortRefNodeVector( Node *foreach_output_port_node, std::vector< Node * > &result_node_ref_link_vector );
	virtual bool sortProcessNodeRefArray( const std::vector< Node * > &sort_vector, std::vector< Node * > &result_begin_vector, std::vector< Node * > &result_process_vector, std::vector< Node * > &result_end_vector );
protected:
	void releaseResource( ) override;
public:
Q_SIGNALS:
	void clickNodeItem( Node *click_node );
};

#endif // STARTNODEEDITOR_H_H_HEAD__FILE__
