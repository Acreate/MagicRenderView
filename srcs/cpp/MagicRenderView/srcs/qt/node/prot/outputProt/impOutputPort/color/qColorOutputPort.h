#ifndef QCOLOROUTPUTPORT_H_H_HEAD__FILE__
#define QCOLOROUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeOutputPort.h"

class QColorOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = QColor;
public:
	QColorOutputPort( NodeItem *parent );
};
#endif // QCOLOROUTPUTPORT_H_H_HEAD__FILE__
