#ifndef NORMALGENERATENODEMENU_H_H_HEAD__FILE__
#define NORMALGENERATENODEMENU_H_H_HEAD__FILE__

#include <QMenu>
#include <vector>

#include "../../tools/aliasType.h"

namespace path {
	class pathTree;
}
class Node;
class NodeStack;

class NormalGenerateNodeMenu : public QMenu {
	Q_OBJECT;
	friend class GenerateNodeMenuStack;
	friend class NodeDirector;
protected:
	std::vector< NormalGenerateNodeMenuType::TCreateUintyType > createVector;
	std::vector< QAction * > waitUpdateActionVector;
	size_t createCount;
	NormalGenerateNodeMenuType::TCreateUintyType *createArrayPtr;
	size_t createIndex;
protected:
	virtual void releaseObjResource( );
	virtual QMenu * fromNodeGenerateCreateMenu( NodeStack *node_stack_ptr );
	virtual bool fromPathTreeGenerateCreateaAction( const QString &top_name, path::pathTree *path_tree, QMenu *parent_menu, std::pair< QString, std::function< Node *( const QString & ) > > *node_create_stack_array_ptr, const size_t &node_create_stack_array_count );
	virtual void appendCareateItem( QAction *create_node_item, const QString &create_node_name, const NormalGenerateNodeMenuType::TCreateNodeFunction &create_node_function );
private Q_SLOTS:
	void actionSlots( QAction *action );
protected:
	NormalGenerateNodeMenu( );
	virtual bool initNormalGenerateNodeMenu( );
	/// @brief 根据节点名称创建节点
	/// @param node_name 节点名称
	/// @return 节点
	virtual Node * getCreateResultNode( const QString &node_name );
public:
	~NormalGenerateNodeMenu( ) override;
public Q_SLOTS:
	/// @brief 根据节点名称创建节点
	/// @param node_name 节点名称
	/// @return 节点
	virtual void createNode( const QString &node_name );
protected:
	virtual QMenu * formNodeStack( NodeStack *create_node_stack );
	template< typename TCNodeStackType >
		requires requires ( TCNodeStackType *c_node_stack, NodeStack *ptr ) {
			ptr = c_node_stack;
		}
	QMenu * appendCreateSubMenuAtNodeStack( ) {
		auto create = new TCNodeStackType;
		auto result = formNodeStack( create );
		delete create;
		return result;
	}
Q_SIGNALS:
	void create_node_signal( NormalGenerateNodeMenu *signal_obj_ptr, QAction *create_item, const QString &create_node_name, const NormalGenerateNodeMenuType::TCreateNodeFunction &create_node_function );
	void release_menu_signal( NormalGenerateNodeMenu *release_ptr );
};
#endif // NORMALGENERATENODEMENU_H_H_HEAD__FILE__
