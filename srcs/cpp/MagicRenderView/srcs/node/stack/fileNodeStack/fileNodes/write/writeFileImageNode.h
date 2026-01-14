#ifndef WRITEFILEIMAGENODE_H_H_HEAD__FILE__
#define WRITEFILEIMAGENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringInputPort;
class ImageInputPort;
class WriteFileImageNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *writeFilePathPort;
	ImageInputPort *writeImagePort;
public:
	WriteFileImageNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "写入文件/图像" ) );
};
#endif // WRITEFILEIMAGENODE_H_H_HEAD__FILE__
