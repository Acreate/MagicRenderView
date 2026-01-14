#ifndef IMAGECREATEARRAYNODE_H_H_HEAD__FILE__
#define IMAGECREATEARRAYNODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>
class ImageVectorOutputPort;
class ImageCreateArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ImageCreateArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "创建/序列/图像序列" ) );
};
#endif // IMAGECREATEARRAYNODE_H_H_HEAD__FILE__
