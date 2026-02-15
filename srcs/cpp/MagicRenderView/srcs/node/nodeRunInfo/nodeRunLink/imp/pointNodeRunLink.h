#ifndef POINTNODERUNLINK_H_H_HEAD__FILE__
#define POINTNODERUNLINK_H_H_HEAD__FILE__
#include "../nodeRunLink.h"
class NodeRunInfo;
class PointNodeRunLink : public NodeRunLink {
	Q_OBJECT;
	friend class NodeRunInfo;
protected:
	PointNodeRunLink( Node *const init_node_ptr )
		: NodeRunLink( init_node_ptr ) { }
	bool builder( ) override;
	bool getNextRunNode( const std::vector< Node * > &over_run_node_vector, Node *&result_next_node_ptr ) override;
};

#endif // POINTNODERUNLINK_H_H_HEAD__FILE__
