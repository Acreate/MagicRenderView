#ifndef POINTINPUTPORT_H_H_HEAD__FILE__
#define POINTINPUTPORT_H_H_HEAD__FILE__

#include "../pointTypeInputPort.h"

class PointInputPort : public PointTypeInputPort {
	Q_OBJECT;
public:
	PointInputPort( const QString &name )
		: PointTypeInputPort( name ) { }
};

#endif // POINTINPUTPORT_H_H_HEAD__FILE__
