#ifndef NODEPORTLINKINFO_H_H_HEAD__FILE__
#define NODEPORTLINKINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class QMenu;
class QAction;
class NodeOutputPort;
class NodeInputPort;
class NodePortLinkInfo : public QObject {
	Q_OBJECT;
protected:
	friend class NodeDirector;
	NodeInputPort *inputPort;
	std_vector_pairt< NodeOutputPort *, QAction * > outputPorts;
	QMenu *removeLinkMenu;
public:
	~NodePortLinkInfo( ) override;
	NodePortLinkInfo( NodeInputPort *input_port );
	virtual bool link( NodeOutputPort *link_output_port );
	virtual bool unLink( NodeOutputPort *link_output_port );
	virtual std_vector< NodeOutputPort * > getOutputPorts( ) const;
	virtual QMenu * getRemoveLinkMenu( ) const { return removeLinkMenu; }
Q_SIGNALS:
	void linkNodePort( NodePortLinkInfo *sender_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
	void unlinkNodePort( NodePortLinkInfo *sender_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port );
	void releaseThis( NodePortLinkInfo *release_ptr );
};
#endif // NODEPORTLINKINFO_H_H_HEAD__FILE__
