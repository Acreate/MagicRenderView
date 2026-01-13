#ifndef FLOATCREATEARRAYNODE_H_H_HEAD__FILE__
#define FLOATCREATEARRAYNODE_H_H_HEAD__FILE__


#include <node/node/arrayNode.h>
class FloatVectorOutputPort;
class FloatCreateArrayNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	FloatCreateArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/生成/浮点序列" ) );
};
#endif // FLOATCREATEARRAYNODE_H_H_HEAD__FILE__
