#ifndef TIMEOUTPUTPORT_H_H_HEAD__FILE__
#define TIMEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once


#include "../../nodeOutputPort.h"

class TimeOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = QDateTime;
public:
	TimeOutputPort( NodeItem *parent );
};

#endif // TIMEOUTPUTPORT_H_H_HEAD__FILE__
