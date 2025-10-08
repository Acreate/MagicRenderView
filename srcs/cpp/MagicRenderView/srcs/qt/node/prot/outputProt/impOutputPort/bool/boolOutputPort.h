#ifndef BOOLOUTPUTPORT_H_H_HEAD__FILE__
#define BOOLOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../../nodeOutputPort.h"

class BoolOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = double_t;
public:
	BoolOutputPort( NodeItem *parent );
};
#endif // BOOLOUTPUTPORT_H_H_HEAD__FILE__
