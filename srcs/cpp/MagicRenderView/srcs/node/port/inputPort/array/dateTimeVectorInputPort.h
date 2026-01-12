#ifndef DATETIMEVECTORINPUTPORT_H_H_HEAD__FILE__
#define DATETIMEVECTORINPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeInputPort.h"

class DateTimeVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	DateTimeVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // DATETIMEVECTORINPUTPORT_H_H_HEAD__FILE__
