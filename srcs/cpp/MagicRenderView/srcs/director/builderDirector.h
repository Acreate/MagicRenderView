#ifndef BUILDERDIRECTOR_H_H_HEAD__FILE__
#define BUILDERDIRECTOR_H_H_HEAD__FILE__

#include <QObject>

#include "../menu/app/imp/menu/builderApplicationMenu.h"
#include "../menu/app/imp/toolBar/builderApplicationToolBar.h"

class Node;
class NormalApplicationToolBar;
class NormalApplicationMenu;
class BuilderApplicationToolBar;
class BuilderApplicationMenu;
class NodeRunInfo;
class NodeDirector;
class Application;
class MainWindow;
class BuilderDirector : public QObject {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	Application *instancePtr;
	NodeDirector *nodeDirector;
	NodeRunInfo *nodeRunInfo;
protected:
	std::vector< BuilderApplicationMenu * > menus;
	std::vector< BuilderApplicationToolBar * > toolBars;
protected:
	virtual void resetBuilderMenuActionObjInfo( BuilderApplicationMenu::BuilderApplicationMenuActionList &builder_app_menu_action_list );
	virtual void resetBuilderToolBarActionObjInfo( BuilderApplicationToolBar::BuilderApplicationToolBarActionList &builder_app_tool_bar_action_list );
	virtual void validBuilderMenuActionObjInfo( BuilderApplicationMenu::BuilderApplicationMenuActionList &builder_app_menu_action_list );
	virtual void validBuilderToolBarActionObjInfo( BuilderApplicationToolBar::BuilderApplicationToolBarActionList &builder_app_tool_bar_action_list );

	virtual void setRunNodeStatusBuilderMenuActionObjInfo( BuilderApplicationMenu::BuilderApplicationMenuActionList &builder_app_menu_action_list );
	virtual void setRunNodeStatusBuilderToolBarActionObjInfo( BuilderApplicationToolBar::BuilderApplicationToolBarActionList &builder_app_tool_bar_action_list );

	virtual void updateBuilderActionObjInfo( );
	virtual void setRunNodeStatusAction( );
	virtual void resetBuilderActionObjInfo( );
	virtual void validBuilderActionObjInfo( );
	virtual void removeMenu( NormalApplicationMenu *remove_target );
	virtual void removeToolBar( NormalApplicationToolBar *remove_target );
protected Q_SLOTS:
	/// @brief 当自动运行状态被改变时，发出该信号
	/// @param change_obj 信号对象 
	/// @param new_status 新的状态
	virtual void autoRunStatusChange_Slot( NodeRunInfo *change_obj, bool new_status );
public:
	BuilderDirector( );
	~BuilderDirector( ) override;
	virtual bool init( );
	virtual bool addMenu( BuilderApplicationMenu *builder_application_menu );
	virtual bool addToolBar( BuilderApplicationToolBar *builder_application_tool_bar );
	virtual bool runToNextFrame( );
	virtual bool runToTargetNode( const Node *target_node_ptr );
	virtual bool builderNodeProject( );
	virtual bool resetStartNodeProject( );
	virtual bool nextStepBuilderNode( );
	virtual bool runBuilderBuilderNode( );
	virtual bool stopBuilderBuilderNode( );
	virtual NodeRunInfo * getNodeRunInfo( ) const { return nodeRunInfo; }
Q_SIGNALS:
	void release_node_run_info_signal( BuilderDirector *signal_ptr, NodeRunInfo *node_run_info );
	void create_node_run_info_signalr( BuilderDirector *signal_ptr, NodeRunInfo *node_run_info );
};

#endif // BUILDERDIRECTOR_H_H_HEAD__FILE__
