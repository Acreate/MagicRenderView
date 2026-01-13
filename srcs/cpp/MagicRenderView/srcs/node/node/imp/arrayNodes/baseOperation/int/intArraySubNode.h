#ifndef INTARRAYSUBNODE_H_H_HEAD__FILE__
#define INTARRAYSUBNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class IntVectorInputPort;
class IntVectorOutputPort;
class IntOutputPort;
class IntInputPort;
class IntArraySubNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntVectorInputPort *firstInputPort;
	IntInputPort *secondInputPort;
	IntVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	IntArraySubNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/运算/整数/减法" ) );
};

#endif // INTARRAYSUBNODE_H_H_HEAD__FILE__
