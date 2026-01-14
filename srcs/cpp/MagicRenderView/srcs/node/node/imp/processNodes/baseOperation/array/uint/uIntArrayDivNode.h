#ifndef UINTARRAYDIVNODE_H_H_HEAD__FILE__
#define UINTARRAYDIVNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntVectorInputPort;
class UIntVectorOutputPort;
class UIntOutputPort;
class UIntInputPort;
class UIntArrayDivNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	UIntVectorInputPort *firstInputPort;
	UIntInputPort *secondInputPort;
	UIntVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	UIntArrayDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/序列/无符号整数序列/除法" ) );
};

#endif // UINTARRAYDIVNODE_H_H_HEAD__FILE__
