#ifndef IMAGEADDTOARRAYNODE_H_H_HEAD__FILE__
#define IMAGEADDTOARRAYNODE_H_H_HEAD__FILE__


#include <node/node/arrayNode.h>
class ImageVectorOutputPort;
class ImageInputPort;
class ImageAddToArrayNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageInputPort *firstInputPort;
	ImageVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ImageAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "组合/序列/图像" ) );
};
#endif // IMAGEADDTOARRAYNODE_H_H_HEAD__FILE__
