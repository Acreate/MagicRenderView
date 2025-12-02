#ifndef NODEPORTLINKINFO_H_H_HEAD__FILE__
#define NODEPORTLINKINFO_H_H_HEAD__FILE__
#pragma once
#include <vector>

class QMenu;
class NodeRefLinkInfo;
class OutputPort;
class InputPort;
class NodePortLinkInfo {
	friend class NodeDirector;
	friend class NodeRefLinkInfo;
	friend class NodeRefLinkInfoTools;
protected:
	NodeRefLinkInfo *nodeRefLinkInfo;
	std::vector< std::pair< InputPort *, std::vector< OutputPort * > > > inputPortVector;
public:
	NodePortLinkInfo( NodeRefLinkInfo *node_ref_link_info );
	virtual bool appEndLinkTarget( OutputPort *out_put_port, InputPort *in_put_port );
	virtual bool removeLinkTarget( OutputPort *out_put_port, InputPort *in_put_port );
	virtual size_t removeNodeRefLinkInfoLinkTarget( NodeRefLinkInfo *remove_all_port_node_ref_link_info );
	virtual bool hasNodeRef( const NodeRefLinkInfo *check_node_ref ) const;
	virtual bool hasPortRef( const OutputPort *out_put_port, const InputPort *in_put_port ) const;
	virtual const std::vector< std::pair< InputPort *, std::vector< OutputPort * > > > & getInputPortVector( ) const { return inputPortVector; }
	virtual ~NodePortLinkInfo( ) { }
};

#endif // NODEPORTLINKINFO_H_H_HEAD__FILE__
