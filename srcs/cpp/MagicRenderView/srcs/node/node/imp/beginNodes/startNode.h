#ifndef STARTNODE_H_H_HEAD__FILE__
#define STARTNODE_H_H_HEAD__FILE__

#include "../../beginNode.h"

class ToBeginOutputPort;
class BeginOutputPort;
class StartNode : public BeginNode {
	Q_OBJECT;
protected:
	BeginOutputPort *beginOutputPort;
	ToBeginOutputPort *toBeginOutputPort;
	bool readUpdate;
	size_t *var;
public:
	StartNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
protected:
	bool readNextBeginNodeData( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "起始/开始" ) );
};

#endif // STARTNODE_H_H_HEAD__FILE__
