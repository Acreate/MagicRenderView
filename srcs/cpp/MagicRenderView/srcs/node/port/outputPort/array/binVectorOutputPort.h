#ifndef BINVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define BINVECTOROUTPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeOutputPort.h"

class BinVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	BinVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // BINVECTOROUTPUTPORT_H_H_HEAD__FILE__
