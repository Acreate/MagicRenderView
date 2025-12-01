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
class NodeRefLinkInfo {
	friend class NodePortLinkInfo;
	friend class NodeRefLinkInfoTools;
protected:
	Node *currentNode;
	DrawLinkWidget *drawLinkWidget;
	DrawNodeWidget *drawNodeWidget;
	NodePortLinkInfo *nodePortLinkInfo;
	std::vector< NodeRefLinkInfo * > refInputVector;
	std::vector< NodeRefLinkInfo * > refOutputVector;
public:
	NodeRefLinkInfo( Node *current_node );
	virtual ~NodeRefLinkInfo( );
	virtual bool appendInputRef( OutputPort *output_port, NodeRefLinkInfo *in_put_ref, InputPort *input_port );
	virtual bool removeInputRef( OutputPort *output_port, NodeRefLinkInfo *in_put_ref, InputPort *input_port );
	virtual DrawLinkWidget * getDrawLinkWidget( ) const { return drawLinkWidget; }
	virtual DrawNodeWidget * getDrawNodeWidget( ) const { return drawNodeWidget; }
	virtual Node * getCurrentNode( ) const { return currentNode; }
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
