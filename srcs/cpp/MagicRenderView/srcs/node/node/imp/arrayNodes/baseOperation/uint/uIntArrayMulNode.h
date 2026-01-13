#ifndef UINTARRAYMULNODE_H_H_HEAD__FILE__
#define UINTARRAYMULNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class UIntVectorOutputPort;
class UIntVectorInputPort;
class UIntOutputPort;
class UIntInputPort;
class UIntArrayMulNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	UIntVectorInputPort *firstInputPort;
	UIntInputPort *secondInputPort;
	UIntVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	UIntArrayMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/运算/无符号整数/乘法" ) );
};

#endif // UINTARRAYMULNODE_H_H_HEAD__FILE__
