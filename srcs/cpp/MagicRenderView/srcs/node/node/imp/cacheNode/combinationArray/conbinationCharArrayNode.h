#ifndef CONBINATIONCHARARRAYNODE_H_H_HEAD__FILE__
#define CONBINATIONCHARARRAYNODE_H_H_HEAD__FILE__

#include <node/node/cacheNode.h>

class AnyVarOutputPort;
class AnyVarInputPort;
class CharVectorOutputPort;
class CharOutputPort;
class CharCacheInputPort;
class IntVectorInputPort;
class IntOutputPort;
class ConbinationCharArrayNode : public CacheNode {
	Q_OBJECT;
protected:
	CharCacheInputPort* cacheInputPort;
	CharVectorOutputPort *vectorOutPortPtr;
	AnyVarInputPort *anyInputPort;
	AnyVarOutputPort *anyOutputPort;
	std::vector< QChar > *outVarPtr;
	std::vector< Node * > adviseNextNodeVector;
public:
	ConbinationCharArrayNode( const QString &node_name );
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
	Def_Extend_NodeTypeName( Node::tr( "缓存/组成/字符序列" ) );
};
#endif // CONBINATIONCHARARRAYNODE_H_H_HEAD__FILE__
