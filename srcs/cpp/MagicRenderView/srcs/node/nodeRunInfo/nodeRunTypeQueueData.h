#ifndef NODERUNTYPEQUEUEDATA_H_H_HEAD__FILE__
#define NODERUNTYPEQUEUEDATA_H_H_HEAD__FILE__
#include <QObject>
namespace NodeEnum {
	enum class NodeType;
}
class Node;
class NodeRunTypeQueueData : public QObject {
	Q_OBJECT;
private:
	std::vector< Node * > nodeQueue;
	NodeEnum::NodeType type;
protected:
	virtual const std::vector< Node * > & getNodeQueue( ) const;
	virtual void setNodeQueue( const std::vector< Node * > &node_queue );
	virtual NodeEnum::NodeType getType( ) const;
	virtual void setType( NodeEnum::NodeType type );
	virtual bool appendNode( Node *append_node_ptr );
	virtual bool removeNode( const Node *remove_node_ptr );
public:
	NodeRunTypeQueueData( );
};

#endif // NODERUNTYPEQUEUEDATA_H_H_HEAD__FILE__
