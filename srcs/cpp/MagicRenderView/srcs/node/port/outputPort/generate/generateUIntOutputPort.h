#ifndef GENERATEUINTOUTPUTPORT_H_H_HEAD__FILE__
#define GENERATEUINTOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../generateTypeOutputPort.h"

class GenerateUIntOutputPort : public GenerateTypeOutputPort{
	Q_OBJECT;
public:
	GenerateUIntOutputPort( const QString &name )
		: GenerateTypeOutputPort( name ) { }
	bool init(Node *parent) override;
};
#endif // GENERATEUINTOUTPUTPORT_H_H_HEAD__FILE__
