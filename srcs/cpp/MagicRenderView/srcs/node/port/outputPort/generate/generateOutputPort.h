#ifndef GENERATEOUTPUTPORT_H_H_HEAD__FILE__
#define GENERATEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../generateTypeOutputPort.h"

class GenerateOutputPort: public GenerateTypeOutputPort{
	Q_OBJECT;
public:
	GenerateOutputPort( const QString &name )
		: GenerateTypeOutputPort( name ) { }
};

#endif // GENERATEOUTPUTPORT_H_H_HEAD__FILE__
