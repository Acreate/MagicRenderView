#ifndef CALLTYPEINPUTPORT_H_H_HEAD__FILE__
#define CALLTYPEINPUTPORT_H_H_HEAD__FILE__

#include "inputPort.h"

class CallTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	CallTypeInputPort( const QString &name );

	NodeEnum::PortType getPortType( ) const override;
};
#endif // CALLTYPEINPUTPORT_H_H_HEAD__FILE__
