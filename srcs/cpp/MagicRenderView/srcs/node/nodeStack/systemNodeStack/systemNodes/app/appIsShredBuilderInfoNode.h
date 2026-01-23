#ifndef APPISSHREDBUILDERINFONODE_H_H_HEAD__FILE__
#define APPISSHREDBUILDERINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class BoolOutputPort;

class AppIsShredBuilderInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	BoolOutputPort *outputPortPtr;
	bool *outputVarPtr;
public:
	AppIsShredBuilderInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // APPISSHREDBUILDERINFONODE_H_H_HEAD__FILE__
