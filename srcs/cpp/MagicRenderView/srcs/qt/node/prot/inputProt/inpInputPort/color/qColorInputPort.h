#ifndef QCOLORINPUTPORT_H_H_HEAD__FILE__
#define QCOLORINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInputPort.h"

class QColorInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = QColor;
public:
	QColorInputPort( NodeItem *parent );
};

#endif // QCOLORINPUTPORT_H_H_HEAD__FILE__
