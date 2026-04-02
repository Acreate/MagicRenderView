#ifndef ANYVARTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define ANYVARTYPEOUTPUTPORT_H_H_HEAD__FILE__


#include "outputPort.h"

class AnyVarTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	AnyVarTypeOutputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override;
	bool init( Node *parent ) override;
};
#endif // ANYVARTYPEOUTPUTPORT_H_H_HEAD__FILE__
