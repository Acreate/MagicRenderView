#ifndef APPRUNSTARTTIMENODE_H_H_HEAD__FILE__
#define APPRUNSTARTTIMENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class DateTimeOutputPort;
class AppRunStartTimeNode : public ProcessNode {
	Q_OBJECT;
protected:
	DateTimeOutputPort *outputPortPtr;
	QDateTime *outputVarPtr;
public:
	AppRunStartTimeNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // APPRUNSTARTTIMENODE_H_H_HEAD__FILE__
