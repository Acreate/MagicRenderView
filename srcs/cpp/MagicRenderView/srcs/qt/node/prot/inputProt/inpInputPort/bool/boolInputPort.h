#ifndef BOOLINPUTPORT_H_H_HEAD__FILE__
#define BOOLINPUTPORT_H_H_HEAD__FILE__
#pragma once


#include "../../nodeInputPort.h"

class BoolInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = bool;
public:
	BoolInputPort( NodeItem *parent );
};
#endif // BOOLINPUTPORT_H_H_HEAD__FILE__
