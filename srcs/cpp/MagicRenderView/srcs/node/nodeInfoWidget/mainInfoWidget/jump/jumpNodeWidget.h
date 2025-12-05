#ifndef JUMPNODEWIDGET_H_H_HEAD__FILE__
#define JUMPNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class JumpNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
public:
	JumpNodeWidget( MainWindow *parent )
		: NodeInfoWidget( parent ) { }
	bool isNodeInfo( Node *check_node_ptr ) override;
	bool isNodeTypeInfoWidget( Node *check_node_ptr ) const override;
protected:
	void okButtonEvent( ) override{}
	void cancelButtonEvent( ) override{}
};

#endif // JUMPNODEWIDGET_H_H_HEAD__FILE__
