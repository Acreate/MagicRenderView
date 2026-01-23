#ifndef TOPOINTINPUTPORT_H_H_HEAD__FILE__
#define TOPOINTINPUTPORT_H_H_HEAD__FILE__

#include "../toPointTypeInputPort.h"

class ToPointInputPort : public  ToPointTypeInputPort{
	Q_OBJECT;
public:
	ToPointInputPort( const QString &name )
		: ToPointTypeInputPort( name ) { }
};

#endif // TOPOINTINPUTPORT_H_H_HEAD__FILE__
