#ifndef RESULTNODE_H_H_HEAD__FILE__
#define RESULTNODE_H_H_HEAD__FILE__
#pragma once
#include "../../endNode.h"

class ResultNode : public EndNode {
	Q_OBJECT;
public:
	ResultNode( const QString &node_name )
		: EndNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readNodeRunData( ) override;
	bool fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "结束/返回" ) );

};

#endif // RESULTNODE_H_H_HEAD__FILE__
