#ifndef POINTTYPEINPUTPORT_H_H_HEAD__FILE__
#define POINTTYPEINPUTPORT_H_H_HEAD__FILE__


#include "inputPort.h"

class PointTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	PointTypeInputPort( const QString &name );

	NodeEnum::PortType getPortType( ) const override;
};
#endif // POINTTYPEINPUTPORT_H_H_HEAD__FILE__
