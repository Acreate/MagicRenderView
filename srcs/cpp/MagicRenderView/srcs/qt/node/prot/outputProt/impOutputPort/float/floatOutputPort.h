#ifndef FLOATOUTPUTPORT_H_H_HEAD__FILE__
#define FLOATOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../../nodeOutputPort.h"

class FloatOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = double_t;
public:
	FloatOutputPort( NodeItem *parent );
};

#endif // FLOATOUTPUTPORT_H_H_HEAD__FILE__
