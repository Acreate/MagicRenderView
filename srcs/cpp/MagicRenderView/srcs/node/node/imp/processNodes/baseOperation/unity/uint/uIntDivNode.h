#ifndef UINTDIVNODE_H_H_HEAD__FILE__
#define UINTDIVNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntOutputPort;
class UIntInputPort;
class UIntDivNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	UIntInputPort *firstInputPort;
	UIntInputPort *secondInputPort;
	UIntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	UIntDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "单元/运算/无符号整数/除法" ) );
};

#endif // UINTDIVNODE_H_H_HEAD__FILE__
