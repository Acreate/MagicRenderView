#ifndef TIMEVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define TIMEVECTOROUTPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeOutputPort.h"

class TimeVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	TimeVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // TIMEVECTOROUTPUTPORT_H_H_HEAD__FILE__
