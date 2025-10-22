#ifndef INTOUTPUTPORT_H_H_HEAD__FILE__
#define INTOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeOutputPort.h"

class IntOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = int64_t;
public:
	IntOutputPort( NodeItem *parent );
};

#endif // INTOUTPUTPORT_H_H_HEAD__FILE__
