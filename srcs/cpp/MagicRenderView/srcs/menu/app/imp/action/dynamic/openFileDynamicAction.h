#ifndef OPENFILEDYNAMICACTION_H_H_HEAD__FILE__
#define OPENFILEDYNAMICACTION_H_H_HEAD__FILE__

#include <menu/app/action/normalApplicationAction.h>

class OpenFileDynamicAction : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow *parent ) override;
	virtual bool setOpenFilePath( const QString &open_file_path );
};

#endif // OPENFILEDYNAMICACTION_H_H_HEAD__FILE__
