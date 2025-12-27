#include "applicationMenuStack.h"

#include <QMenu>
#include <QToolBar>

#include "../../app/application.h"
#include "../../menu/app/action/normalApplicationAction.h"
#include "../../menu/app/imp/action/app/quitAppAction.h"
#include "../../menu/app/imp/action/app/resetAppAction.h"
#include "../../menu/app/imp/action/builder/builderPorjectAction.h"
#include "../../menu/app/imp/action/builder/nextStepBuilderAction.h"
#include "../../menu/app/imp/action/builder/runBuilderAction.h"
#include "../../menu/app/imp/action/builder/stopBuilderAction.h"
#include "../../menu/app/imp/action/editor/copyNodeAction.h"
#include "../../menu/app/imp/action/editor/cutNodeAction.h"
#include "../../menu/app/imp/action/editor/pasteNodeAction.h"

#include "../../menu/app/imp/action/project/clearProjectAction.h"
#include "../../menu/app/imp/action/project/closeProjectAction.h"
#include "../../menu/app/imp/action/project/openProjectAction.h"
#include "../../menu/app/imp/action/project/reLoadProjectAction.h"
#include "../../menu/app/imp/action/project/saveAsProjectAction.h"
#include "../../menu/app/imp/action/project/savePorjectAction.h"
#include "../../menu/app/imp/action/project/updateProjectAction.h"
#include "../../menu/app/imp/menu/builderApplicationMenu.h"
#include "../../menu/app/imp/menu/projectApplicationMenu.h"
#include "../../menu/app/imp/toolBar/builderApplicationToolBar.h"
#include "../../menu/app/imp/toolBar/projectApplicationToolBar.h"

#include "../../menu/app/normalApplicationMenu.h"
#include "../../menu/app/normalApplicationToolBar.h"

#define generator( base_template_type_name_, type_name_ ) \
	[this] -> base_template_type_name_* {\
		base_template_type_name_ *resultPtr = new type_name_( ); \
		if( resultPtr->init( this ) == true )\
			return resultPtr;\
		delete resultPtr;\
		return nullptr;\
	}
#define generator_type_uinty( base_template_type_name_, type_name_, str_type_name_, ...  ) \
	Generator< base_template_type_name_ > ( generator(base_template_type_name_, type_name_ ),#type_name_, {  str_type_name_,QString( typeid(type_name_).name(  )),__VA_ARGS__} )

bool ApplicationMenuStack::initActionGenerator( ) {

	// 项目操作 action
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, OpenProjectAction, tr( "打开文件" ), tr( "打开..." ), tr( "打开项目" ), tr( "打开项目..." ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, ClearProjectAction, tr( "清理文件" ), tr( "清理项目" ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, CloseProjectAction, tr( "关闭文件" ), tr( "关闭项目" ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, SavePorjectAction, tr( "保存文件" ), tr( "保存项目" ), tr( "保存文件..." ), tr( "保存项目..." ), tr( "存为文件" ), tr( "存为项目" ), tr( "存为文件..." ), tr( "存为项目..." ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, SaveAsProjectAction, tr( "另存为文件" ), tr( "另存为项目" ), tr( "另存为文件..." ), tr( "另存为项目..." ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, ReLoadProjectAction, tr( "重新加载项目" ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, UpdateProjectAction, tr( "刷新当前项目" ) ) );
	// 编译操作 action
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, BuilderPorjectAction, tr( "编译项目" ), tr( "编译文件" ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, NextStepBuilderAction, tr( "运行下一步" ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, RunBuilderAction, tr( "运行" ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, StopBuilderAction, tr( "停止" ) ) );
	// 编辑器操作 action
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, CopyNodeAction, tr( "拷贝" ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, CutNodeAction, tr( "剪切" ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, PasteNodeAction, tr( "粘贴" ) ) );
	// 软件操作 action
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, QuitAppAction, tr( "退出软件" ) ) );
	actionGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationAction, ResetAppAction, tr( "重启软件" ) ) );
	return true;
}
bool ApplicationMenuStack::initMenuGenerator( ) {
	menuGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationMenu, ProjectApplicationMenu, tr( "文件" ) ) );
	menuGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationMenu, BuilderApplicationMenu, tr( "编译" ) ) );

	return true;
}
bool ApplicationMenuStack::initToolBarGenerator( ) {
	toolBarGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationToolBar, ProjectApplicationToolBar, tr( "文件" ) ) );
	toolBarGeneratorArray.appendGenerator( generator_type_uinty( NormalApplicationToolBar, BuilderApplicationToolBar, tr( "编译" ) ) );
	return true;
}
ApplicationMenuStack::ApplicationMenuStack( QObject *parent ) : QObject( parent ) {

}

bool ApplicationMenuStack::initStack( ) {
	application = Application::getInstancePtr( );
	if( initActionGenerator( ) == false )
		return false;
	if( initMenuGenerator( ) == false )
		return false;
	if( initToolBarGenerator( ) == false )
		return false;
	return true;
}
NormalApplicationToolBar * ApplicationMenuStack::getToolBar( const QString &tool_menu_name ) {
	NormalApplicationToolBar *fromTypeCreate = toolBarGeneratorArray.fromTypeCreate( tool_menu_name );
	if( fromTypeCreate == nullptr ) {
		fromTypeCreate = toolBarGeneratorArray.fromAliasTypeCreate( tool_menu_name );
		if( fromTypeCreate == nullptr )
			return nullptr;
	}
	return fromTypeCreate;
}
NormalApplicationMenu * ApplicationMenuStack::getMenu( const QString &tool_menu_name ) {
	NormalApplicationMenu *fromTypeCreate = menuGeneratorArray.fromTypeCreate( tool_menu_name );
	if( fromTypeCreate == nullptr ) {
		fromTypeCreate = menuGeneratorArray.fromAliasTypeCreate( tool_menu_name );
		if( fromTypeCreate == nullptr )
			return nullptr;
	}
	return fromTypeCreate;
}
NormalApplicationAction * ApplicationMenuStack::getAction( const QString &acton_name ) {
	NormalApplicationAction *fromTypeCreate = actionGeneratorArray.fromTypeCreate( acton_name );
	if( fromTypeCreate == nullptr ) {
		fromTypeCreate = actionGeneratorArray.fromAliasTypeCreate( acton_name );
		if( fromTypeCreate == nullptr )
			return nullptr;
	}
	return fromTypeCreate;
}
