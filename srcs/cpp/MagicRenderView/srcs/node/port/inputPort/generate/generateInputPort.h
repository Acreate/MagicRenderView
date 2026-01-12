#ifndef GENERATEINPUTPORT_H_H_HEAD__FILE__
#define GENERATEINPUTPORT_H_H_HEAD__FILE__

#include "../generateTypeInputPort.h"

class GenerateInputPort : public GenerateTypeInputPort {
	Q_OBJECT;
public:
	GenerateInputPort( const QString &name )
		: GenerateTypeInputPort( name ) { }
};

#endif // GENERATEINPUTPORT_H_H_HEAD__FILE__
