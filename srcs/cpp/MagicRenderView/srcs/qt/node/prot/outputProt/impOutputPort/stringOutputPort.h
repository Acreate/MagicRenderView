#ifndef STRINGOUTPUTPORT_H_H_HEAD__FILE__
#define STRINGOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../nodeOutputPort.h"

class StringOutputPort : public NodeOutputPort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeOutputPort );
public:
	StringOutputPort( NodeItem *parent );
};

#endif // STRINGOUTPUTPORT_H_H_HEAD__FILE__
