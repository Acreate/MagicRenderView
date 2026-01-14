#ifndef TOUINTNODE_H_H_HEAD__FILE__
#define TOUINTNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class AnyVarInputPort;
class UIntOutputPort;
class ToUIntNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *anyVarInputPortPtr;
	UIntOutputPort *uIntOutputPortPtr;
	uint64_t *outVarPtr;
public:
	ToUIntNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/无符号整数" ) );
};
#endif // TOUINTNODE_H_H_HEAD__FILE__
