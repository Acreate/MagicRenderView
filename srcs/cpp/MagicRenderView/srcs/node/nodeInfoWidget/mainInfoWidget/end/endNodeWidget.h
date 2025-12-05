#ifndef ENDNODEWIDGET_H_H_HEAD__FILE__
#define ENDNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class EndNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
public:
	EndNodeWidget( MainWindow *parent )
		: NodeInfoWidget( parent ) { }
	bool isNodeInfo( Node *check_node_ptr ) override;
	bool isNodeTypeInfoWidget( Node *check_node_ptr ) const override;
protected:
	void okButtonEvent( ) override{}
	void cancelButtonEvent( ) override{}
};

#endif // ENDNODEWIDGET_H_H_HEAD__FILE__
