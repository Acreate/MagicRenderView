#ifndef FILEINFONODE_H_H_HEAD__FILE__
#define FILEINFONODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class AnyVarInputPort;
class FileInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	AnyVarInputPort *inputBugPort;
public:
	FileInfoNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "路径/路径信息" ) );
};
#endif // FILEINFONODE_H_H_HEAD__FILE__
