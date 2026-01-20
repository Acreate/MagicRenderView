#ifndef DECLINEEDIT_H_H_HEAD__FILE__
#define DECLINEEDIT_H_H_HEAD__FILE__


#include "numberVarLineEdit.h"
class DecLineEdit : public NumberVarLineEdit {
	Q_OBJECT;
public:
	DecLineEdit( uint64_t value, QWidget *parent );
};

#endif // DECLINEEDIT_H_H_HEAD__FILE__
