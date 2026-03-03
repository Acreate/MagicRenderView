#ifndef FUNCTIONNODERUNLINK_H_H_HEAD__FILE__
#define FUNCTIONNODERUNLINK_H_H_HEAD__FILE__

#include "../nodeRunLink.h"

class FunctionNodeRunLink : public NodeRunLink {
	Q_OBJECT;
	friend class NodeRunInfo;
protected:
	FunctionNodeRunLink( Node *const init_node_ptr )
		: NodeRunLink( init_node_ptr ) { }
	bool builder( ) override;
};
#endif // FUNCTIONNODERUNLINK_H_H_HEAD__FILE__
