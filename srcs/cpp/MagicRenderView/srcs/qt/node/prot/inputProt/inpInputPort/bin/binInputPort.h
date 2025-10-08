#ifndef BININPUTPORT_H_H_HEAD__FILE__
#define BININPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInputPort.h"

class BinInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = uint8_t;
public:
	BinInputPort( NodeItem *parent );
};

#endif // BININPUTPORT_H_H_HEAD__FILE__
