#ifndef BEGININPUTPORT_H_H_HEAD__FILE__
#define BEGININPUTPORT_H_H_HEAD__FILE__

#include "../beginTypeInputPort.h"

class BeginInputPort : public BeginTypeInputPort {
	Q_OBJECT;
public:
	BeginInputPort( const QString &name )
		: BeginTypeInputPort( name ) { }
};
#endif // BEGININPUTPORT_H_H_HEAD__FILE__
