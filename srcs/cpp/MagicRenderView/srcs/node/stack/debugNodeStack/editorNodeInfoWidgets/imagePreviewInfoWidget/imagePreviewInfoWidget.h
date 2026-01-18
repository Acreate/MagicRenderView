#ifndef IMAGEPREVIEWINFOWIDGET_H_H_HEAD__FILE__
#define IMAGEPREVIEWINFOWIDGET_H_H_HEAD__FILE__
#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class ImagePreviewInfoScrollArea;
class PreviewImageNode;
class ImageOutPortItemScrollWidget;
class OutputPort;
class InputPort;
class ImagePreviewInfoWidget : public NodeInfoWidget {
	Q_OBJECT;
	friend class PreviewImageNode;
protected:
	ImagePreviewInfoScrollArea *previewNodeEditorScrallArea;
	PreviewImageNode *previewImageNode;
	ImageOutPortItemScrollWidget *imageOutPortItemScrollWidget;
protected:
	ImagePreviewInfoWidget( PreviewImageNode *debug_info_node );
	virtual bool appendPortInfoMsg( OutputPort *output_port_ptr, const QImage &image_ref_obj );
	virtual bool clear( );
public:
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
};
#endif // IMAGEPREVIEWINFOWIDGET_H_H_HEAD__FILE__
