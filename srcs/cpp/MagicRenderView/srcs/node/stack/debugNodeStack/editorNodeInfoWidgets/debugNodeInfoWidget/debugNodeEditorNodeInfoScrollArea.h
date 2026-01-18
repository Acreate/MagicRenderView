#ifndef DEBUGNODEEDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
#define DEBUGNODEEDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
#include "../../../../nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h"

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
protected:
	void resizeEvent( QResizeEvent * ) override;
};

#endif // DEBUGNODEEDITORNODEINFOSCROLLAREA_H_H_HEAD__FILE__
