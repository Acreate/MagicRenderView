#ifndef BEGINOUTPUTPORT_H_H_HEAD__FILE__
#define BEGINOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../beginTypeOutputPort.h"

class BeginOutputPort : public BeginTypeOutputPort {
	Q_OBJECT;
public:
	BeginOutputPort( const QString &name )
		: BeginTypeOutputPort( name ) { }
};

#endif // BEGINOUTPUTPORT_H_H_HEAD__FILE__
