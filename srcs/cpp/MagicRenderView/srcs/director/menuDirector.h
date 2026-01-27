#ifndef MENUDIRECTOR_H_H_HEAD__FILE__
#define MENUDIRECTOR_H_H_HEAD__FILE__

#include <QObject>
#include <vector>

class EditorNodeMenuStack;
class GenerateNodeMenuStack;
class ApplicationMenuStack;
class MainWindow;
class MainWidget;
class NodeRunInfo;
class Application;
class NodeDirector;
class QShortcut;
class PrinterDirector;
class QAction;
class SrackInfo;
class MenuDirector : public QObject {
	Q_OBJECT;
protected:
	ApplicationMenuStack *applicationMenuStack;
	GenerateNodeMenuStack *generateNodeMenuStack;
	EditorNodeMenuStack *editorNodeMenuStack;
	Application *instancePtr;
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	MainWindow *mainWindow;
	MainWidget *mainWidget;
public:
	MenuDirector( QObject *parent = nullptr );
	~MenuDirector( ) override;
	virtual bool init( );
	virtual ApplicationMenuStack * getApplicationMenuStack( ) const { return applicationMenuStack; }
	virtual GenerateNodeMenuStack * getGenerateNodeMenuStack( ) const { return generateNodeMenuStack; }
	virtual EditorNodeMenuStack * getEditorNodeMenuStack( ) const { return editorNodeMenuStack; }
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_obj_ptr 释放对象指针
	/// @param srack_info 信号行
	void release_signal( MenuDirector *release_obj_ptr, const SrackInfo &srack_info );
};

#endif // MENUDIRECTOR_H_H_HEAD__FILE__
