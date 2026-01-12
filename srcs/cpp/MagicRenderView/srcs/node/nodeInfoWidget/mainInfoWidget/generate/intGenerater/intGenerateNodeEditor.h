#ifndef INTGENERATENODEEDITOR_H_H_HEAD__FILE__
#define INTGENERATENODEEDITOR_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class IntGenerateTool;
class IntGenerateRenderWidget;
class IntGenerateRenderScrollArea;
class IntGenerateNode;
class QVBoxLayout;
class IntGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	IntGenerateRenderScrollArea *generateRenderScrollArea;
	IntGenerateTool *addGenerateTool;
	std::vector< int64_t > *bindGenerateVector;
	IntGenerateRenderWidget *generateRenderWidget;
protected:
	void releaseResource( ) override;
protected:
	virtual void addItem( IntGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant );
	virtual void requesPopItemMenu( QMenu *pop_menu );
public:
	IntGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< int64_t > * getBindGenerateVector( ) const { return bindGenerateVector; }
	virtual void setBindGenerateVector( std::vector< int64_t > *bind_generate_vector ) { bindGenerateVector = bind_generate_vector; }
	virtual void syncVarVector( );
	virtual bool updateGenerateItemInfo( );
	virtual void updateEditorNodeInfoLayout( );
protected:
	void resizeEvent( QResizeEvent * ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // INTGENERATENODEEDITOR_H_H_HEAD__FILE__
