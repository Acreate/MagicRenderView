#ifndef READFILEIMAGENODE_H_H_HEAD__FILE__
#define READFILEIMAGENODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>
class StringInputPort;
class ImageOutputPort;
class ReadFileImageNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort* filePathPort;
	ImageOutputPort* imageOutputPort;
	QImage* outVarPtr;
public:
	ReadFileImageNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "读取文件/图像" ) );
};
#endif // READFILEIMAGENODE_H_H_HEAD__FILE__
