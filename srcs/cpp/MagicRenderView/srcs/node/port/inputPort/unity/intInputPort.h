#ifndef INTINPUTPORT_H_H_HEAD__FILE__
#define INTINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../unityTypeInputPort.h"

class IntInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	IntInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // INTINPUTPORT_H_H_HEAD__FILE__
