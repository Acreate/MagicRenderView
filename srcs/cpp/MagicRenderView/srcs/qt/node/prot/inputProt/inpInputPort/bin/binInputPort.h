#ifndef BININPUTPORT_H_H_HEAD__FILE__
#define BININPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInputPort.h"

class BinInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
public:
	BinInputPort( NodeItem *parent );
};

#endif // BININPUTPORT_H_H_HEAD__FILE__
