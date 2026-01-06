#ifndef ANYVARINPUTPORT_H_H_HEAD__FILE__
#define ANYVARINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../anyVarTypeInputPort.h"

class AnyVarInputPort : public AnyVarTypeInputPort {
	Q_OBJECT;
public:
	AnyVarInputPort( const QString &name )
		: AnyVarTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // ANYVARINPUTPORT_H_H_HEAD__FILE__
