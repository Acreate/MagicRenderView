#ifndef IMAGEARRAYADDNODE_H_H_HEAD__FILE__
#define IMAGEARRAYADDNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class ImageVectorInputPort;
class ImageInputPort;
class ImageVectorOutputPort;
class ImageArrayAddNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageVectorInputPort *firstInputPort;
	ImageInputPort *secondInputPort;
	ImageVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ImageArrayAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/序列/图像/加法" ) );
};

#endif // IMAGEARRAYADDNODE_H_H_HEAD__FILE__
