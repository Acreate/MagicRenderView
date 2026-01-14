#ifndef UINTARRAYSELFMULNODE_H_H_HEAD__FILE__
#define UINTARRAYSELFMULNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntVectorInputPort;
class UIntOutputPort;
class UIntArraySelfMulNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	UIntVectorInputPort *firstInputPort;
	UIntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	UIntArraySelfMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/自运算/无符号整数/乘法" ) );
};

#endif // UINTARRAYSELFMULNODE_H_H_HEAD__FILE__
