#ifndef UINT64OCTVALIDATOR_H_H_HEAD__FILE__
#define UINT64OCTVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>


class UInt64OctValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt64OctValidator( QObject *parent );
	~UInt64OctValidator( ) override;
};
#endif // UINT64OCTVALIDATOR_H_H_HEAD__FILE__
