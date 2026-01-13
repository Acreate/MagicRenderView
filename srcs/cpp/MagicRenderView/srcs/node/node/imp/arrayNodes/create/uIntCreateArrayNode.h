#ifndef UINTCREATEARRAYNODE_H_H_HEAD__FILE__
#define UINTCREATEARRAYNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class UIntVectorOutputPort;
class UIntCreateArrayNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	UIntVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	UIntCreateArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/生成/无符号整数序列" ) );
};
#endif // UINTCREATEARRAYNODE_H_H_HEAD__FILE__
