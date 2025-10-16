#ifndef NODEPORTLINKINFO_H_H_HEAD__FILE__
#define NODEPORTLINKINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class NodeItem;
class NodePort;
class QMenu;
class QAction;
class NodeOutputPort;
class NodeInputPort;
class NodePortLinkInfo : public QObject {
	Q_OBJECT;
protected:
	friend class NodeDirector;
	friend class NodeItemBuilderLink;
	NodeInputPort *inputPort;
	std_vector_pairt< NodeItem *, std_vector_pairt< NodeOutputPort *, QAction * > > outputPorts;
	QMenu *removeLinkMenu;
protected:
	NodePortLinkInfo( NodeInputPort *input_port );
public:
	~NodePortLinkInfo( ) override;
	virtual bool link( NodeOutputPort *link_output_port );
	virtual bool unLink( NodeOutputPort *link_output_port );
	virtual bool releaseNodeItemPtr( NodeItem *link_node_item );
	virtual bool getLink( NodeItem *link_node_item, std_vector< NodeOutputPort * > result_link );
	virtual bool getLink( std_vector< NodeOutputPort * > result_link );
	virtual bool getLinkNodeItem( std_vector< NodeItem * > result_link_node_items );
	virtual QMenu * getRemoveLinkMenu( ) const { return removeLinkMenu; }
	virtual bool hasNodeItem( const NodeItem *check_nodeitem_ptr ) const;
Q_SIGNALS:
	void linkNodePort( NodePortLinkInfo *sender_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
	void unlinkNodePort( NodePortLinkInfo *sender_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
	void releaseThis( NodePortLinkInfo *release_ptr );
};
#endif // NODEPORTLINKINFO_H_H_HEAD__FILE__
