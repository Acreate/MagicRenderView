#ifndef ANYARRAYOUTPUTPORT_H_H_HEAD__FILE__
#define ANYARRAYOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeOutputPort.h"

class Any;
class AnyArrayOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = Any;
public:
	AnyArrayOutputPort( NodeItem *parent );
};

#endif // ANYARRAYOUTPUTPORT_H_H_HEAD__FILE__
