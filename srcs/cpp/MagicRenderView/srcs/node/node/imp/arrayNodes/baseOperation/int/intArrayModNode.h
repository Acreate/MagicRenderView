#ifndef INTARRAYMODNODE_H_H_HEAD__FILE__
#define INTARRAYMODNODE_H_H_HEAD__FILE__
#include <node/node/arrayNode.h>
class IntVectorInputPort;
class IntVectorOutputPort;
class IntOutputPort;
class IntInputPort;
class IntArrayModNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntVectorInputPort *firstInputPort;
	IntInputPort *secondInputPort;
	IntVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	IntArrayModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/序列/整数/求余" ) );
};

#endif // INTARRAYMODNODE_H_H_HEAD__FILE__
