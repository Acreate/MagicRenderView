#ifndef DATEVECTORINPUTPORT_H_H_HEAD__FILE__
#define DATEVECTORINPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeInputPort.h"

class DateVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	DateVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // DATEVECTORINPUTPORT_H_H_HEAD__FILE__
