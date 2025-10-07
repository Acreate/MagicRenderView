#ifndef BINOUTPUTPORT_H_H_HEAD__FILE__
#define BINOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeOutputPort.h"

class BinOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = uint8_t;
public:
	BinOutputPort( NodeItem *parent );
};

#endif // BINOUTPUTPORT_H_H_HEAD__FILE__
