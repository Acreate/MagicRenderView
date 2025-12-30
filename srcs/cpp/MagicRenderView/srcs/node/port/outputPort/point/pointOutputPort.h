#ifndef POINTOUTPUTPORT_H_H_HEAD__FILE__
#define POINTOUTPUTPORT_H_H_HEAD__FILE__
#pragma once


#include "../pointTypeOutputPort.h"

class PointOutputPort : public PointTypeOutputPort{
	Q_OBJECT;
public:
	PointOutputPort( const QString &name )
		: PointTypeOutputPort( name ) { }
};
#endif // POINTOUTPUTPORT_H_H_HEAD__FILE__
