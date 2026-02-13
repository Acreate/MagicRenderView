#ifndef GOTONODE_H_H_HEAD__FILE__
#define GOTONODE_H_H_HEAD__FILE__

#include <node/node/jumpNode.h>

class AnyVarInputPort;
class PointInputPort;
class ToPointInputPort;
class GotoNode : public JumpNode {
	Q_OBJECT;
protected:
	PointInputPort *pointInputPort;
	ToPointInputPort *toPointInputPort;
public:
	GotoNode( const QString &node_name )
		: JumpNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector, size_t current_frame ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // GOTONODE_H_H_HEAD__FILE__
