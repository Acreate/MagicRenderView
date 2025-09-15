#ifndef STRINGINPUTPORT_H_H_HEAD__FILE__
#define STRINGINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../nodeInputPort.h"

class StringInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
public:
	StringInputPort( NodeItem *parent )
		: NodeInputPort( parent ) {
		title = getMetaObjectName( );
	}
	void linkOutputPort( NodeOutputPort *output_port ) override{}
};

#endif // STRINGINPUTPORT_H_H_HEAD__FILE__
