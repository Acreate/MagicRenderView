#ifndef IFNODE_H_H_HEAD__FILE__
#define IFNODE_H_H_HEAD__FILE__

#include <node/node/logicNode.h>

class PointInputPort;
class AnyVarOutputPort;
class AnyVarInputPort;
class IfNode : public LogicNode {
	Q_OBJECT;
protected:
	PointInputPort *pointInputPort;
	AnyVarInputPort *ifResultPort;
	AnyVarInputPort *channelInputPort;
	AnyVarOutputPort *channelOutputPort;
	std::vector< Node * > adviseNextVector;
public:
	IfNode( const QString &node_name )
		: LogicNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector, size_t current_frame ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
	Def_Extern_NodeTypeName_Function( );
};

#endif // IFNODE_H_H_HEAD__FILE__
