#ifndef IMAGEDIVNODE_H_H_HEAD__FILE__
#define IMAGEDIVNODE_H_H_HEAD__FILE__


#include <node/node/unityNode.h>
class ImageOutputPort;
class ImageInputPort;
class ImageDivNode : public UnityNode {
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
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/无符号整数/加法" ) );
};
#endif // IMAGEDIVNODE_H_H_HEAD__FILE__
