#ifndef PREVIEWIMAGENODE_H_H_HEAD__FILE__
#define PREVIEWIMAGENODE_H_H_HEAD__FILE__
#include <node/node/processNode.h>

class ImageInputPort;
class AnyVarInputPort;
class PreviewImageNode : public ProcessNode {
	Q_OBJECT;
protected:
	ImageInputPort *imageInputPortPtr;
	std::vector< QImage > imageVector;
public:
	PreviewImageNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "预览/图像" ) );
};
#endif // PREVIEWIMAGENODE_H_H_HEAD__FILE__
