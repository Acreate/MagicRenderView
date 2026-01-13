#ifndef IFNODE_H_H_HEAD__FILE__
#define IFNODE_H_H_HEAD__FILE__

#include "../../logicNode.h"

class PointInputPort;
class AnyVarOutputPort;
class AnyVarInputPort;
class IfNode : public LogicNode {
	Q_OBJECT;
protected:
	PointInputPort * pointInputPort;
	AnyVarInputPort *ifResultPort;
	AnyVarOutputPort *trueOutputPort;
	AnyVarOutputPort *falseOutputPort;
	std::vector< Node * > adviseNextVector;
public:
	IfNode( const QString &node_name )
		: LogicNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) override;
	Def_Extend_NodeTypeName( Node::tr( "逻辑/分支" ) );
};

#endif // IFNODE_H_H_HEAD__FILE__
