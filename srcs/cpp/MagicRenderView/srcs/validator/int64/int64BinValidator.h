#ifndef INT64BINVALIDATOR_H_H_HEAD__FILE__
#define INT64BINVALIDATOR_H_H_HEAD__FILE__


#include "../validator.h"

class Int64BinValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Int64BinValidator( QObject *parent );
	~Int64BinValidator( ) override;
};
#endif // INT64BINVALIDATOR_H_H_HEAD__FILE__
