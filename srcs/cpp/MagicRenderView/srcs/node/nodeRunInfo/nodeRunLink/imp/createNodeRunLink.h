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
};

#endif // CREATENODERUNLINK_H_H_HEAD__FILE__
