#ifndef QIMAGEOUTPUTPORT_H_H_HEAD__FILE__
#define QIMAGEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeOutputPort.h"

class QImageOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
protected:
	using t_current_type = QImage;
public:
	QImageOutputPort( NodeItem *parent );
};
#endif // QIMAGEOUTPUTPORT_H_H_HEAD__FILE__
