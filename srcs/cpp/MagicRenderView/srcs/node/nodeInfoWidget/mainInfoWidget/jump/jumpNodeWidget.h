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
	JumpNodeWidget( );
	bool initNodeInfo( Node *check_node_ptr ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
};

#endif // JUMPNODEWIDGET_H_H_HEAD__FILE__
