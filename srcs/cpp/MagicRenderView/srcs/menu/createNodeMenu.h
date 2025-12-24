#ifndef CREATENODEMENU_H_H_HEAD__FILE__
#define CREATENODEMENU_H_H_HEAD__FILE__
#pragma once
#include <QMenu>
#include <vector>

namespace path {
	class pathTree;
}
class Node;
class NodeStack;
class CreateNodeMenu : public QMenu {
	Q_OBJECT;
public:
	using TCreateNodeFunction = std::function< Node *( const QString & ) >;
	using TCreateNodeInfo = std::pair< QString, TCreateNodeFunction >;
	using TCreateUintyType = std::pair< QAction *, TCreateNodeInfo >;
protected:
	std::vector< TCreateUintyType > createVector;
	std::vector< QAction * > waitUpdateActionVector;
	size_t createCount;
	TCreateUintyType *createArrayPtr;
	size_t createIndex;
protected:
	virtual void releaseObjResource( );
	virtual QMenu * fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr );
	virtual bool fromPathTreeGenerateCreateaAction( const QString &top_name, path::pathTree *path_tree, QMenu *parent_menu, std::pair< QString, std::function< Node *( const QString & ) > > *node_create_stack_array_ptr, const size_t &node_create_stack_array_count );
	virtual void appendCareateItem( QAction *create_node_item, const QString &create_node_name, const TCreateNodeFunction &create_node_function );
private Q_SLOTS:
	void actionSlots( QAction *action );
public:
	CreateNodeMenu( );
	virtual bool initCreateNodeMenu( );
	virtual void appendCareateItem( const QString &create_item_name, const QString &create_node_name, const TCreateNodeFunction &create_node_function );
	virtual QMenu * formNodeStack( NodeStack *create_node_stack );
	template< typename TCNodeStackType >
		requires requires ( TCNodeStackType *c_node_stack, NodeStack *ptr ) {
			ptr = c_node_stack;
		}
	QMenu * appendCreateSubMenuAtNodeStack( ) {
		return formNodeStack( new TCNodeStackType );
	}
Q_SIGNALS:
	void createNode( CreateNodeMenu *signal_obj_ptr, QAction *create_item, const QString &create_node_name, const TCreateNodeFunction &create_node_function );
};

#endif // CREATENODEMENU_H_H_HEAD__FILE__
