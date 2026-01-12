#ifndef GENERATEINTOUTPUTPORT_H_H_HEAD__FILE__
#define GENERATEINTOUTPUTPORT_H_H_HEAD__FILE__

#include "../generateTypeOutputPort.h"

class GenerateIntOutputPort : public GenerateTypeOutputPort{
	Q_OBJECT;
public:
	GenerateIntOutputPort( const QString &name )
		: GenerateTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // GENERATEINTOUTPUTPORT_H_H_HEAD__FILE__
