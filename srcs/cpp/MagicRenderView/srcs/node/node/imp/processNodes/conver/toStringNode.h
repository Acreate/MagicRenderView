#ifndef TOSTRINGNODE_H_H_HEAD__FILE__
#define TOSTRINGNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class AnyVarInputPort;
class StringOutputPort;
class ToStringNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *anyVarInputPortPtr;
	StringOutputPort *stringOutputPortPtr;
	QString *outVarPtr;
public:
	ToStringNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "单元/转换/字符串" ) );
};
#endif // TOSTRINGNODE_H_H_HEAD__FILE__
