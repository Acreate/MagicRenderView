#ifndef TOBEGINOUTPUTPORT_H_H_HEAD__FILE__
#define TOBEGINOUTPUTPORT_H_H_HEAD__FILE__


#include "../toBeginTypeOutputPort.h"

class ToBeginOutputPort : public ToBeginTypeOutputPort {
	Q_OBJECT;
public:
	ToBeginOutputPort( const QString &name )
		: ToBeginTypeOutputPort( name ) { }
};

#endif // TOBEGINOUTPUTPORT_H_H_HEAD__FILE__
