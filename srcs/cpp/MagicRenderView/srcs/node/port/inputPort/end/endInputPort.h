#ifndef ENDINPUTPORT_H_H_HEAD__FILE__
#define ENDINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../endTypeInputPort.h"

class EndInputPort : public EndTypeInputPort {
	Q_OBJECT;
public:
	EndInputPort( const QString &name )
		: EndTypeInputPort( name ) { }
};

#endif // ENDINPUTPORT_H_H_HEAD__FILE__
