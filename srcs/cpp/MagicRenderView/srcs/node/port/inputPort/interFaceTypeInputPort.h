#ifndef INTERFACETYPEINPUTPORT_H_H_HEAD__FILE__
#define INTERFACETYPEINPUTPORT_H_H_HEAD__FILE__


#include "inputPort.h"

class InterFaceTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	InterFaceTypeInputPort( const QString &name )
		: InputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::InterFace;
	}
	bool isMultiple( ) override { return true; }
};
#endif // INTERFACETYPEINPUTPORT_H_H_HEAD__FILE__
