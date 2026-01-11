#ifndef FLOATMULNODE_H_H_HEAD__FILE__
#define FLOATMULNODE_H_H_HEAD__FILE__

#include <node/node/unityNode.h>

class FloatOutputPort;
class FloatInputPort;
class FloatMulNode : public UnityNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatInputPort *firstInputPort;
	FloatInputPort *secondInputPort;
	FloatOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	FloatMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/浮点/乘法" ) );
};

#endif // FLOATMULNODE_H_H_HEAD__FILE__
