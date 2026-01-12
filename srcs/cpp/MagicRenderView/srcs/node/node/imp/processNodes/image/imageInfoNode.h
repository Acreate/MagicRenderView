#ifndef IMAGEINFONODE_H_H_HEAD__FILE__
#define IMAGEINFONODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class StringOutputPort;
class UIntOutputPort;
class ImageInputPort;
class ImageInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	ImageInputPort *imageInputPortPtr;
	UIntOutputPort *widthOutputPortPtr;
	UIntOutputPort *heightOutputPortPtr;
	StringOutputPort *fromatOutputPortPtr;
	uint64_t *width;
	uint64_t *height;
	QString *fromat;
public:
	ImageInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "图像/图像信息" ) );
};
#endif // IMAGEINFONODE_H_H_HEAD__FILE__
