#ifndef DEBUGNODEEDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
#define DEBUGNODEEDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class OutputPort;
class DebugNodeContentWidget;
class DebugNodeEditorNodeInfoScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class DebugNodeInfoWidget;
protected:
	DebugNodeContentWidget *debugNodeContentWidget;
protected:
	virtual void runToNode_Slot( Node *run_target );
public:
	bool initNode( Node *init_node ) override;
	virtual DebugNodeContentWidget * getDebugNodeContentWidget( ) const { return debugNodeContentWidget; }
protected:
	DebugNodeEditorNodeInfoScrollArea( NodeInfoWidget *parent );
	void releaseResource( ) override;
	void resizeEvent( QResizeEvent * ) override;
};

#endif // DEBUGNODEEDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
