#ifndef BOOLVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define BOOLVECTOROUTPUTPORT_H_H_HEAD__FILE__


#include "../arrayTypeOutputPort.h"

class BoolVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	BoolVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // BOOLVECTOROUTPUTPORT_H_H_HEAD__FILE__
