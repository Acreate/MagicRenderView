#ifndef UINTARRAYMODNODE_H_H_HEAD__FILE__
#define UINTARRAYMODNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class UIntVectorInputPort;
class UIntVectorOutputPort;
class UIntOutputPort;
class UIntInputPort;
class UIntArrayModNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	UIntVectorInputPort *firstInputPort;
	UIntInputPort *secondInputPort;
	UIntVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	UIntArrayModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/序列/无符号整数/求余" ) );
};

#endif // UINTARRAYMODNODE_H_H_HEAD__FILE__
