#ifndef IMAGEPREVIEWINFOSCROLLAREA_H_H_HEAD__FILE__
#define IMAGEPREVIEWINFOSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class PreviewImageContentWidget;
class ImageOutPortContentToolsWidget;
class OutputPort;
class ImagePreviewInfoScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	PreviewImageContentWidget *previewImageContentWidget;
protected:
	virtual void runToNode_Slot( Node *run_target );
public:
	ImagePreviewInfoScrollArea( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual PreviewImageContentWidget * getPreviewImageContentWidget( ) const { return previewImageContentWidget; }
protected:
	void releaseResource( ) override;
	void resizeEvent( QResizeEvent * ) override;
};

#endif // IMAGEPREVIEWINFOSCROLLAREA_H_H_HEAD__FILE__
