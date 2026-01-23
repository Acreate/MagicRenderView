#ifndef TIMEINPUTPORT_H_H_HEAD__FILE__
#define TIMEINPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeInputPort.h"

class TimeInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	TimeInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // TIMEINPUTPORT_H_H_HEAD__FILE__
