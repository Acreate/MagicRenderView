#ifndef DEBUGNODEINFOWIDGET_H_H_HEAD__FILE__
#define DEBUGNODEINFOWIDGET_H_H_HEAD__FILE__
#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class DebugNodeEditorNodeInfoScrollArea;
class DebugInfoNode;
class OutputPort;
class InputPort;
class DebugNodeInfoWidget : public NodeInfoWidget {
	Q_OBJECT;
	friend class DebugInfoNode;
protected:
	DebugNodeEditorNodeInfoScrollArea *debugNodeEditorScrallArea;
	DebugInfoNode *debugInfoNode;
protected:
	DebugNodeInfoWidget( DebugInfoNode *debug_info_node );
	virtual bool appendPortInfoMsg( OutputPort *output_port_ptr, const QString &msg );
public:
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
};

#endif // DEBUGNODEINFOWIDGET_H_H_HEAD__FILE__
