#ifndef CREATENODERUNLINK_H_H_HEAD__FILE__
#define CREATENODERUNLINK_H_H_HEAD__FILE__
#include "../nodeRunLink.h"

class NodeRunInfo;
class CreateNodeRunLink : public NodeRunLink {
	Q_OBJECT;
	friend class NodeRunInfo;
protected:
	CreateNodeRunLink( Node *const init_node_ptr );
	bool builder( ) override;
	bool linkHasNode( const Node *const check_node_ptr ) const override;
	bool getNextRunNode( Node *&result_next_node_ptr ) override;
	bool getCurrentRunNode( Node *&result_current_node_ptr ) override;
};

#endif // CREATENODERUNLINK_H_H_HEAD__FILE__
