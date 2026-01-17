#ifndef BOOLOUTPUTPORT_H_H_HEAD__FILE__
#define BOOLOUTPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeOutputPort.h"

class BoolOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	BoolOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // BOOLOUTPUTPORT_H_H_HEAD__FILE__
