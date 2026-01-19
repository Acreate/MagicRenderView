#ifndef BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class BinCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class BinCreateUnityNodeEditorWidget;
protected:
	BinCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
};

#endif // BINCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
