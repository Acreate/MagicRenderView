#ifndef NODEOUTPUTPORT_H_H_HEAD__FILE__
#define NODEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../NodePort.h"

class NodeOutputPort : public NodePort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodePort );
	friend class NodeWidgetSerialization;
	friend class NodeItemSerialization;
	friend class MainWidget;
public:
	NodeOutputPort( NodeItem *parent ) : NodePort( parent ) {
	}
	~NodeOutputPort( ) override {
		emit outputPorDelete( this );
	}
	bool updateProtLayout( ) override;

	bool getPos( QPoint &result_pos ) const override;
};

#endif // NODEOUTPUTPORT_H_H_HEAD__FILE__
