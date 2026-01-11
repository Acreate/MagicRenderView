#ifndef CONBINATIONIMAGEARRAYNODE_H_H_HEAD__FILE__
#define CONBINATIONIMAGEARRAYNODE_H_H_HEAD__FILE__

#include <node/node/cacheNode.h>

class ImageCacheInputPort;
class ImageCacheOutputPort;
class ImageVectorOutputPort;
class AnyVarInputPort;
class AnyVarOutputPort;
class IntVectorInputPort;
class IntOutputPort;
class ConbinationImageArrayNode : public CacheNode {
	Q_OBJECT;
protected:
	ImageCacheInputPort *cacheInputPort;
	ImageVectorOutputPort *vectorOutPortPtr;
	AnyVarInputPort *anyInputPort;
	AnyVarOutputPort *anyOutputPort;
	std::vector< QImage > *outVarPtr;
	std::vector< Node * > adviseNextNodeVector;
public:
	ConbinationImageArrayNode( const QString &node_name );
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
	Def_Extend_NodeTypeName( Node::tr( "缓存/组成/图像序列" ) );
};
#endif // CONBINATIONIMAGEARRAYNODE_H_H_HEAD__FILE__
