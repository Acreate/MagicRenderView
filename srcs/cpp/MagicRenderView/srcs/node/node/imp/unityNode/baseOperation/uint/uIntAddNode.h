#ifndef UINTADDNODE_H_H_HEAD__FILE__
#define UINTADDNODE_H_H_HEAD__FILE__

#include <node/node/unityNode.h>

class UIntOutputPort;
class UIntInputPort;
class UIntAddNode : public UnityNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	UIntInputPort *firstInputPort;
	UIntInputPort *secondInputPort;
	UIntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	UIntAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/无符号整数/加法" ) );
};

#endif // UINTADDNODE_H_H_HEAD__FILE__
