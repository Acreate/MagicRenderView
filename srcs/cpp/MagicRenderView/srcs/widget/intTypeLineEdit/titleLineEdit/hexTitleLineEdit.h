#ifndef HEXTITLELINEEDIT_H_H_HEAD__FILE__
#define HEXTITLELINEEDIT_H_H_HEAD__FILE__

#include "numberVarTitleLineEdit.h"

class HexTitleLineEdit : public NumberVarTitleLineEdit {
	Q_OBJECT;
public:
	HexTitleLineEdit( const QString &titile_text, uint64_t max_var, bool is_un_sign, QWidget *parent );
};
#endif // HEXTITLELINEEDIT_H_H_HEAD__FILE__
