#ifndef file_mac_H_HEAD__FILE__
#define file_mac_H_HEAD__FILE__

#include "../generateTypeInputPort.h"

class GenerateFloatInputPort : public GenerateTypeInputPort {
	Q_OBJECT;
public:
	GenerateFloatInputPort( const QString &name )
		: GenerateTypeInputPort( name ) { }
};
#endif // file_mac_H_HEAD__FILE__
