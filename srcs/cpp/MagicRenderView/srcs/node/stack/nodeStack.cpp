#include "nodeStack.h"

#include <QMenu>

#include "../../app/application.h"

#include "../../director/printerDirector.h"

#include "../../widget/drawNodeWidget.h"
#include "../../widget/mainWidget.h"

#include "../../win/mainWindow.h"

#include "../node/node.h"
bool NodeStack::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	releaseMainMenu( );
	return true;
}
bool NodeStack::createMenuAtNodeType( const QString &node_type_name, const std::function< Node *( ) > &action_click_function ) {

	qsizetype qcharCount = node_type_name.length( );
	if( qcharCount == 0 )
		return false;
	QString buff;
	buff.resize( qcharCount );

	std::vector< QString > targetName;
	auto qcharArrayPtr = node_type_name.data( );
	auto buffArrayPtr = buff.data( );
	QString appendUnity;
	decltype(qcharCount) buffIndex = 0;
	decltype(qcharCount) index = 0;
	for( ; index < qcharCount; ++index )
		if( qcharArrayPtr[ index ] == '\\' || qcharArrayPtr[ index ] == '/' ) {
			if( buffIndex != 0 ) {
				appendUnity = QString( buffArrayPtr, buffIndex );
				targetName.emplace_back( appendUnity );
				buffIndex = 0;
			}
		} else {
			buffArrayPtr[ buffIndex ] = qcharArrayPtr[ index ];
			++buffIndex;
		}
	if( buffIndex != 0 ) {
		appendUnity = QString( buffArrayPtr, buffIndex );
		targetName.emplace_back( appendUnity );
	}

	size_t nameVectorCount = targetName.size( );
	if( nameVectorCount == 0 )
		return false;
	size_t foreachCount;
	size_t foreachIndex;
	QMenu *manu;
	std::pair< std::vector< QString >, QMenu * > *subMenuArrayPtr;
	std::vector< QString > compVector;
	size_t compVectorIndex;
	auto nameVectorArratPtr = targetName.data( );
	nameVectorCount -= 1; // 末尾名称作为 QAction 对象
	size_t nameVectorIndex = 0;
	size_t leftCount;
	size_t compVectorArrayCount;
	QString *compArrayPtr;
	QString *leftArray;
	if( nameVectorCount != 0 )
		do {
			compVector.emplace_back( nameVectorArratPtr[ nameVectorIndex ] );
			compVectorArrayCount = compVector.size( );
			compArrayPtr = compVector.data( );
			foreachCount = subMenus.size( );
			foreachIndex = 0;
			subMenuArrayPtr = subMenus.data( );
			for( ; foreachIndex < foreachCount; ++foreachIndex ) {
				leftCount = subMenuArrayPtr[ foreachIndex ].first.size( );
				if( leftCount != compVectorArrayCount )
					continue;
				leftArray = subMenuArrayPtr[ foreachIndex ].first.data( );
				for( compVectorIndex = 0; compVectorIndex < compVectorArrayCount; ++compVectorIndex )
					if( leftArray[ compVectorIndex ] != compArrayPtr[ compVectorIndex ] )
						break;
				if( compVectorIndex == compVectorArrayCount )
					break;
			}
			if( foreachIndex == foreachCount ) {
				manu = new QMenu( nameVectorArratPtr[ nameVectorIndex ] );
				// 寻找挂靠
				compVectorArrayCount -= 1;// 挂靠时。不需要末尾
				if( compVectorArrayCount != 0 ) {
					for( foreachIndex = 0; foreachIndex < foreachCount; ++foreachIndex ) {
						leftCount = subMenuArrayPtr[ foreachIndex ].first.size( );
						if( leftCount != compVectorArrayCount )
							continue;
						leftArray = subMenuArrayPtr[ foreachIndex ].first.data( );
						for( compVectorIndex = 0; compVectorIndex < compVectorArrayCount; ++compVectorIndex )
							if( leftArray[ compVectorIndex ] != compArrayPtr[ compVectorIndex ] )
								break;
						if( compVectorIndex == compVectorArrayCount )
							break;
					}
					if( foreachIndex == foreachCount ) {
						QString msg( "[ %1 ]节点菜单对象不存在挂靠的 QMenu" );
						printerDirector->error( msg.arg( appendUnity ) );
						return false;
					}
					subMenuArrayPtr[ foreachIndex ].second->addMenu( manu );
				}
				subMenus.emplace_back( compVector, manu );
			}
			buff = appendUnity;
			++nameVectorIndex;
		} while( nameVectorIndex < nameVectorCount );
	// 最后的路径
	compVector.emplace_back( nameVectorArratPtr[ nameVectorCount ] );
	foreachCount = actions.size( );
	foreachIndex = 0;
	compVectorArrayCount = compVector.size( );
	compArrayPtr = compVector.data( );
	auto actionArrayPtr = actions.data( );
	for( ; foreachIndex < foreachCount; ++foreachIndex ) {

		leftCount = actionArrayPtr[ foreachIndex ].first.size( );
		if( leftCount != compVectorArrayCount )
			continue;
		leftArray = actionArrayPtr[ foreachIndex ].first.data( );
		for( compVectorIndex = 0; compVectorIndex < compVectorArrayCount; ++compVectorIndex )
			if( leftArray[ compVectorIndex ] != compArrayPtr[ compVectorIndex ] )
				break;
		if( compVectorIndex == compVectorArrayCount )
			break;
	}
	if( foreachIndex != foreachCount ) {
		QString msg( "[ %1 ]节点菜单对象已经存在对应的 QAction" );
		printerDirector->error( msg.arg( appendUnity ) );
		return false;
	}
	auto action = new QAction( nameVectorArratPtr[ nameVectorCount ] );
	using QActionTriggered = void(QAction::*)( bool );
	QActionTriggered triggered = &QAction::triggered;
	if( connectCreateNodeAction( action, triggered, node_type_name, action_click_function ) == false )
		return false;
	actions.emplace_back( compVector, action );
	// 路径数量大于 0，则寻找挂靠
	compVectorArrayCount -= 1;
	if( compVectorArrayCount != 0 ) {
		foreachCount = subMenus.size( );
		foreachIndex = 0;
		subMenuArrayPtr = subMenus.data( );
		for( ; foreachIndex < foreachCount; ++foreachIndex ) {
			leftCount = subMenuArrayPtr[ foreachIndex ].first.size( );
			if( leftCount != compVectorArrayCount )
				continue;
			leftArray = subMenuArrayPtr[ foreachIndex ].first.data( );
			for( compVectorIndex = 0; compVectorIndex < compVectorArrayCount; ++compVectorIndex )
				if( leftArray[ compVectorIndex ] != compArrayPtr[ compVectorIndex ] )
					break;
			if( compVectorIndex == compVectorArrayCount )
				break;
		}
		if( foreachIndex == foreachCount ) {
			QString msg( "[ %1 ]节点菜单对象不存在挂靠的 QMenu" );
			printerDirector->error( msg.arg( appendUnity ) );
			return false;
		}
		subMenuArrayPtr[ foreachIndex ].second->addAction( action );
	}

	return true;
}
bool NodeStack::connectCreateNodeAction( QAction *connect_qaction_ptr, QActionTriggered connect_qaction_fun_ptr, const QString &node_type_name, const std::function< Node *( ) > &action_click_function ) {
	if( connect_qaction_ptr == nullptr || connect_qaction_fun_ptr == nullptr )
		return false;
	connect( connect_qaction_ptr, connect_qaction_fun_ptr, [this,action_click_function, node_type_name]( ) {
		auto node = action_click_function( );
		MainWindow *mainWindow = instancePtr->getMainWindow( );
		if( mainWindow == nullptr ) {
			auto errorMsg = tr( "无法匹配主窗口[Application::]getMainWindow( )" );
			printerDirector->error( errorMsg );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::MainWindow_Nullptr, errorMsg );
			delete node;
			return;
		}
		MainWidget *mainWidget = mainWindow->getMainWidget( );
		if( mainWidget == nullptr ) {
			auto errorMsg = tr( "无法匹配主渲染组件[MainWindow::getMainWidget()]" );
			printerDirector->error( errorMsg );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::MainWidget_Nullptr, errorMsg );
			delete node;
			return;
		}
		DrawNodeWidget *drawNodeWidget = mainWidget->getDrawNodeWidget( );
		if( drawNodeWidget == nullptr ) {
			auto errorMsg = tr( "无法匹配节点渲染组件 [MainWidget::getDrawNodeWidget()]" );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::DrawNodeWidget_Nullptr, errorMsg );
			delete node;
			return;
		}
		if( drawNodeWidget->addNode( node ) == false ) {
			auto errorMsg = tr( "节点添加失败[DrawNodeWidget::addNode( Node *add_node )]" );
			printerDirector->error( errorMsg );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::DrawNodeWidget_Add, errorMsg );
			delete node;
			return;
		}
		if( node->parent( ) != drawNodeWidget ) {
			auto errorMsg = tr( "节点父节点需要匹配到节点渲染组件[MainWidget::getDrawNodeWidget()]" );
			printerDirector->error( errorMsg );
			emit error_create_signal( node_type_name, NodeEnum::CreateType::Node_Parent, errorMsg );
			delete node;
			return;
		}
	} );
	return true;
}
NodeStack::NodeStack( QObject *parent ) : QObject( parent ), mainMenu( nullptr ) { }
void NodeStack::releaseMainMenu( ) {
	size_t count;
	size_t index;

	count = actions.size( );
	if( count ) {
		auto actionArrayPtr = actions.data( );
		for( index = 0; index < count; ++index )
			delete actionArrayPtr[ index ].second;
		actions.clear( );
	}

	count = subMenus.size( );
	if( count ) {
		auto subMenuArrayPtr = subMenus.data( );
		for( index = 0; index < count; ++index )
			delete subMenuArrayPtr[ index ].second;
		subMenus.clear( );
	}
	if( mainMenu )
		delete mainMenu;
	mainMenu = nullptr;
}
NodeStack::~NodeStack( ) {
	releaseMainMenu( );
}
Node * NodeStack::createNode( const QString &node_type_name ) {
	size_t count = nodeGenerate.size( );
	if( count == 0 )
		return nullptr;
	auto nodeGenerateArrayPtr = nodeGenerate.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeGenerateArrayPtr[ index ].first == node_type_name )
			return nodeGenerateArrayPtr[ index ].second( );
	return nullptr;
}
