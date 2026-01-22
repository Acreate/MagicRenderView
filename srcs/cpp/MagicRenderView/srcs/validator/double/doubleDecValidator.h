#ifndef DOUBLEDECVALIDATOR_H_H_HEAD__FILE__
#define DOUBLEDECVALIDATOR_H_H_HEAD__FILE__


#include "../validator.h"

class DoubleDecValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	DoubleDecValidator( QObject *parent );
	~DoubleDecValidator( ) override;
};
#endif // DOUBLEDECVALIDATOR_H_H_HEAD__FILE__
