#ifndef CONBINATIONCOLORARRAYNODE_H_H_HEAD__FILE__
#define CONBINATIONCOLORARRAYNODE_H_H_HEAD__FILE__

#include <node/node/cacheNode.h>

class ColorCacheInputPort;
class ColorVectorOutputPort;
class AnyVarOutputPort;
class AnyVarInputPort;
class IntVectorInputPort;
class IntOutputPort;
class ConbinationColorArrayNode : public CacheNode {
	Q_OBJECT;
protected:
	ColorCacheInputPort* cacheInputPort;
	ColorVectorOutputPort *vectorOutPortPtr;
	AnyVarInputPort *anyInputPort;
	AnyVarOutputPort *anyOutputPort;
	std::vector< QColor > *outVarPtr;
	std::vector< Node * > adviseNextNodeVector;
public:
	ConbinationColorArrayNode( const QString &node_name );
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
	Def_Extend_NodeTypeName( Node::tr( "缓存/组成/颜色序列" ) );
};
#endif // CONBINATIONCOLORARRAYNODE_H_H_HEAD__FILE__
