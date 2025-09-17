#ifndef NODEOUTPUTPORT_H_H_HEAD__FILE__
#define NODEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../NodePort.h"

class NodeOutputPort : public NodePort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodePort );
public:
	NodeOutputPort( NodeItem *parent ) : NodePort( parent ) {
	}
	~NodeOutputPort( ) override {
		emit outputPorDelete( this );
	}
	bool updateProtLayout( ) override;

	bool getPos( QPoint &result_pos ) const override;
Q_SIGNALS:
	void outputPorDelete( NodeOutputPort *remove_output_port );
};

#endif // NODEOUTPUTPORT_H_H_HEAD__FILE__
