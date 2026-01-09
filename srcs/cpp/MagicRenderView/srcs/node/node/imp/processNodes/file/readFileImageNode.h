#ifndef READFILEIMAGENODE_H_H_HEAD__FILE__
#define READFILEIMAGENODE_H_H_HEAD__FILE__
#pragma once


#include "../../../processNode.h"
class ReadFileImageNode : public ProcessNode {
	Q_OBJECT;
public:
	ReadFileImageNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "文件/读取/图像" ) );
};
#endif // READFILEIMAGENODE_H_H_HEAD__FILE__
