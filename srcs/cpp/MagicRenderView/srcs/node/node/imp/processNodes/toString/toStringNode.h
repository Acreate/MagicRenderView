#ifndef TOSTRINGNODE_H_H_HEAD__FILE__
#define TOSTRINGNODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class ToStringNode : public ProcessNode {
	Q_OBJECT;
public:
	ToStringNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/自识别/字符串" ) );
};
#endif // TOSTRINGNODE_H_H_HEAD__FILE__
