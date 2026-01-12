#ifndef DATETIMEVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define DATETIMEVECTOROUTPUTPORT_H_H_HEAD__FILE__


#include "../arrayTypeOutputPort.h"

class DateTimeVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	DateTimeVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // DATETIMEVECTOROUTPUTPORT_H_H_HEAD__FILE__
