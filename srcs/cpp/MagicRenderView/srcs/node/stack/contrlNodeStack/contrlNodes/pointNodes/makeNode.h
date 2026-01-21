#ifndef MAKENODE_H_H_HEAD__FILE__
#define MAKENODE_H_H_HEAD__FILE__

#include <node/node/pointNode.h>

class ToPointOutputPort;
class PointOutputPort;
class MakeNode : public PointNode {
	Q_OBJECT;
protected:
	PointOutputPort *nextNode;
	ToPointOutputPort *toPointOutputPortPtr;
public:
	MakeNode( const QString &node_name )
		: PointNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
	bool fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // MAKENODE_H_H_HEAD__FILE__
