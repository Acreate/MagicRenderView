#ifndef DEBUGNODEINFOWIDGET_H_H_HEAD__FILE__
#define DEBUGNODEINFOWIDGET_H_H_HEAD__FILE__
#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class DebugInfoNode;
class DebugNodeInfoWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	DebugInfoNode *debugInfoNode;
public:
	DebugNodeInfoWidget( );
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
};

#endif // DEBUGNODEINFOWIDGET_H_H_HEAD__FILE__
