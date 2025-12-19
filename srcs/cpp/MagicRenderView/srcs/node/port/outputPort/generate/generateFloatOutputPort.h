#ifndef GENERATEFLOATOUTPUTPORT_H_H_HEAD__FILE__
#define GENERATEFLOATOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../generateTypeOutputPort.h"

class GenerateFloatOutputPort : public GenerateTypeOutputPort{
	Q_OBJECT;
public:
	GenerateFloatOutputPort( const QString &name )
		: GenerateTypeOutputPort( name ) { }
	bool init(Node *parent) override;
};

#endif // GENERATEFLOATOUTPUTPORT_H_H_HEAD__FILE__
