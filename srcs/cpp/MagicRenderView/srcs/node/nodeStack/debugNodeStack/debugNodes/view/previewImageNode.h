#ifndef PREVIEWIMAGENODE_H_H_HEAD__FILE__
#define PREVIEWIMAGENODE_H_H_HEAD__FILE__
#include <node/node/processNode.h>

class ImagePreviewInfoWidget;
class ImageInputPort;
class AnyVarInputPort;
class PreviewImageNode : public ProcessNode {
	Q_OBJECT;
protected:
	ImageInputPort *imageInputPortPtr;
	std::vector< QImage > imageVector;
	ImagePreviewInfoWidget *imagePreviewPtr;
public:
	PreviewImageNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
protected:
	bool initNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	void releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) override;
	NodeInfoWidget * getNodeInfoWidget( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // PREVIEWIMAGENODE_H_H_HEAD__FILE__
