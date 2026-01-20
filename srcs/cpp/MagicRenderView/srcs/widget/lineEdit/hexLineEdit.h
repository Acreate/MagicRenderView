#ifndef HEXLINEEDIT_H_H_HEAD__FILE__
#define HEXLINEEDIT_H_H_HEAD__FILE__

#include <QLineEdit>

#include "numberVarLineEdit.h"
class HexLineEdit : public NumberVarLineEdit {
	Q_OBJECT;
public:
	HexLineEdit( uint64_t value, QWidget *parent );
};

#endif // HEXLINEEDIT_H_H_HEAD__FILE__
