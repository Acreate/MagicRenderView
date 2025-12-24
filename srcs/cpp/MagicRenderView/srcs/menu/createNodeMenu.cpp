#include "createNodeMenu.h"

#include "../node/stack/baseNodeStack/baseNodeStack.h"
#include "../tools/path.h"
void CreateNodeMenu::releaseObjResource( ) {

	if( createCount != 0 ) {
		createIndex = 0;
		for( ; createIndex < createCount; ++createIndex )
			delete createArrayPtr[ createIndex ].first;
		createVector.clear( );
		createCount = 0;
		createArrayPtr = nullptr;
	}
}
void CreateNodeMenu::actionSlots( QAction *action ) {
	if( createCount == 0 )
		return;
	for( createIndex = 0; createIndex < createCount; ++createIndex )
		if( action == createArrayPtr[ createIndex ].first ) {
			emit createNode( this, createArrayPtr[ createIndex ].first, createArrayPtr[ createIndex ].second.first, createArrayPtr[ createIndex ].second.second );
			break;
		}
}
CreateNodeMenu::CreateNodeMenu( ) : QMenu( ) {
	createCount = 0;
	createArrayPtr = nullptr;
	connect( this, &QMenu::triggered, this, &CreateNodeMenu::actionSlots );
}
bool CreateNodeMenu::initCreateNodeMenu( ) {
	releaseObjResource( );
	// 这里加入节点窗口创建函数
	NodeStack *createNodeStack = new BaseNodeStack( );
	if( createNodeStack->init( ) == false ) {
		delete createNodeStack;
		return false;
	}
	// 初始化菜单
	auto nodeGenerateCreateMenu = fromNodeGenerateCreateMenu( createNodeStack );
	if( addMenu( nodeGenerateCreateMenu ) == nullptr ) {
		delete createNodeStack;
		return false;
	}

	createCount = createVector.size( );
	createArrayPtr = createVector.data( );
	return createCount != 0;
}
void CreateNodeMenu::appendCareateItem( QAction *create_node_item, const QString &create_node_name, const TCreateNodeFunction &create_node_function ) {
	TCreateUintyType unity = std::pair( create_node_item, TCreateNodeInfo( create_node_name, create_node_function ) );
	createVector.emplace_back( unity );
}
void CreateNodeMenu::appendCareateItem( const QString &create_item_name, const QString &create_node_name, const TCreateNodeFunction &create_node_function ) {
	appendCareateItem( addAction( create_item_name ), create_node_name, create_node_function );
}

QMenu * CreateNodeMenu::fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr ) {
	auto nodeStackName = node_stack_ptr->objectName( );
	size_t count = node_stack_ptr->nodeGenerate.size( );
	auto data = node_stack_ptr->nodeGenerate.data( );
	size_t index = 0;
	path::pathTree pathTree( nodeStackName );
	for( ; index < count; ++index )
		pathTree.appSubPath( data[ index ].first );
	if( pathTree.getSubPath( ).size( ) == 0 )
		return nullptr;
	nodeStackName = pathTree.getName( );
	QMenu *resultMenu = new QMenu( nodeStackName );
	fromPathTreeGenerateCreateaAction( &pathTree, resultMenu );
	return resultMenu;
}
bool CreateNodeMenu::fromPathTreeGenerateCreateaAction( path::pathTree *path_tree, QMenu *parent_menu ) {
	auto pathTreeSubPath = path_tree->getSubPath( );
	size_t subPathCount = pathTreeSubPath.size( );
	if( subPathCount == 0 )
		return false;

	auto pathTreeSubPathTree = pathTreeSubPath.data( );
	size_t subPathIndex = 0;
	QString name;
	QString absolutePathName;
	std::list< path::pathTree * > subPathTree;
	for( ; subPathIndex < subPathCount; ++subPathIndex )
		if( pathTreeSubPathTree[ subPathIndex ]->getSubPath( ).size( ) == 0 ) {
			name = pathTreeSubPathTree[ subPathIndex ]->getName( );
			pathTreeSubPathTree[ subPathIndex ]->getAbsolutePath( absolutePathName );
			appendCareateItem( parent_menu->addAction( name ), absolutePathName, nullptr );
		} else
			subPathTree.emplace_back( pathTreeSubPathTree[ subPathIndex ] );
	for( auto &forreachPathTree : subPathTree ) {
		name = forreachPathTree->getName( );
		auto topMenu = parent_menu->addMenu( name );
		if( fromPathTreeGenerateCreateaAction( forreachPathTree, topMenu ) == false )
			return false;
	}
	return true;
}
