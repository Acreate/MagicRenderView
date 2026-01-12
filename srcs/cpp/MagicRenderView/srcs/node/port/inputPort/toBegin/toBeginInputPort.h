#ifndef TOBEGININPUTPORT_H_H_HEAD__FILE__
#define TOBEGININPUTPORT_H_H_HEAD__FILE__

#include "../toBeginTypeInputPort.h"

class ToBeginInputPort : public ToBeginTypeInputPort {
	Q_OBJECT;
public:
	ToBeginInputPort( const QString &name )
		: ToBeginTypeInputPort( name ) { }
};
#endif // TOBEGININPUTPORT_H_H_HEAD__FILE__
