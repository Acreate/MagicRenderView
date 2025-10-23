#ifndef QIMAGEINPUTPORT_H_H_HEAD__FILE__
#define QIMAGEINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../../nodeInputPort.h"

class QImageInputPort : public NodeInputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeInputPort );
protected:
	using t_current_type = QImage;
public:
	QImageInputPort( NodeItem *parent );
};
#endif // QIMAGEINPUTPORT_H_H_HEAD__FILE__
