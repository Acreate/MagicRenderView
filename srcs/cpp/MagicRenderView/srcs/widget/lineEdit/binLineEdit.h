#ifndef BINLINEEDIT_H_H_HEAD__FILE__
#define BINLINEEDIT_H_H_HEAD__FILE__


#include "numberVarLineEdit.h"
class BinLineEdit : public NumberVarLineEdit {
	Q_OBJECT;
public:
	BinLineEdit( uint64_t value, QWidget *parent );
};

#endif // BINLINEEDIT_H_H_HEAD__FILE__
