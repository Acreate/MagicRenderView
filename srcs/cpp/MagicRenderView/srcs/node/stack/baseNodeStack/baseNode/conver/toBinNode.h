#ifndef TOBINNODE_H_H_HEAD__FILE__
#define TOBINNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class BinOutputPort;
class AnyVarInputPort;
class UIntOutputPort;
class ToBinNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *anyVarInputPortPtr;
	BinOutputPort *binOutputPortPtr;
	uint8_t *outVarPtr;
public:
	ToBinNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/单元/二进制" ) );
};
#endif // TOBINNODE_H_H_HEAD__FILE__
