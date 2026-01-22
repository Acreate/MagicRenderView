#ifndef DOUBLEBINVALIDATOR_H_H_HEAD__FILE__
#define DOUBLEBINVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class DoubleBinValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	DoubleBinValidator( QObject *parent );
	~DoubleBinValidator( ) override;
};
#endif // DOUBLEBINVALIDATOR_H_H_HEAD__FILE__
