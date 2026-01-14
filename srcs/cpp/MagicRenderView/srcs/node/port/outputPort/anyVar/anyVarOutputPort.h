#ifndef ANYVAROUTPUTPORT_H_H_HEAD__FILE__
#define ANYVAROUTPUTPORT_H_H_HEAD__FILE__


#include "../anyVarTypeOutputPort.h"

class AnyVarOutputPort : public AnyVarTypeOutputPort {
	Q_OBJECT;
public:
	AnyVarOutputPort( const QString &name )
		: AnyVarTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};
#endif // ANYVAROUTPUTPORT_H_H_HEAD__FILE__
