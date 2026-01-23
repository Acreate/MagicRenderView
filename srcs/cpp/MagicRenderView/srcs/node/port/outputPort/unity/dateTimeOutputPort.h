#ifndef DATETIMEOUTPUTPORT_H_H_HEAD__FILE__
#define DATETIMEOUTPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeOutputPort.h"

class DateTimeOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	DateTimeOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // DATETIMEOUTPUTPORT_H_H_HEAD__FILE__
