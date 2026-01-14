#ifndef TIMEOUTPUTPORT_H_H_HEAD__FILE__
#define TIMEOUTPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeOutputPort.h"

class TimeOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	TimeOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // TIMEOUTPUTPORT_H_H_HEAD__FILE__
