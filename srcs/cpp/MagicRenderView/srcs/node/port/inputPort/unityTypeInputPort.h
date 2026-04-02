#ifndef UNITYTYPEINPUTPORT_H_H_HEAD__FILE__
#define UNITYTYPEINPUTPORT_H_H_HEAD__FILE__

#include "inputPort.h"

class UnityTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	UnityTypeInputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override;
};
#endif // UNITYTYPEINPUTPORT_H_H_HEAD__FILE__
