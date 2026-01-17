#ifndef APPBUILDERTOOLNAMENODE_H_H_HEAD__FILE__
#define APPBUILDERTOOLNAMENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
class AppBuilderToolNameNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *outputPortPtr;
	QString *outputVarPtr;
public:
	AppBuilderToolNameNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "软件/编译工具名称" ) );
};
#endif // APPBUILDERTOOLNAMENODE_H_H_HEAD__FILE__
