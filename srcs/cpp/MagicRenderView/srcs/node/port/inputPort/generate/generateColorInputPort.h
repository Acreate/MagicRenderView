#ifndef GENERATECOLORINPUTPORT_H_H_HEAD__FILE__
#define GENERATECOLORINPUTPORT_H_H_HEAD__FILE__


#include "../generateTypeInputPort.h"

class GenerateColorInputPort : public GenerateTypeInputPort {
	Q_OBJECT;
public:
	GenerateColorInputPort( const QString &name )
		: GenerateTypeInputPort( name ) { }
};
#endif // GENERATECOLORINPUTPORT_H_H_HEAD__FILE__
