#ifndef CONBINATIONUINTARRAYNODE_H_H_HEAD__FILE__
#define CONBINATIONUINTARRAYNODE_H_H_HEAD__FILE__

#include <node/node/cacheNode.h>

class UIntCacheInputPort;
class UIntVectorOutputPort;
class UIntOutputPort;
class AnyVarOutputPort;
class AnyVarInputPort;
class IntVectorInputPort;
class IntOutputPort;
class ConbinationUIntArrayNode : public CacheNode {
	Q_OBJECT;
protected:
	UIntCacheInputPort* cacheInputPort;
	UIntVectorOutputPort *vectorOutPortPtr;
	AnyVarInputPort *anyInputPort;
	AnyVarOutputPort *anyOutputPort;
	std::vector< uint64_t > *outVarPtr;
	std::vector<Node*> adviseNextNodeVector;
public:
	ConbinationUIntArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillOutputPortCall( std::vector<Node *> &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) override;
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "缓存/组成/无符号序列" ) );
};
#endif // CONBINATIONUINTARRAYNODE_H_H_HEAD__FILE__
