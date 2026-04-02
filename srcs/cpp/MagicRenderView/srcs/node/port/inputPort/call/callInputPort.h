#ifndef CALLINPUTPORT_H_H_HEAD__FILE__
#define CALLINPUTPORT_H_H_HEAD__FILE__
#include "../callTypeInputPort.h"

class CallInputPort : public CallTypeInputPort {
	Q_OBJECT;
public:
	CallInputPort( const QString &name )
		: CallTypeInputPort( name ) { }
};

#endif // CALLINPUTPORT_H_H_HEAD__FILE__
