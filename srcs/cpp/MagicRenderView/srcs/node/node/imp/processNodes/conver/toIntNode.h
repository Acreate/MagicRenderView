#ifndef TOINTNODE_H_H_HEAD__FILE__
#define TOINTNODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class ToIntNode : public ProcessNode {
	Q_OBJECT;
public:
	ToIntNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/整数" ) );
};
#endif // TOINTNODE_H_H_HEAD__FILE__
