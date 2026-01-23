#ifndef DATEOUTPUTPORT_H_H_HEAD__FILE__
#define DATEOUTPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeOutputPort.h"

class DateOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	DateOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // DATEOUTPUTPORT_H_H_HEAD__FILE__
