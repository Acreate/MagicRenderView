#ifndef UINT8OCTVALIDATOR_H_H_HEAD__FILE__
#define UINT8OCTVALIDATOR_H_H_HEAD__FILE__


#include <validator/unSignedValidator.h>

class UInt8OctValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	UInt8OctValidator( QObject *parent );
	~UInt8OctValidator( ) override;
};
#endif // UINT8OCTVALIDATOR_H_H_HEAD__FILE__
