#ifndef STARTNODEWIDGET_H_H_HEAD__FILE__
#define STARTNODEWIDGET_H_H_HEAD__FILE__

#include "../../nodeInfoWidget.h"
#include "startNodeEditor.h"

class StartNodeItem;
class StartNodeWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	StartNodeEditor *startNodeEditor;
public:
	StartNodeWidget( );
	bool initNodeInfo( Node *check_node_ptr ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
protected:
	void updateLayout( ) override;
};
#endif // STARTNODEWIDGET_H_H_HEAD__FILE__
