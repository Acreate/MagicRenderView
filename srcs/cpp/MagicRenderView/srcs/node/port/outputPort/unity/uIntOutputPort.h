#ifndef UINTOUTPUTPORT_H_H_HEAD__FILE__
#define UINTOUTPUTPORT_H_H_HEAD__FILE__

#include "../unityTypeOutputPort.h"


class UIntOutputPort : public UnityTypeOutputPort {
	Q_OBJECT;
public:
	UIntOutputPort( const QString &name )
		: UnityTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // UINTOUTPUTPORT_H_H_HEAD__FILE__
