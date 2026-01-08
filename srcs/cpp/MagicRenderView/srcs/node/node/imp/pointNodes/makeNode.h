#ifndef MAKENODE_H_H_HEAD__FILE__
#define MAKENODE_H_H_HEAD__FILE__
#pragma once
#include "../../pointNode.h"

class PointOutputPort;
class MakeNode : public PointNode {
	Q_OBJECT;
protected:
	PointOutputPort *nextNode;
public:
	MakeNode( const QString &node_name )
		: PointNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
	bool fillOutputPortCall( std::vector<Node *> &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "记录/记录位置" ) );
};

#endif // MAKENODE_H_H_HEAD__FILE__
