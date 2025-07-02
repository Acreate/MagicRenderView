#ifndef NODELINKVECTOR_H_H_HEAD__FILE__
#define NODELINKVECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>
#include "./nodeLinkItem/nodeLinkItem.h"

class NodeLinkVector : public QObject {
	Q_OBJECT;
protected:
	std_shared_ptr< std_mutex > mutex;
	std_shared_ptr< std_vector< NodeLinkItem > > nodeLinkItems;
public:
	NodeLinkVector( );
	virtual std_vector< NodeLinkItem > toVector( ) const;
	virtual void resetVector( const std_vector< NodeLinkItem > &conver ) const;
	virtual bool hasItem( const NodeLinkItem &item ) const;
	virtual bool emplace_back( const NodeLinkItem &item );
	virtual bool append( const NodeLinkItem &item ) {
		return emplace_back( item );
	}
	virtual size_t size( ) const;
	virtual int linkHasUnity( const INodeComponent *unity ) const;
	virtual int linkHasUnity( const INodeWidget *unity ) const;
	virtual int linkHasInputUnity( const INodeComponent *input_unity ) const;
	virtual int linkHasInputUnity( const INodeWidget *input_unity ) const;
	virtual int linkHasOutputUnity( const INodeComponent *output_unity ) const;
	virtual int linkHasOutputUnity( const INodeWidget *output_unity ) const;
	virtual int linkRemoveFirstInputItem( const INodeComponent *input_unity );
	virtual int linkRemoveFirstOutputItem( const INodeComponent *output_unity );
	virtual int linkRemoveFirstInputItem( const INodeComponent *output_unity, const INodeComponent *input_unity );
	std_vector< std_pairt< INodeWidget *, INodeComponent * > > getOutLinkItems( const INodeComponent *input_unity );
	std_vector< std_pairt< INodeWidget *, INodeComponent * > > getInLinkItems( const INodeComponent *ouutput_unity );
	virtual void clear();
};

#endif // NODELINKVECTOR_H_H_HEAD__FILE__
