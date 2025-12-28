#ifndef NODETYPEINFOSERIALIZEION_H_H_HEAD__FILE__
#define NODETYPEINFOSERIALIZEION_H_H_HEAD__FILE__
#pragma once
#include <cstdint>
#include <vector>
#include <functional>

class VarDirector;
class QString;
class Node;
class NodeTypeInfo;
class NodeTypeInfoSerializeion {
public:
	using TFCreate_Node_Function = std::function< Node*( const QString &, const uint64_t &, const int32_t &, const int32_t & ) >;
	using TFLink_Port_Function = std::function< bool( const uint64_t &, const uint64_t &, const uint64_t &, const uint64_t & ) >;
protected:
	std::vector< Node * > nodeObjPtr;
	Node **nodeObjPtrArrayPtr;
	size_t nodeObjPtrArrayCount;
public:
	NodeTypeInfoSerializeion( );
	virtual ~NodeTypeInfoSerializeion( );
	virtual const std::vector< Node * > & getNodeObjPtr( ) const { return nodeObjPtr; }
	virtual void clearNodeVector( );
	virtual bool appendNodePtr( Node *append_node_ptr );
	virtual bool removeNodePtr( Node *remove_node_ptr );
	virtual bool loadData( size_t &use_count, const uint8_t *src_data_ptr, const size_t &src_data_count, const TFCreate_Node_Function &node_create_function, const TFLink_Port_Function &prot_link_fcuntion );
	virtual bool toData( std::vector< uint8_t > &result_data_vector );
};

#endif // NODETYPEINFOSERIALIZEION_H_H_HEAD__FILE__
