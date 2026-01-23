#ifndef UINT16OCTVALIDATOR_H_H_HEAD__FILE__
#define UINT16OCTVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>

class UInt16OctValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt16OctValidator( QObject *parent );
	~UInt16OctValidator( ) override;
};
#endif // UINT16OCTVALIDATOR_H_H_HEAD__FILE__
