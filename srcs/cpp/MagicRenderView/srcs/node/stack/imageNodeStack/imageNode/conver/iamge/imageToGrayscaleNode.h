#ifndef IMAGETOGRAYSCALENODE_H_H_HEAD__FILE__
#define IMAGETOGRAYSCALENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class ImageToGrayscaleNode : public ProcessNode {
	Q_OBJECT;
protected:
	DynamicTypeInputPort *imageInputPortPtr;
	DynamicTypeOutputPort *imageOutputPortPtr;
	QImage *outImagePtr;
public:
	ImageToGrayscaleNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/图像/转灰度" ) );
};
#endif // IMAGETOGRAYSCALENODE_H_H_HEAD__FILE__
