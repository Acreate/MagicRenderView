#ifndef ARRAYTYPEINPUTPORT_H_H_HEAD__FILE__
#define ARRAYTYPEINPUTPORT_H_H_HEAD__FILE__

#include "inputPort.h"

class ArrayTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	ArrayTypeInputPort( const QString &name );

	NodeEnum::PortType getPortType( ) const override;
};
#endif // ARRAYTYPEINPUTPORT_H_H_HEAD__FILE__
