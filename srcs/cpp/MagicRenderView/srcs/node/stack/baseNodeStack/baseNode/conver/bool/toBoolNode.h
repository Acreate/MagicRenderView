#ifndef TOBOOLNODE_H_H_HEAD__FILE__
#define TOBOOLNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class BoolOutputPort;
class AnyVarInputPort;
class ToBoolNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *anyVarInputPortPtr;
	BoolOutputPort *binOutputPortPtr;
	bool *outVarPtr;
public:
	ToBoolNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/单元/布尔" ) );
};
#endif // TOBOOLNODE_H_H_HEAD__FILE__
