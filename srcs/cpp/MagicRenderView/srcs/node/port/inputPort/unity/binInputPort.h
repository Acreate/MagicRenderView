#ifndef BININPUTPORT_H_H_HEAD__FILE__
#define BININPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../unityTypeInputPort.h"

class BinInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	BinInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // BININPUTPORT_H_H_HEAD__FILE__
