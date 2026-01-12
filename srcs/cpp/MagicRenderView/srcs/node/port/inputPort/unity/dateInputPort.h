#ifndef DATEINPUTPORT_H_H_HEAD__FILE__
#define DATEINPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeInputPort.h"

class DateInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	DateInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // DATEINPUTPORT_H_H_HEAD__FILE__
