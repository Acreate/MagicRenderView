#ifndef INTERFACEINPUTPORT_H_H_HEAD__FILE__
#define INTERFACEINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../interFaceTypeInputPort.h"

class InterFaceInputPort : public  InterFaceTypeInputPort{
	Q_OBJECT;
public:
	InterFaceInputPort( const QString &name )
		: InterFaceTypeInputPort( name ) { }
};

#endif // INTERFACEINPUTPORT_H_H_HEAD__FILE__
