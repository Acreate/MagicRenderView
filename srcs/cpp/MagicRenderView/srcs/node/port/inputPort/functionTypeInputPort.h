#ifndef FUNCTIONTYPEINPUTPORT_H_H_HEAD__FILE__
#define FUNCTIONTYPEINPUTPORT_H_H_HEAD__FILE__


#include "inputPort.h"

class FunctionTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	FunctionTypeInputPort( const QString &name );

	NodeEnum::PortType getPortType( ) const override;
};
#endif // FUNCTIONTYPEINPUTPORT_H_H_HEAD__FILE__
