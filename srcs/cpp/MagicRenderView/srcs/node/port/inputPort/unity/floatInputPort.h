#ifndef FLOATINPUTPORT_H_H_HEAD__FILE__
#define FLOATINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../unityTypeInputPort.h"

class FloatInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	FloatInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // FLOATINPUTPORT_H_H_HEAD__FILE__
