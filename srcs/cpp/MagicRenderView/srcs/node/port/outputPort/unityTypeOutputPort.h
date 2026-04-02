#ifndef UNITYTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define UNITYTYPEOUTPUTPORT_H_H_HEAD__FILE__

#include "outputPort.h"

class UnityTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	UnityTypeOutputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override;
};

#endif // UNITYTYPEOUTPUTPORT_H_H_HEAD__FILE__
