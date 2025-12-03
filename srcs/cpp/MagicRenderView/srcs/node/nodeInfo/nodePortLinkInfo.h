#ifndef NODEPORTLINKINFO_H_H_HEAD__FILE__
#define NODEPORTLINKINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <vector>

#include <tools/aliasType.h>

class InputportLinkOutputPortInfo;
class SrackInfo;
class Node;
class QMenu;
class NodeRefLinkInfo;
class OutputPort;
class InputPort;
class NodePortLinkInfo : public QObject {
	Q_OBJECT;
	friend class NodeDirector;
	friend class NodeRefLinkInfo;
	friend class NodeRefLinkInfoTools;
protected:
	NodeRefLinkInfo *nodeRefLinkInfo;
	std::vector< InputportLinkOutputPortInfo * > inputPortVector;
public:
	NodePortLinkInfo( NodeRefLinkInfo *node_ref_link_info );
	virtual bool appEndLinkInputTarget( InputPort *in_put_port, OutputPort *out_put_port );
	virtual bool removeLinkInputTarget( InputPort *in_put_port, OutputPort *out_put_port );
	virtual size_t removeNodeRefLinkInfoLinkTarget( NodeRefLinkInfo *remove_all_port_node_ref_link_info );
	virtual bool hasNodeRef( const NodeRefLinkInfo *check_node_ref ) const;
	virtual bool hasNodeRef( const Node *check_node ) const;
	virtual bool hasPortRef( const InputPort *in_put_port, const OutputPort *out_put_port ) const;
	virtual const std::vector< InputportLinkOutputPortInfo * > & getInputPortVector( ) const { return inputPortVector; }
	~NodePortLinkInfo( ) override;
	virtual bool toUint8VectorData( std::vector< uint8_t > &result_vector_data );
	virtual bool toLinkMap( std::vector< InputportLinkOutputPortInfoMap > &result_map_vector, size_t &user_data_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const;
Q_SIGNALS:
	void release_link_signal( InputPort *input_port, OutputPort *release_output_port, const SrackInfo &srack_info );
	void create_link_signal( InputPort *input_port, OutputPort *release_output_port, const SrackInfo &srack_info );
};

#endif // NODEPORTLINKINFO_H_H_HEAD__FILE__
