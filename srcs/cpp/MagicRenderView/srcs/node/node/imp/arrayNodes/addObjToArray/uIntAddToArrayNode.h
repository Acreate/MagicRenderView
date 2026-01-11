#ifndef UINTADDTOARRAYNODE_H_H_HEAD__FILE__
#define UINTADDTOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class UIntVectorOutputPort;
class UIntInputPort;
class UIntAddToArrayNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	UIntInputPort *firstInputPort;
	UIntVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	UIntAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "组合/序列/无符号整数" ) );
};
#endif // UINTADDTOARRAYNODE_H_H_HEAD__FILE__
