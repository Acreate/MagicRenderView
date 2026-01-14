#ifndef FLOATARRAYSELFMULNODE_H_H_HEAD__FILE__
#define FLOATARRAYSELFMULNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class FloatOutputPort;
class FloatVectorInputPort;

class FloatArraySelfMulNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatVectorInputPort *firstInputPort;
	FloatOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	FloatArraySelfMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/自运算/浮点/乘法" ) );
};

#endif // FLOATARRAYSELFMULNODE_H_H_HEAD__FILE__
