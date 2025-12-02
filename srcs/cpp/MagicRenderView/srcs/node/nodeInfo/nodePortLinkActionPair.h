#ifndef NODEPORTLINKACTIONPAIR_H_H_HEAD__FILE__
#define NODEPORTLINKACTIONPAIR_H_H_HEAD__FILE__
#pragma once

class QAction;
class OutputPort;
class InputPort;
class NodePortLinkActionPair {
	friend class NodeDirector;
protected:
	InputPort *inputPort;
	QAction *inputLinkAction;
	OutputPort *outputPort;
	QAction *outputLinkAction;
public:
	NodePortLinkActionPair( InputPort *input_port, QAction *input_link_action, OutputPort *output_port, QAction *output_link_action );
	virtual ~NodePortLinkActionPair( );
};

#endif // NODEPORTLINKACTIONPAIR_H_H_HEAD__FILE__
