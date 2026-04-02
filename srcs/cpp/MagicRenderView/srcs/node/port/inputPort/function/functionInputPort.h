#ifndef FUNCTIONINPUTPORT_H_H_HEAD__FILE__
#define FUNCTIONINPUTPORT_H_H_HEAD__FILE__
#include "../functionTypeInputPort.h"

class FunctionInputPort : public FunctionTypeInputPort {
	Q_OBJECT;
public:
	FunctionInputPort( const QString &name )
		: FunctionTypeInputPort( name ) { }
};

#endif // FUNCTIONINPUTPORT_H_H_HEAD__FILE__
