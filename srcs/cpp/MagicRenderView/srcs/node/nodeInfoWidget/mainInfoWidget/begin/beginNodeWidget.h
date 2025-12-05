#ifndef BEGINNODEWIDGET_H_H_HEAD__FILE__
#define BEGINNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class BeginNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
public:
	BeginNodeWidget( MainWindow *parent );
	bool isNodeTypeInfoWidget( Node *check_node_ptr ) const override;
	bool isNodeInfo( Node *check_node_ptr ) override;
protected:
	void okButtonEvent( ) override;
	void cancelButtonEvent( ) override;
};

#endif // BEGINNODEWIDGET_H_H_HEAD__FILE__
