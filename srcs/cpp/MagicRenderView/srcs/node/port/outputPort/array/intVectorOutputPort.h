#ifndef INTVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define INTVECTOROUTPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeOutputPort.h"
#include "../outputPort.h"

class IntVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	IntVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // INTVECTOROUTPUTPORT_H_H_HEAD__FILE__
