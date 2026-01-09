#ifndef GENERATEBININPUTPORT_H_H_HEAD__FILE__
#define GENERATEBININPUTPORT_H_H_HEAD__FILE__


#include "../generateTypeInputPort.h"

class GenerateBinInputPort : public GenerateTypeInputPort {
	Q_OBJECT;
public:
	GenerateBinInputPort( const QString &name )
		: GenerateTypeInputPort( name ) { }
};
#endif // GENERATEBININPUTPORT_H_H_HEAD__FILE__
