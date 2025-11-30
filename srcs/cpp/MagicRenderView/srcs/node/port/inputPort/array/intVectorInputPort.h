#ifndef INTVECTORINPUTPORT_H_H_HEAD__FILE__
#define INTVECTORINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../arrayTypeInputPort.h"

class IntVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	IntVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // INTVECTORINPUTPORT_H_H_HEAD__FILE__
