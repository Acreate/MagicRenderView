#ifndef CALLOUTPUTPORT_H_H_HEAD__FILE__
#define CALLOUTPUTPORT_H_H_HEAD__FILE__
#include "../callTypeOutputPort.h"

class CallOutputPort : public CallTypeOutputPort {
	Q_OBJECT;
public:
	CallOutputPort( const QString &name )
		: CallTypeOutputPort( name ) { }
};

#endif // CALLOUTPUTPORT_H_H_HEAD__FILE__
