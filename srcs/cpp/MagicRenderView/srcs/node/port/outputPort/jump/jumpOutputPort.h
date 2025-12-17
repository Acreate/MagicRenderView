#ifndef JUMPOUTPUTPORT_H_H_HEAD__FILE__
#define JUMPOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../jumpTypeOutputPort.h"

class JumpOutputPort : public JumpTypeOutputPort {
	Q_OBJECT;
public:
	JumpOutputPort( const QString &name )
		: JumpTypeOutputPort( name ) { }
};

#endif // JUMPOUTPUTPORT_H_H_HEAD__FILE__
