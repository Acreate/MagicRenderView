#ifndef TIMEVECTORINPUTPORT_H_H_HEAD__FILE__
#define TIMEVECTORINPUTPORT_H_H_HEAD__FILE__


#include "../arrayTypeInputPort.h"

class TimeVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	TimeVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // TIMEVECTORINPUTPORT_H_H_HEAD__FILE__
