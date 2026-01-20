#ifndef OCTLINEEDIT_H_H_HEAD__FILE__
#define OCTLINEEDIT_H_H_HEAD__FILE__


#include "numberVarLineEdit.h"
class OctLineEdit : public NumberVarLineEdit {
	Q_OBJECT;
public:
	OctLineEdit( uint64_t value, QWidget *parent );
};

#endif // OCTLINEEDIT_H_H_HEAD__FILE__
