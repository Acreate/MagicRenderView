#ifndef STRINGOUTPUTPORT_H_H_HEAD__FILE__
#define STRINGOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../unityTypeOutputPort.h"

class StringOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	StringOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // STRINGOUTPUTPORT_H_H_HEAD__FILE__
