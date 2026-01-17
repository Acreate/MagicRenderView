#ifndef APPISSHREDBUILDERINFONODE_H_H_HEAD__FILE__
#define APPISSHREDBUILDERINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class IntOutputPort;
class AppIsShredBuilderInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	IntOutputPort *outputPortPtr;
	int64_t *outputVarPtr;
public:
	AppIsShredBuilderInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "软件/是否使用qt共享库" ) );
};
#endif // APPISSHREDBUILDERINFONODE_H_H_HEAD__FILE__
