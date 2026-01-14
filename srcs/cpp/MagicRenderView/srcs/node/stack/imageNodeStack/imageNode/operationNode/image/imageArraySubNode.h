#ifndef IMAGEARRAYSUBNODE_H_H_HEAD__FILE__
#define IMAGEARRAYSUBNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ImageVectorOutputPort;
class ImageInputPort;
class ImageVectorInputPort;
class ImageArraySubNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageVectorInputPort *firstInputPort;
	ImageInputPort *secondInputPort;
	ImageVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ImageArraySubNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "图像/序列/减法" ) );
};

#endif // IMAGEARRAYSUBNODE_H_H_HEAD__FILE__
