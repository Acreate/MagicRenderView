#ifndef CHARBINVALIDATOR_H_H_HEAD__FILE__
#define CHARBINVALIDATOR_H_H_HEAD__FILE__
#include "../validator.h"

class CharBinValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	CharBinValidator( QObject *parent );
	~CharBinValidator( ) override;
};
#endif // CHARBINVALIDATOR_H_H_HEAD__FILE__
