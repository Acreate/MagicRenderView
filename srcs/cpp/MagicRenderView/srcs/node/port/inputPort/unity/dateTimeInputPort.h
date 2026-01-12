#ifndef DATETIMEINPUTPORT_H_H_HEAD__FILE__
#define DATETIMEINPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeInputPort.h"

class DateTimeInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	DateTimeInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // DATETIMEINPUTPORT_H_H_HEAD__FILE__
