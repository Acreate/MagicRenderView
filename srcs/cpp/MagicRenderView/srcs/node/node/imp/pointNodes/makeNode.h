#ifndef MAKENODE_H_H_HEAD__FILE__
#define MAKENODE_H_H_HEAD__FILE__
#pragma once
#include "../../pointNode.h"

class MakeNode : public PointNode {
	Q_OBJECT;
public:
	MakeNode( const QString &node_name )
		: PointNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readNodeRunData( ) override;
	bool fillInputPortCall( std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "记录/记录位置" ) );
};

#endif // MAKENODE_H_H_HEAD__FILE__
