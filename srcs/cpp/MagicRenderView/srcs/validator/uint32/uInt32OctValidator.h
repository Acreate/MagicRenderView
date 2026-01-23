#ifndef UINT32OCTVALIDATOR_H_H_HEAD__FILE__
#define UINT32OCTVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>

class UInt32OctValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt32OctValidator( QObject *parent );
	~UInt32OctValidator( ) override;
};
#endif // UINT32OCTVALIDATOR_H_H_HEAD__FILE__
