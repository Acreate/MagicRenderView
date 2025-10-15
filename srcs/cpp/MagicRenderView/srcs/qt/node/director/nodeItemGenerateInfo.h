#ifndef NODEITEMGENERATEINFO_H_H_HEAD__FILE__
#define NODEITEMGENERATEINFO_H_H_HEAD__FILE__
#pragma once

#include <QObject>

#include <alias/type_alias.h>

class I_Type;
class NodeItem;
class NodeItemGenerateInfo : public QObject {
	Q_OBJECT;
protected:
	QString dirName;
	QString nodeName;
	std_shared_ptr< I_Type > createTypeInstancePtr;
public:
	~NodeItemGenerateInfo( ) override ;
	NodeItemGenerateInfo( const QString &dir_name, const QString &node_name, const std_shared_ptr< I_Type > &create_type_instance_ptr )
		: dirName( dir_name ),
		nodeName( node_name ),
		createTypeInstancePtr( create_type_instance_ptr ) { }
	virtual const QString & getDirName( ) const { return dirName; }
	virtual const QString & getNodeName( ) const { return nodeName; }
	virtual const std_shared_ptr< I_Type > & getCreateTypeInstancePtr( ) const { return createTypeInstancePtr; }
	virtual bool isNodeType( const QString &dir_name, const QString &node_name ) {
		return dirName == dir_name && nodeName == node_name;
	}
	virtual NodeItem * createNodeItem( const QString &dir_name, const QString &node_name );
Q_SIGNALS:
	void releaseThis( NodeItemGenerateInfo *release_ptr );
};

#endif // NODEITEMGENERATEINFO_H_H_HEAD__FILE__
