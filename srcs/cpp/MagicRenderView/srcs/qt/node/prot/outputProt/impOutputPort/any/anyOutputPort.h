#ifndef ANYOUTPUTPORT_H_H_HEAD__FILE__
#define ANYOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../../nodeOutputPort.h"

class AnyOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = void *;
public:
	AnyOutputPort( NodeItem *parent );
};
#endif // ANYOUTPUTPORT_H_H_HEAD__FILE__
