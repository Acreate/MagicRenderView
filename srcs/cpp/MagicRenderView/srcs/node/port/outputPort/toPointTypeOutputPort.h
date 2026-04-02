#ifndef TOPOINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define TOPOINTTYPEOUTPUTPORT_H_H_HEAD__FILE__


#include "outputPort.h"

class ToPointTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	ToPointTypeOutputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override;
};
#endif // TOPOINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
