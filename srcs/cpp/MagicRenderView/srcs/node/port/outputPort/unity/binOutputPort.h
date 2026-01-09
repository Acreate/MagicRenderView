#ifndef BINOUTPUTPORT_H_H_HEAD__FILE__
#define BINOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../unityTypeOutputPort.h"

class BinOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	BinOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // BINOUTPUTPORT_H_H_HEAD__FILE__
