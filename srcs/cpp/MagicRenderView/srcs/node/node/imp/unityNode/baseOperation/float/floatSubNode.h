#ifndef FLOATSUBNODE_H_H_HEAD__FILE__
#define FLOATSUBNODE_H_H_HEAD__FILE__

#include <node/node/unityNode.h>

class FloatOutputPort;
class FloatInputPort;
class FloatSubNode : public UnityNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatInputPort *firstInputPort;
	FloatInputPort *secondInputPort;
	FloatOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	FloatSubNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/浮点/减法" ) );
};

#endif // FLOATSUBNODE_H_H_HEAD__FILE__
