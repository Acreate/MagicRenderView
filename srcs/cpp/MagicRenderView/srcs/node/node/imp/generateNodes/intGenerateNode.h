#ifndef INTGENERATENODE_H_H_HEAD__FILE__
#define INTGENERATENODE_H_H_HEAD__FILE__
#pragma once
#include "../../generateNode.h"

class IntGenerateNode : public GenerateNode {
	Q_OBJECT;
protected:
	std::vector< int64_t > *overVarPtr;
public:
	IntGenerateNode( const QString &node_name )
		: GenerateNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool initArrayUintyTypeName( QString &change_array_unty_type_name ) override;
	bool updateLayout( ) override;
	virtual std::vector< int64_t > * getGenerateVarPtr( ) const;
	bool formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) override;
	bool toUint8VectorData( std::vector< uint8_t > &result_vector_data ) override;
protected:
	bool initVarPtr( ) override;
public:
	bool readNodeRunData( ) override;
	bool fillInputPortCall( std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "生成/生成整数" ) );
};

#endif // INTGENERATENODE_H_H_HEAD__FILE__
