#ifndef NODEOUTPUTPORT_H_H_HEAD__FILE__
#define NODEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../NodePort.h"

class NodeOutputPort : public NodePort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodePort );
public:
	NodeOutputPort( QObject *parent ) : NodePort( parent ) {
	}
};

#endif // NODEOUTPUTPORT_H_H_HEAD__FILE__
