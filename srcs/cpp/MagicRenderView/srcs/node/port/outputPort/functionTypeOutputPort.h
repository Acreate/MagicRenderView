#ifndef FUNCTIONTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define FUNCTIONTYPEOUTPUTPORT_H_H_HEAD__FILE__


#include "outputPort.h"

class FunctionTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	FunctionTypeOutputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override;
};
#endif // FUNCTIONTYPEOUTPUTPORT_H_H_HEAD__FILE__
