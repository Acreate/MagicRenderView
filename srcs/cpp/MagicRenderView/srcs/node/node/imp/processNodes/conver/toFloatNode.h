#ifndef TOFLOATNODE_H_H_HEAD__FILE__
#define TOFLOATNODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class ToFloatNode : public ProcessNode {
	Q_OBJECT;
public:
	ToFloatNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/浮点" ) );
};
#endif // TOFLOATNODE_H_H_HEAD__FILE__
