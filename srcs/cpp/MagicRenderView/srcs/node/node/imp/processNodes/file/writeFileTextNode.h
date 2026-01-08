#ifndef WRITEFILETEXTNODE_H_H_HEAD__FILE__
#define WRITEFILETEXTNODE_H_H_HEAD__FILE__

#include "../../../processNode.h"
class WriteFileTextNode : public ProcessNode {
	Q_OBJECT;
public:
	WriteFileTextNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "文件/写入/字符串" ) );
};
#endif // WRITEFILETEXTNODE_H_H_HEAD__FILE__
