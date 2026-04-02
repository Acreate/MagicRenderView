#ifndef POINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define POINTTYPEOUTPUTPORT_H_H_HEAD__FILE__


#include "outputPort.h"

class PointTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	PointTypeOutputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override;
};
#endif // POINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
