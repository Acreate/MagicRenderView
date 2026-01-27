#ifndef IMAGECREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
#define IMAGECREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h>

class ImageCreateUnityNode;
class ImageCreateUnityNodeEditorScrollArea;
class ImageCreateUnityNodeEditorWidget : public NodeInfoWidget {
	Q_OBJECT;
protected:
	ImageCreateUnityNode *createBinNode;
	ImageCreateUnityNodeEditorScrollArea *imageCreateUnityNodeEditorScrollArea;
	QImage *bindVarPtr;
	QImage buffValue;
protected:
	virtual void valueChange( QImage new_value );
public:
	ImageCreateUnityNodeEditorWidget( ImageCreateUnityNode *create_bin_node, QImage *bind_var_ptr );
	~ImageCreateUnityNodeEditorWidget( ) override;
	bool checkNodeValid( Node *check_node_ptr ) override;
	bool initNodeInfo( Node *check_node_ptr ) override;
	
protected:
	void okButtonEvent( ) override;
};
#endif // IMAGECREATEUNITYNODEEDITORWIDGET_H_H_HEAD__FILE__
