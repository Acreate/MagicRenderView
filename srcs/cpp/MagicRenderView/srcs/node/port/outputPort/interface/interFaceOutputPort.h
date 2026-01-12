#ifndef INTERFACEOUTPUTPORT_H_H_HEAD__FILE__
#define INTERFACEOUTPUTPORT_H_H_HEAD__FILE__

#include "../InterFaceTypeOutputPort.h"

class InterFaceOutputPort : public InterFaceTypeOutputPort {
	Q_OBJECT;
public:
	InterFaceOutputPort( const QString &name )
		: InterFaceTypeOutputPort( name ) { }
};

#endif // INTERFACEOUTPUTPORT_H_H_HEAD__FILE__
