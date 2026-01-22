#ifndef DOUBLEOCTVALIDATOR_H_H_HEAD__FILE__
#define DOUBLEOCTVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class DoubleOctValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	DoubleOctValidator( QObject *parent );
	~DoubleOctValidator( ) override;
};
#endif // DOUBLEOCTVALIDATOR_H_H_HEAD__FILE__
