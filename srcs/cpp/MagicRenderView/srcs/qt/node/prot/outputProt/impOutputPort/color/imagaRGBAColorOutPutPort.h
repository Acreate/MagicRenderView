#ifndef IMAGARGBACOLOROUTPUTPORT_H_H_HEAD__FILE__
#define IMAGARGBACOLOROUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeOutputPort.h"

class ImagaRGBAColorOutPutPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = QImage;
public:
	ImagaRGBAColorOutPutPort( NodeItem *parent );
};

#endif // IMAGARGBACOLOROUTPUTPORT_H_H_HEAD__FILE__
