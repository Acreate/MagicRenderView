#ifndef RUNARGINFONODE_H_H_HEAD__FILE__
#define RUNARGINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class StringOutputPort;
class RunArgInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *outputPortPtr;
	QString *outputVarPtr;
public:
	RunArgInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // RUNARGINFONODE_H_H_HEAD__FILE__
