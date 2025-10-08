#ifndef INTINPUTPORT_H_H_HEAD__FILE__
#define INTINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInputPort.h"

class IntInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = int64_t;
public:
	IntInputPort( NodeItem *parent );
};

#endif // INTINPUTPORT_H_H_HEAD__FILE__
