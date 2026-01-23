#ifndef UINT8DECVALIDATOR_H_H_HEAD__FILE__
#define UINT8DECVALIDATOR_H_H_HEAD__FILE__

#include <validator/unSignedValidator.h>

class Uint8DecValidator : public UnSignedValidator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Uint8DecValidator( QObject *parent );
	~Uint8DecValidator( ) override;
};
#endif // UINT8DECVALIDATOR_H_H_HEAD__FILE__
