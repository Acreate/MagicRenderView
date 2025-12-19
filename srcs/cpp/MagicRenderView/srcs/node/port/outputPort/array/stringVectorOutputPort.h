#ifndef STRINGVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define STRINGVECTOROUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../arrayTypeOutputPort.h"

class StringVectorOutputPort : public ArrayTypeOutputPort {
	Q_OBJECT;
public:
	StringVectorOutputPort( const QString &name )
		: ArrayTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // STRINGVECTOROUTPUTPORT_H_H_HEAD__FILE__
