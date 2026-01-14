#ifndef COLORVECTORINPUTPORT_H_H_HEAD__FILE__
#define COLORVECTORINPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeInputPort.h"

class ColorVectorInputPort : public ArrayTypeInputPort {
	Q_OBJECT;
public:
	ColorVectorInputPort( const QString &name )
		: ArrayTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // COLORVECTORINPUTPORT_H_H_HEAD__FILE__
