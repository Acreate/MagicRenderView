#ifndef IMAGECHANNELNODE_H_H_HEAD__FILE__
#define IMAGECHANNELNODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class ImageInputPort;
class ColorVectorOutputPort;
class AnyVarInputPort;
class ImageChannelNode : public ProcessNode {
	Q_OBJECT;
protected:
	ImageInputPort *imageInputPortPtr;
	ColorVectorOutputPort *redOutputPort;
	ColorVectorOutputPort *greenOutputPort;
	ColorVectorOutputPort *blueOutputPort;
	ColorVectorOutputPort *alphaOutputPort;

	std::vector< QColor > *redOutVectorVarPtr;
	std::vector< QColor > *greenOutVectorVarPtr;
	std::vector< QColor > *blueOutVectorVarPtr;
	std::vector< QColor > *alphaOutVectorVarPtr;
public:
	ImageChannelNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "图像/切分通道" ) );
};
#endif // IMAGECHANNELNODE_H_H_HEAD__FILE__
