#ifndef FLOATVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define FLOATVECTOROUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../arrayTypeOutputPort.h"
#include "../outputPort.h"

class FloatVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	FloatVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // FLOATVECTOROUTPUTPORT_H_H_HEAD__FILE__
