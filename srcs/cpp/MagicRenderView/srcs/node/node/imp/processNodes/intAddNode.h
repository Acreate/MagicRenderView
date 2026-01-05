#ifndef INTADDNODE_H_H_HEAD__FILE__
#define INTADDNODE_H_H_HEAD__FILE__
#pragma once
#include "../../processNode.h"

class IntAddNode : public ProcessNode {
	Q_OBJECT;
public:
	IntAddNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readNodeRunData( ) override;
	bool fillInputPortCall( std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "数值运算/整数加法" ) );
};

#endif // INTADDNODE_H_H_HEAD__FILE__
