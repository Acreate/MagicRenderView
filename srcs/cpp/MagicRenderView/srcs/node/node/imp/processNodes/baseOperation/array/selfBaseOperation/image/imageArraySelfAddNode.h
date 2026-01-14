#ifndef IMAGEARRAYSELFADDNODE_H_H_HEAD__FILE__
#define IMAGEARRAYSELFADDNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ImageOutputPort;
class ImageVectorInputPort;
class ImageArraySelfAddNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QImage;
protected:
	ImageVectorInputPort *firstInputPort;
	ImageOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	ImageArraySelfAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/自运算/图像/加法" ) );
};
#endif // IMAGEARRAYSELFADDNODE_H_H_HEAD__FILE__
