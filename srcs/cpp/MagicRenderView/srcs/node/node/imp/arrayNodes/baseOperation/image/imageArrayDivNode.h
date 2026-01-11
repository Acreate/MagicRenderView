#ifndef IMAGEARRAYDIVNODE_H_H_HEAD__FILE__
#define IMAGEARRAYDIVNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class ImageVectorInputPort;
class ImageInputPort;
class ImageVectorOutputPort;
class ImageArrayDivNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageVectorInputPort *firstInputPort;
	ImageInputPort *secondInputPort;
	ImageVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ImageArrayDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/序列/图像/除法" ) );
};

#endif // IMAGEARRAYDIVNODE_H_H_HEAD__FILE__
