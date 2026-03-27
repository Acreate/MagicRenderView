#ifndef LIFTNODE_H_H_HEAD__FILE__
#define LIFTNODE_H_H_HEAD__FILE__
#include "../../../../node/callNode.h"

class AnyVarInputPort;
class PointInputPort;
class ToPointInputPort;
class LiftNode : public CallNode {
	Q_OBJECT;
protected:
	PointInputPort *pointInputPort;
	ToPointInputPort *toPointInputPort;
public:
	LiftNode( const QString &node_name )
		: CallNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillInputPortCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame, std::vector< Node * > &result_need_run_ref_node_vector ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
	bool fillOutputPortCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame, std::vector< Node * > &result_next_run_advise_node_vector ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // LIFTNODE_H_H_HEAD__FILE__
