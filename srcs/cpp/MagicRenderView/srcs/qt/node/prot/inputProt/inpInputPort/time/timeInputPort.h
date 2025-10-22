#ifndef TIMEINPUTPORT_H_H_HEAD__FILE__
#define TIMEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../../nodeInputPort.h"

class TimeInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = QDateTime;
public:
	TimeInputPort( NodeItem *parent );
};

#endif // TIMEINPUTPORT_H_H_HEAD__FILE__
