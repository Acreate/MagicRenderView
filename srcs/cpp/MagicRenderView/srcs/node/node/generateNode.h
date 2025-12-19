#ifndef GENERATENODE_H_H_HEAD__FILE__
#define GENERATENODE_H_H_HEAD__FILE__
#pragma once
#include "node.h"

class GenerateNode : public Node {
	Q_OBJECT;
protected:
	virtual bool initVarPtr( ) = 0;
public:
	GenerateNode( const QString &node_name );
	~GenerateNode( ) override;
	bool init( DrawNodeWidget *parent ) override;

	virtual bool initArrayUintyTypeName( QString &change_array_unty_type_name ) = 0;
	NodeEnum::NodeType getNodeType( ) const override {
		return NodeEnum::NodeType::Generate;
	}
	bool formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) override;
	bool toUint8VectorData( std::vector< uint8_t > &result_vector_data ) override;
};

#endif // GENERATENODE_H_H_HEAD__FILE__
