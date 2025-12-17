#ifndef JUMPINPUTPORT_H_H_HEAD__FILE__
#define JUMPINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../jumpTypeInputPort.h"

class JumpInputPort : public JumpTypeInputPort{
	Q_OBJECT;
public:
	JumpInputPort( const QString &name )
		: JumpTypeInputPort( name ) { }
};

#endif // JUMPINPUTPORT_H_H_HEAD__FILE__
