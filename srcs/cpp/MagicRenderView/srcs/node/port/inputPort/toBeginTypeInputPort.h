#ifndef TOBEGINTYPEINPUTPORT_H_H_HEAD__FILE__
#define TOBEGINTYPEINPUTPORT_H_H_HEAD__FILE__



#include "inputPort.h"

class ToBeginTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	ToBeginTypeInputPort( const QString &name )
		: InputPort( name ) { }

	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::ToBegin;
	}
};
#endif // TOBEGINTYPEINPUTPORT_H_H_HEAD__FILE__
