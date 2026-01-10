#ifndef TOUINTNODE_H_H_HEAD__FILE__
#define TOUINTNODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class ToUIntNode : public ProcessNode {
	Q_OBJECT;
public:
	ToUIntNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/无符号整数" ) );
};
#endif // TOUINTNODE_H_H_HEAD__FILE__
