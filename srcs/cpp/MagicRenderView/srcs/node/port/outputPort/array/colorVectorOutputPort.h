#ifndef COLORVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define COLORVECTOROUTPUTPORT_H_H_HEAD__FILE__

#include "../arrayTypeOutputPort.h"

class ColorVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	ColorVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // COLORVECTOROUTPUTPORT_H_H_HEAD__FILE__
