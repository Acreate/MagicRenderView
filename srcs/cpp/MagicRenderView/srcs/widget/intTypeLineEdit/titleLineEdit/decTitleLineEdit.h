#ifndef DECTITLELINEEDIT_H_H_HEAD__FILE__
#define DECTITLELINEEDIT_H_H_HEAD__FILE__

#include "numberVarTitleLineEdit.h"

class DecTitleLineEdit : public NumberVarTitleLineEdit {
	Q_OBJECT;
public:
	DecTitleLineEdit( const QString &titile_text, uint64_t max_var, bool is_un_sign, QWidget *parent );
};
#endif // DECTITLELINEEDIT_H_H_HEAD__FILE__
