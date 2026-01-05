#ifndef STARTNODE_H_H_HEAD__FILE__
#define STARTNODE_H_H_HEAD__FILE__
#pragma once
#include "../../beginNode.h"

class StartNode : public BeginNode {
	Q_OBJECT;
public:
	StartNode( const QString &node_name )
		: BeginNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readNodeRunData( ) override;
	bool fillInputPortCall( std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "起始/开始" ) );
};

#endif // STARTNODE_H_H_HEAD__FILE__
