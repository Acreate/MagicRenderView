#ifndef INTGENERATENODEEDITOR_H_H_HEAD__FILE__
#define INTGENERATENODEEDITOR_H_H_HEAD__FILE__
#pragma once
#include "../editorNodeInfoScrollArea.h"

class GenerateRenderWidget;
class GenerateRenderScrollArea;
class AddGenerateTool;
class GenerateItemWidget;
class QVBoxLayout;
class IntGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	GenerateRenderScrollArea *generateRenderScrollArea;
	AddGenerateTool *addGenerateTool;
	std::vector< GenerateItemWidget * > *intGenerateItemWidgetVector;
	std::vector< int64_t > *bindGenerateVector;
	std::vector< int64_t > *newCreactePtr;
	GenerateRenderWidget *generateRenderWidget;
protected:
	void releaseResource( ) override;
	virtual bool updateGenerateItemInfo( );
	virtual void updateLayout( );
protected:
	virtual void addItem( AddGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant, const QString &var_value );
public:
	IntGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< int64_t > * getBindGenerateVector( ) const { return bindGenerateVector; }
	virtual void setBindGenerateVector( std::vector< int64_t > *bind_generate_vector ) { bindGenerateVector = bind_generate_vector; }
	virtual std::vector< int64_t > * getNewCreactePtr( ) const { return newCreactePtr; }
	virtual void resetGenerateVarVector( );
protected:
	void resizeEvent( QResizeEvent * ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // INTGENERATENODEEDITOR_H_H_HEAD__FILE__
