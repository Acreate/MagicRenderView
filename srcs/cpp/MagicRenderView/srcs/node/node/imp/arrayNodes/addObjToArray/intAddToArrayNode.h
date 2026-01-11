#ifndef INTADDTOARRAYNODE_H_H_HEAD__FILE__
#define INTADDTOARRAYNODE_H_H_HEAD__FILE__


#include <node/node/arrayNode.h>
class IntInputPort;
class IntVectorOutputPort;
class IntAddToArrayNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntInputPort *firstInputPort;
	IntVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	IntAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "组合/序列/整数" ) );
};
#endif // INTADDTOARRAYNODE_H_H_HEAD__FILE__
