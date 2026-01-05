#ifndef IFNODE_H_H_HEAD__FILE__
#define IFNODE_H_H_HEAD__FILE__
#pragma once
#include "../../logicNode.h"

class IfNode : public LogicNode {
	Q_OBJECT;
public:
	IfNode( const QString &node_name )
		: LogicNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readNodeRunData( ) override;
	bool fillInputPortCall( std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "逻辑/分支" ) );
};

#endif // IFNODE_H_H_HEAD__FILE__
