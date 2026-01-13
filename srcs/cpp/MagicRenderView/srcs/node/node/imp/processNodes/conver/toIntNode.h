#ifndef TOINTNODE_H_H_HEAD__FILE__
#define TOINTNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class AnyVarInputPort;
class IntOutputPort;
class ToIntNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *anyVarInputPortPtr;
	IntOutputPort *intOutputPortPtr;
	int64_t *outVarPtr;
public:
	ToIntNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "单元/转换/整数" ) );
};
#endif // TOINTNODE_H_H_HEAD__FILE__
