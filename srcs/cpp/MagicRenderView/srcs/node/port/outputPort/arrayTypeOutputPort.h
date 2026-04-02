#ifndef ARRAYTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define ARRAYTYPEOUTPUTPORT_H_H_HEAD__FILE__

#include "outputPort.h"

class ArrayTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	ArrayTypeOutputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override;
};

#endif // ARRAYTYPEOUTPUTPORT_H_H_HEAD__FILE__
