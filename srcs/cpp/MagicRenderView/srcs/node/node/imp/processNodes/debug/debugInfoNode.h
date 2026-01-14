#ifndef DEBUGINFONODE_H_H_HEAD__FILE__
#define DEBUGINFONODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class AnyVarInputPort;
class DebugInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *inputBugPort;
public:
	DebugInfoNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "调试/输出" ) );
};
#endif // DEBUGINFONODE_H_H_HEAD__FILE__
