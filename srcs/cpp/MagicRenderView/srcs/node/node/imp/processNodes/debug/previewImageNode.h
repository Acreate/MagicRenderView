#ifndef PREVIEWIMAGENODE_H_H_HEAD__FILE__
#define PREVIEWIMAGENODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class ImageInputPort;
class AnyVarInputPort;
class PreviewImageNode : public ProcessNode {
	Q_OBJECT;
protected:
	ImageInputPort *imageInputPortPtr;
public:
	PreviewImageNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "调试/图像预览" ) );
};
#endif // PREVIEWIMAGENODE_H_H_HEAD__FILE__
