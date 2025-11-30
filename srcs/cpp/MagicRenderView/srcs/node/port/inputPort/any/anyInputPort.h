#ifndef ANYINPUTPORT_H_H_HEAD__FILE__
#define ANYINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../anyTypeInputPort.h"

class AnyInputPort : public AnyTypeInputPort {
	Q_OBJECT;
public:
	AnyInputPort( const QString &name )
		: AnyTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // ANYINPUTPORT_H_H_HEAD__FILE__
