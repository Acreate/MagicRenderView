#ifndef FLOATOUTPUTPORT_H_H_HEAD__FILE__
#define FLOATOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../unityTypeOutputPort.h"

class FloatOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	FloatOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // FLOATOUTPUTPORT_H_H_HEAD__FILE__
