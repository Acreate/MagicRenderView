#ifndef UINTVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define UINTVECTOROUTPUTPORT_H_H_HEAD__FILE__


#include "../arrayTypeOutputPort.h"

class UIntVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	UIntVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // UINTVECTOROUTPUTPORT_H_H_HEAD__FILE__
