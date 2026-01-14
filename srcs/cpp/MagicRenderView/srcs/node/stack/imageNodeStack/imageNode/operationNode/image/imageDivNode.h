#ifndef IMAGEDIVNODE_H_H_HEAD__FILE__
#define IMAGEDIVNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ImageOutputPort;
class ImageInputPort;
class ImageDivNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageInputPort *firstInputPort;
	ImageInputPort *secondInputPort;
	ImageOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	ImageDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "图像/单元/除法" ) );
};
#endif // IMAGEDIVNODE_H_H_HEAD__FILE__
