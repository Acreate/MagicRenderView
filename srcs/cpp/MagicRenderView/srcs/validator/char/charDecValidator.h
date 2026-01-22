#ifndef CHARDECVALIDATOR_H_H_HEAD__FILE__
#define CHARDECVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class CharDecValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	CharDecValidator( QObject *parent );
	~CharDecValidator( ) override;
};
#endif // CHARDECVALIDATOR_H_H_HEAD__FILE__
