#ifndef BEGINOUTPUTPORT__H_H_HEAD__FILE__
#define BEGINOUTPUTPORT__H_H_HEAD__FILE__
#pragma once
#include "../BeginTypeOutputPort.h"

class BeginOutputPort : public BeginTypeOutputPort {
	Q_OBJECT;
public:
	BeginOutputPort( const QString &name )
		: BeginTypeOutputPort( name ) { }
};
#endif // BEGINOUTPUTPORT__H_H_HEAD__FILE__
