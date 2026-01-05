#ifndef INTARRAYADDNODE_H_H_HEAD__FILE__
#define INTARRAYADDNODE_H_H_HEAD__FILE__
#pragma once
#include "../../arrayNode.h"
#include "../../cacheNode.h"

class IntArrayAddNode : public ArrayNode {
	Q_OBJECT;
public:
	IntArrayAddNode( const QString &node_name )
		: ArrayNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readNodeRunData( ) override;
	bool fillInputPortCall( std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "缓存/整数序列和" ) );
};

#endif // INTARRAYADDNODE_H_H_HEAD__FILE__
