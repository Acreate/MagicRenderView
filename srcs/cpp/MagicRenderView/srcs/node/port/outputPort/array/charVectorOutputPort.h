#ifndef CHARVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define CHARVECTOROUTPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeOutputPort.h"

class CharVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	CharVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // CHARVECTOROUTPUTPORT_H_H_HEAD__FILE__
