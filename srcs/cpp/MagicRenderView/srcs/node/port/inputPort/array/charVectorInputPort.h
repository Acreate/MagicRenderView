#ifndef CHARVECTORINPUTPORT_H_H_HEAD__FILE__
#define CHARVECTORINPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeInputPort.h"

class CharVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	CharVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // CHARVECTORINPUTPORT_H_H_HEAD__FILE__
