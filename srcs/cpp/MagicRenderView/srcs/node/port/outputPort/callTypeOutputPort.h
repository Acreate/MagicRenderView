#ifndef CALLTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define CALLTYPEOUTPUTPORT_H_H_HEAD__FILE__


#include "outputPort.h"

class CallTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	CallTypeOutputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override;
};
#endif // CALLTYPEOUTPUTPORT_H_H_HEAD__FILE__
