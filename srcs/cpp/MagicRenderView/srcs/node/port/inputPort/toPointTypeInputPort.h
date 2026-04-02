#ifndef TOPOINTTYPEINPUTPORT_H_H_HEAD__FILE__
#define TOPOINTTYPEINPUTPORT_H_H_HEAD__FILE__

#include "inputPort.h"

class ToPointTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	ToPointTypeInputPort( const QString &name );

	NodeEnum::PortType getPortType( ) const override;
};
#endif // TOPOINTTYPEINPUTPORT_H_H_HEAD__FILE__
