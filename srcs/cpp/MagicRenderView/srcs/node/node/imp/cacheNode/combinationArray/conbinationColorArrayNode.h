#ifndef CONBINATIONCOLORARRAYNODE_H_H_HEAD__FILE__
#define CONBINATIONCOLORARRAYNODE_H_H_HEAD__FILE__

#include <node/node/cacheNode.h>

class IntVectorInputPort;
class IntOutputPort;
class ConbinationColorArrayNode : public CacheNode {
	Q_OBJECT;
protected:
	IntOutputPort *intOutputPort;
	IntVectorInputPort *intVectorInputPort;
	int64_t* addResultVar;
public:
	ConbinationColorArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "缓存/组成/颜色序列" ) );
};
#endif // CONBINATIONCOLORARRAYNODE_H_H_HEAD__FILE__
