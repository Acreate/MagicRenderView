#ifndef DATEVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define DATEVECTOROUTPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeOutputPort.h"

class DateVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	DateVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // DATEVECTOROUTPUTPORT_H_H_HEAD__FILE__
