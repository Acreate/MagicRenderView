#ifndef JUMPNODEWIDGET_H_H_HEAD__FILE__
#define JUMPNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../nodeInfoWidget.h"

class JumpNodeEditor;
class JumpNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	JumpNodeEditor* jumpNodeEditor;
public:
	JumpNodeWidget( MainWindow *parent );
	bool initNodeInfo( Node *check_node_ptr ) override;
	bool isNodeTypeInfoWidget( Node *check_node_ptr ) const override;

};

#endif // JUMPNODEWIDGET_H_H_HEAD__FILE__
