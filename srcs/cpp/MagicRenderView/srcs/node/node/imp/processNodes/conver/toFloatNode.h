#ifndef TOFLOATNODE_H_H_HEAD__FILE__
#define TOFLOATNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class AnyVarInputPort;
class FloatOutputPort;
class ToFloatNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *anyVarInputPortPtr;
	FloatOutputPort *floatOutputPortPtr;
	double* outVarPtr;
public:
	ToFloatNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/单元/浮点" ) );
};
#endif // TOFLOATNODE_H_H_HEAD__FILE__
