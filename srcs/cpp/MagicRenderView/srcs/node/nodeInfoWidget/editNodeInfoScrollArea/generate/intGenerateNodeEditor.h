#ifndef INTGENERATENODEEDITOR_H_H_HEAD__FILE__
#define INTGENERATENODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class GenerateItemWidget;
class QVBoxLayout;
class IntGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	std::vector< GenerateItemWidget * > intGenerateItemWidgetVector;
	std::vector< int64_t > *bindGenerateVector;
protected:
	void releaseResource( ) override;
	virtual bool createJumpItem( NodeRefLinkInfo *node_ref_link_info );
	virtual bool updateGenerateItemInfo( );
public:
	IntGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< int64_t > * getBindGenerateVector( ) const { return bindGenerateVector; }
	virtual void setBindGenerateVector( std::vector< int64_t > *bind_generate_vector ) { bindGenerateVector = bind_generate_vector; }
};

#endif // INTGENERATENODEEDITOR_H_H_HEAD__FILE__
