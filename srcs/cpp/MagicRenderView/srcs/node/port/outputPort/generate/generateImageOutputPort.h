#ifndef GENERATEIMAGEOUTPUTPORT_H_H_HEAD__FILE__
#define GENERATEIMAGEOUTPUTPORT_H_H_HEAD__FILE__


#include "../generateTypeOutputPort.h"

class GenerateImageOutputPort : public GenerateTypeOutputPort{
	Q_OBJECT;
public:
	GenerateImageOutputPort( const QString &name )
		: GenerateTypeOutputPort( name ) { }
	bool init(Node *parent) override;
};
#endif // GENERATEIMAGEOUTPUTPORT_H_H_HEAD__FILE__
