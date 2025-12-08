#ifndef POINTNODEWIDGET_H_H_HEAD__FILE__
#define POINTNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class PointNodeEditor;
class PointNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	PointNodeEditor* pointNodeEditor;
public:
	PointNodeWidget( MainWindow *parent );
	bool initNodeInfo( Node *check_node_ptr ) override;
	bool isNodeTypeInfoWidget( Node *check_node_ptr ) const override;

};

#endif // POINTNODEWIDGET_H_H_HEAD__FILE__
