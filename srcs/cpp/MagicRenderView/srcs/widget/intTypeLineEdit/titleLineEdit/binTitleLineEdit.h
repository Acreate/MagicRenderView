#ifndef BINTITLELINEEDIT_H_H_HEAD__FILE__
#define BINTITLELINEEDIT_H_H_HEAD__FILE__


#include "numberVarTitleLineEdit.h"

class BinTitleLineEdit : public NumberVarTitleLineEdit {
	Q_OBJECT;
public:
	BinTitleLineEdit( const QString &titile_text, uint64_t max_var, QWidget *parent );
};
#endif // BINTITLELINEEDIT_H_H_HEAD__FILE__
