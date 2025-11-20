#ifndef NODEINPUTPORT_H_H_HEAD__FILE__
#define NODEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../NodePort.h"

class NodeInputPort : public NodePort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodePort );
	friend class NodeWidgetSerialization;
	friend class NodeItemSerialization;
	friend class NodeItem;
protected:
public:
	NodeInputPort( NodeItem *parent ) : NodePort( parent ) {
	}
	~NodeInputPort( ) override {
		emit inputPorDelete( this );
	}
	bool isOutputPort( ) const override { return false; }
	bool updateProtLayout( ) override;
	bool getPos( QPoint &result_pos ) const override;
protected:
	virtual bool setInputPortVar( const type_info &var_type_info, const void *set_new_var_ptr );
};
#endif // NODEINPUTPORT_H_H_HEAD__FILE__
