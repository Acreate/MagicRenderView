#ifndef CONBINATIONINTARRAYNODE_H_H_HEAD__FILE__
#define CONBINATIONINTARRAYNODE_H_H_HEAD__FILE__

#include <node/node/cacheNode.h>

class IntCacheInputPort;
class IntVectorOutputPort;
class AnyVarInputPort;
class AnyVarOutputPort;
class IntVectorInputPort;
class IntOutputPort;
class ConbinationIntArrayNode : public CacheNode {
	Q_OBJECT;
protected:
	IntCacheInputPort* cacheInputPort;
	IntVectorOutputPort *vectorOutPortPtr;
	AnyVarInputPort *anyInputPort;
	AnyVarOutputPort *anyOutputPort;
	std::vector< int64_t > *outVarPtr;
	std::vector< Node * > adviseNextNodeVector;
public:
	ConbinationIntArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) override {
		result_next_run_advise_node_vector = adviseNextNodeVector;
		return true;
	}
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "缓存/组成/整数序列" ) );
};
#endif // CONBINATIONINTARRAYNODE_H_H_HEAD__FILE__
