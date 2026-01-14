#ifndef WRITEFILETEXTNODE_H_H_HEAD__FILE__
#define WRITEFILETEXTNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringInputPort;
class WriteFileTextNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *writeFilePathPort;
	StringInputPort *writeTextPort;
public:
	WriteFileTextNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "文件/写入/字符串" ) );
};
#endif // WRITEFILETEXTNODE_H_H_HEAD__FILE__
