#ifndef NODEINPUTPORT_H_H_HEAD__FILE__
#define NODEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../NodePort.h"

#include "../outputProt/nodeOutputPort.h"
class NodeInputPort : public NodePort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodePort );
	friend class NodeWidgetSerialization;
	friend class NodeItemSerialization;
	friend class MainWidget;
protected:
	std_vector< NodeOutputPort * > linkOutputVector;
public:
	NodeInputPort( NodeItem *parent ) : NodePort( parent ) {
	}
	~NodeInputPort( ) override {
		emit inputPorDelete( this );
	}
	bool updateProtLayout( ) override;
	virtual void linkOutputPort( NodeOutputPort *output_port );
	virtual void disLinkOutputPor( NodeOutputPort *remove_output_port );
	virtual const std_vector< NodeOutputPort * > & getLinkOutputVector( ) const { return linkOutputVector; }

	bool getPos( QPoint &result_pos ) const override;
Q_SIGNALS:
	void inputPorDelete( NodeInputPort *remove_input_port );
	void linkOutputPorOver( NodeOutputPort *remove_input_port );
	void disLinkOutputPorOver( NodeOutputPort *remove_input_port );
};
#endif // NODEINPUTPORT_H_H_HEAD__FILE__
