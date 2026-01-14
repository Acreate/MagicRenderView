#ifndef TOPOINTOUTPUTPORT_H_H_HEAD__FILE__
#define TOPOINTOUTPUTPORT_H_H_HEAD__FILE__


#include "../toPointTypeOutputPort.h"

class ToPointOutputPort : public ToPointTypeOutputPort {
	Q_OBJECT;
public:
	ToPointOutputPort( const QString &name )
		: ToPointTypeOutputPort( name ) { }
};

#endif // TOPOINTOUTPUTPORT_H_H_HEAD__FILE__
