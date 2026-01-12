#ifndef GENERATESTRINGOUTPUTPORT_H_H_HEAD__FILE__
#define GENERATESTRINGOUTPUTPORT_H_H_HEAD__FILE__

#include "../generateTypeOutputPort.h"

class GenerateStringOutputPort : public GenerateTypeOutputPort {
	Q_OBJECT;
public:
	GenerateStringOutputPort( const QString &name )
		: GenerateTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
};

#endif // GENERATESTRINGOUTPUTPORT_H_H_HEAD__FILE__
