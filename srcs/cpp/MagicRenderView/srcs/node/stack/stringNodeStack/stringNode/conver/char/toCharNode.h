#ifndef TOCHARNODE_H_H_HEAD__FILE__
#define TOCHARNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class CharOutputPort;
class AnyVarInputPort;
class IntOutputPort;
class ToCharNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *anyVarInputPortPtr;
	CharOutputPort *charOutputPortPtr;
	QChar *outVarPtr;
public:
	ToCharNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/单元/字符" ) );
};
#endif // TOCHARNODE_H_H_HEAD__FILE__
