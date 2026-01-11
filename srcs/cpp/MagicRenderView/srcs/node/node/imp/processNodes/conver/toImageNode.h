#ifndef TOIMAGENODE_H_H_HEAD__FILE__
#define TOIMAGENODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class AnyVarInputPort;
class ImageOutputPort;
class ToImageNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *anyVarInputPortPtr;
	ImageOutputPort *imageOutputPortPtr;
	QImage *outVarPtr;
public:
	ToImageNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/图像" ) );
};
#endif // TOIMAGENODE_H_H_HEAD__FILE__
