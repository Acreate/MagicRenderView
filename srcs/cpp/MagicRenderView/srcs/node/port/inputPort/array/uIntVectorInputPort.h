#ifndef UINTVECTORINPUTPORT_H_H_HEAD__FILE__
#define UINTVECTORINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../arrayTypeInputPort.h"

class UIntVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	UIntVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // UINTVECTORINPUTPORT_H_H_HEAD__FILE__
