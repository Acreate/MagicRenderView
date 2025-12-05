#ifndef POINTNODEWIDGET_H_H_HEAD__FILE__
#define POINTNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class PointNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
public:
	PointNodeWidget( MainWindow *parent )
		: NodeInfoWidget( parent ) { }
	bool isNodeInfo( Node *check_node_ptr ) override;
	bool isNodeTypeInfoWidget( Node *check_node_ptr ) const override;
protected:
	void okButtonEvent( ) override { }
	void cancelButtonEvent( ) override { }
};

#endif // POINTNODEWIDGET_H_H_HEAD__FILE__
