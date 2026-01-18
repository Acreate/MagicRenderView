#ifndef DEBUGNODEEDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
#define DEBUGNODEEDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
#include "../../../../nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h"

class OutputPort;
class DebugNodeContentWidget;
class DebugNodeEditorNodeInfoScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	DebugNodeContentWidget* debugNodeContentWidget;
protected:
	virtual void runToNode_Slot(Node* run_target);
public:
	DebugNodeEditorNodeInfoScrollArea( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual bool appendOutputPort( OutputPort *output_port_ptr, const QString &msg );
	virtual bool clear();
protected:
	void releaseResource( ) override;
	void resizeEvent( QResizeEvent * ) override;
};

#endif // DEBUGNODEEDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
