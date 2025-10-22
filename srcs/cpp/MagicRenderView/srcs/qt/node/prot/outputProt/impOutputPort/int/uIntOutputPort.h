#ifndef UINTOUTPUTPORT_H_H_HEAD__FILE__
#define UINTOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeOutputPort.h"

class UIntOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = uint64_t;
public:
	UIntOutputPort( NodeItem *parent );
};


#endif // UINTOUTPUTPORT_H_H_HEAD__FILE__
