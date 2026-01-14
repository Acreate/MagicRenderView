#ifndef TOPOINTTYPEINPUTPORT_H_H_HEAD__FILE__
#define TOPOINTTYPEINPUTPORT_H_H_HEAD__FILE__

#include "inputPort.h"

class ToPointTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	ToPointTypeInputPort( const QString &name )
		: InputPort( name ) { }

	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::ToPoint;
	}
};
#endif // TOPOINTTYPEINPUTPORT_H_H_HEAD__FILE__
