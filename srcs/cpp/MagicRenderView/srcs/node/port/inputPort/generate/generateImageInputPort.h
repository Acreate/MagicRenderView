#ifndef GENERATEIMAGEINPUTPORT_H_H_HEAD__FILE__
#define GENERATEIMAGEINPUTPORT_H_H_HEAD__FILE__


#include "../generateTypeInputPort.h"

class GenerateImageInputPort : public GenerateTypeInputPort {
	Q_OBJECT;
public:
	GenerateImageInputPort( const QString &name )
		: GenerateTypeInputPort( name ) { }
};
#endif // GENERATEIMAGEINPUTPORT_H_H_HEAD__FILE__
