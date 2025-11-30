#ifndef FLOATVECTORINPUTPORT_H_H_HEAD__FILE__
#define FLOATVECTORINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../arrayTypeInputPort.h"

class FloatVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	FloatVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // FLOATVECTORINPUTPORT_H_H_HEAD__FILE__
