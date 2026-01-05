#ifndef GOTONODE_H_H_HEAD__FILE__
#define GOTONODE_H_H_HEAD__FILE__
#pragma once
#include "../../jumpNode.h"

class GotoNode : public JumpNode {
	Q_OBJECT;
public:
	GotoNode( const QString &node_name )
		: JumpNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readNodeRunData( ) override;
	bool fillInputPortCall( std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "跳转/跳转位置" ) );
};

#endif // GOTONODE_H_H_HEAD__FILE__
