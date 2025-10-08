#ifndef IMAGARGBACOLORINPUTPORT_H_H_HEAD__FILE__
#define IMAGARGBACOLORINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInputPort.h"

class ImagaRGBAColorInPutPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = QColor;
public:
	ImagaRGBAColorInPutPort( NodeItem *parent );
};

#endif // IMAGARGBACOLORINPUTPORT_H_H_HEAD__FILE__
