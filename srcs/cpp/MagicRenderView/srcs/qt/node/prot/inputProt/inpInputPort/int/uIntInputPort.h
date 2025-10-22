#ifndef UINTINPUTPORT_H_H_HEAD__FILE__
#define UINTINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInputPort.h"

class UIntInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = uint64_t;
public:
	UIntInputPort( NodeItem *parent );
};


#endif // UINTINPUTPORT_H_H_HEAD__FILE__
