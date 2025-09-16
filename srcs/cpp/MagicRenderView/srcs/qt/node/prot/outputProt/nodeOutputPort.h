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
	bool updateProtLayout( ) override;
};

#endif // NODEOUTPUTPORT_H_H_HEAD__FILE__
