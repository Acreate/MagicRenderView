#ifndef UINT8OCTVALIDATOR_H_H_HEAD__FILE__
#define UINT8OCTVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>

class Uint8OctValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Uint8OctValidator( QObject *parent );
	~Uint8OctValidator( ) override;
};
#endif // UINT8OCTVALIDATOR_H_H_HEAD__FILE__
