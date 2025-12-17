#ifndef LOGICINPUTPORT_H_H_HEAD__FILE__
#define LOGICINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../logicTypeInputPort.h"

class LogicInputPort : public LogicTypeInputPort{
	Q_OBJECT;
public:
	LogicInputPort( const QString &name )
		: LogicTypeInputPort( name ) { }
};

#endif // LOGICINPUTPORT_H_H_HEAD__FILE__
