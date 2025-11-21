#ifndef ANYARRAYINPUTPORT_H_H_HEAD__FILE__
#define ANYARRAYINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInputPort.h"

class Any;
class AnyArrayInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = Any;
public:
	AnyArrayInputPort( NodeItem *parent );
};
#endif // ANYARRAYINPUTPORT_H_H_HEAD__FILE__
