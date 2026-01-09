#ifndef BEGINNODEWIDGET_H_H_HEAD__FILE__
#define BEGINNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class NodeRefLinkInfo;
class BeginNodeEditor;
class BeginNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	BeginNodeEditor *beginNodeEditor;
public:
	BeginNodeWidget( );
	bool initNodeInfo( Node *check_node_ptr ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
};

#endif // BEGINNODEWIDGET_H_H_HEAD__FILE__
