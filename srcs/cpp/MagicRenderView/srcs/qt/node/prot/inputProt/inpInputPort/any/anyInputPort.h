#ifndef ANYINPUTPORT_H_H_HEAD__FILE__
#define ANYINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../../nodeInputPort.h"

class AnyInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = void *;
public:
	AnyInputPort( NodeItem *parent );
};
#endif // ANYINPUTPORT_H_H_HEAD__FILE__
