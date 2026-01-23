#ifndef BINVECTORINPUTPORT_H_H_HEAD__FILE__
#define BINVECTORINPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeInputPort.h"

class BinVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	BinVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // BINVECTORINPUTPORT_H_H_HEAD__FILE__
