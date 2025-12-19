#ifndef INTOUTPUTPORT_H_H_HEAD__FILE__
#define INTOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../outputPort.h"
#include "../unityTypeOutputPort.h"

class IntOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	IntOutputPort( const QString &name );
	bool init( Node *parent ) override;
};

#endif // INTOUTPUTPORT_H_H_HEAD__FILE__
