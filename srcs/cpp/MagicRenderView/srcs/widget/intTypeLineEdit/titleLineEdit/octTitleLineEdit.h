#ifndef OCTTITLELINEEDIT_H_H_HEAD__FILE__
#define OCTTITLELINEEDIT_H_H_HEAD__FILE__

#include "numberVarTitleLineEdit.h"

class OctTitleLineEdit : public NumberVarTitleLineEdit {
	Q_OBJECT;
public:
	OctTitleLineEdit( const QString &titile_text, uint64_t max_var, bool is_un_sign, QWidget *parent );
};

#endif // OCTTITLELINEEDIT_H_H_HEAD__FILE__
