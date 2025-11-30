#ifndef STRINGINPUTPORT_H_H_HEAD__FILE__
#define STRINGINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../unityTypeInputPort.h"

class StringInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	StringInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // STRINGINPUTPORT_H_H_HEAD__FILE__
