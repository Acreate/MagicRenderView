#ifndef PATHGETONPATHINFOARRAYNODE_H_H_HEAD__FILE__
#define PATHGETONPATHINFOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringVectorOutputPort;
class StringInputPort;
class PathGetOnPathInfoArrayNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *pathInputPortPtr;
	StringVectorOutputPort *pathSubPathOutputPortPtr;
	StringVectorOutputPort *dirPathOutputPortPtr;
	StringVectorOutputPort *filePathOutputPortPtr;

	std::vector< QString > *pathSubPathOutputVarPtr;
	std::vector< QString > *dirPathOutputVarPtr;
	std::vector< QString > *filePathOutputVarPtr;
public:
	PathGetOnPathInfoArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/获取文件与目录" ) );
};
#endif // PATHGETONPATHINFOARRAYNODE_H_H_HEAD__FILE__
