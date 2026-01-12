#ifndef UINTINPUTPORT_H_H_HEAD__FILE__
#define UINTINPUTPORT_H_H_HEAD__FILE__


#include "../unityTypeInputPort.h"

class UIntInputPort : public UnityTypeInputPort {
	Q_OBJECT;
public:
	UIntInputPort( const QString &name )
		: UnityTypeInputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // UINTINPUTPORT_H_H_HEAD__FILE__
