#ifndef CALLNODERUNLINK_H_H_HEAD__FILE__
#define CALLNODERUNLINK_H_H_HEAD__FILE__
#include "../nodeRunLink.h"

class CallNodeRunLink : public NodeRunLink {
	Q_OBJECT;
	friend class NodeRunInfo;
protected:
	CallNodeRunLink( Node *const init_node_ptr )
		: NodeRunLink( init_node_ptr ) { }
};

#endif // CALLNODERUNLINK_H_H_HEAD__FILE__
