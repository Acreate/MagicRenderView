#ifndef INT64HEXVALIDATOR_H_H_HEAD__FILE__
#define INT64HEXVALIDATOR_H_H_HEAD__FILE__

#include "../validator.h"

class Int64HexValidator : public Validator {
	Q_OBJECT;
protected:
	uint64_t maxLen;
	uint64_t binSystem;
public:
	Int64HexValidator( QObject *parent );
	~Int64HexValidator( ) override;
};
#endif // INT64HEXVALIDATOR_H_H_HEAD__FILE__
