#ifndef UINTARRAYSUBNODE_H_H_HEAD__FILE__
#define UINTARRAYSUBNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>

class IntVectorInputPort;
class IntOutputPort;
class UIntArraySubNode : public ArrayNode {
	Q_OBJECT;
protected:
	IntOutputPort *intOutputPort;
	IntVectorInputPort *intVectorInputPort;
	int64_t* addResultVar;
public:
	UIntArraySubNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "数组/无符号整数/序列减" ) );
};

#endif // UINTARRAYSUBNODE_H_H_HEAD__FILE__
