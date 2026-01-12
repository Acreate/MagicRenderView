#ifndef SYSTEMPATHINFO_H_H_HEAD__FILE__
#define SYSTEMPATHINFO_H_H_HEAD__FILE__

#include "../../../processNode.h"

class AnyVarInputPort;
class SystemPathInfo : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *inputBugPort;
public:
	SystemPathInfo( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/系统路径" ) );
};
#endif // SYSTEMPATHINFO_H_H_HEAD__FILE__
