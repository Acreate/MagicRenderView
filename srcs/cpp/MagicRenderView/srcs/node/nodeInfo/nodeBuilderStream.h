#ifndef NODEBUILDERSTREAM_H_H_HEAD__FILE__
#define NODEBUILDERSTREAM_H_H_HEAD__FILE__
#pragma once
#include <vector>

#include "../node/node.h"
class NodeRefLinkInfo;
class NodeBuilderStream {
	friend class NodeBuilderTools;
protected:
	NodeRefLinkInfo *sourceNode;
	std::vector< NodeRefLinkInfo * > builderNodeRefLinkInfoStream;
	std::vector< NodeRefLinkInfo * > beginVector;
protected:
	virtual void foreachOutNodeRefVector( NodeRefLinkInfo *source_node_ref_link_info, std::vector< NodeRefLinkInfo * > &result_out_node_ref );
public:
	virtual ~NodeBuilderStream( ) { }
	NodeBuilderStream( NodeRefLinkInfo *source_node )
		: sourceNode( source_node ) { }
	virtual bool builderNodeRefStream( QString &error_msg );
	virtual NodeRefLinkInfo * getSourceNode( ) const { return sourceNode; }
	virtual const std::vector< NodeRefLinkInfo * > & getBuilderNodeRefLinkInfoStream( ) const { return builderNodeRefLinkInfoStream; }
	virtual const std::vector< NodeRefLinkInfo * > & getBeginVector( ) const { return beginVector; }
};

#endif // NODEBUILDERSTREAM_H_H_HEAD__FILE__
