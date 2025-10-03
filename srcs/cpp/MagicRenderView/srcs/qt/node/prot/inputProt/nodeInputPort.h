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
public:
	NodeInputPort( NodeItem *parent ) : NodePort( parent ) {
	}
	~NodeInputPort( ) override {
		emit inputPorDelete( this );
	}
	bool updateProtLayout( ) override;
	bool linkOutputPort( NodePort *output_port ) override;
	bool disLinkOutputPor( NodePort *remove_output_port ) override;
	bool getPos( QPoint &result_pos ) const override;
};
#endif // NODEINPUTPORT_H_H_HEAD__FILE__
