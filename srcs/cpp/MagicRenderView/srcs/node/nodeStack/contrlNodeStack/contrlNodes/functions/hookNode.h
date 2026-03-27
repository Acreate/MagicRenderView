#ifndef HOOKNODE_H_H_HEAD__FILE__
#define HOOKNODE_H_H_HEAD__FILE__

#include <node/node/functionNode.h>

class ToPointOutputPort;
class PointOutputPort;
class HookNode : public FunctionNode {
	Q_OBJECT;
protected:
	PointOutputPort *nextNode;
	ToPointOutputPort *toPointOutputPortPtr;
public:
	HookNode( const QString &node_name )
		: FunctionNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
	bool fillOutputPortCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame, std::vector< Node * > &result_next_run_advise_node_vector ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // HOOKNODE_H_H_HEAD__FILE__
