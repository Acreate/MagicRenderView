#ifndef WRITEFILEBINDATANODE_H_H_HEAD__FILE__
#define WRITEFILEBINDATANODE_H_H_HEAD__FILE__
#pragma once

#include "../../../processNode.h"
class WriteFileBinDataNode : public ProcessNode {
	Q_OBJECT;
public:
	WriteFileBinDataNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "文件/写入/二进制" ) );
};
#endif // WRITEFILEBINDATANODE_H_H_HEAD__FILE__
