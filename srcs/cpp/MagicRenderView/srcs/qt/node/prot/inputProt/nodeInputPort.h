#ifndef NODEINPUTPORT_H_H_HEAD__FILE__
#define NODEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../NodePort.h"
class NodeInputPort : public NodePort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodePort );
public:
	NodeInputPort( QObject *parent ) : NodePort( parent ) { }

};
#endif // NODEINPUTPORT_H_H_HEAD__FILE__
