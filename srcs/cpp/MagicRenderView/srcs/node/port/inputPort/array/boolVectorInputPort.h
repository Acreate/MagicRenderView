#ifndef BOOLVECTORINPUTPORT_H_H_HEAD__FILE__
#define BOOLVECTORINPUTPORT_H_H_HEAD__FILE__


#include "../arrayTypeInputPort.h"

class BoolVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	BoolVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // BOOLVECTORINPUTPORT_H_H_HEAD__FILE__
