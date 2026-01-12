#ifndef FLOATGENERATENODEEDITOR_H_H_HEAD__FILE__
#define FLOATGENERATENODEEDITOR_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class FloatGenerateRenderWidget;
class FloatGenerateTool;
class FloatGenerateRenderScrollArea;
class QVBoxLayout;
class FloatGenerateNodeEditor : public EditorNodeInfoScrollArea {
	Q_OBJECT;
protected:
	QWidget *mainWidget;
	FloatGenerateRenderScrollArea *generateRenderScrollArea;
	FloatGenerateTool *addGenerateTool;
	std::vector< double > *bindGenerateVector;
	FloatGenerateRenderWidget *generateRenderWidget;
protected:
	void releaseResource( ) override;
protected:
	virtual void addItem( FloatGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant );
	virtual void requesPopItemMenu( QMenu *pop_menu );
public:
	FloatGenerateNodeEditor( NodeInfoWidget *parent );
	bool initNode( Node *init_node ) override;
	virtual std::vector< double > * getBindGenerateVector( ) const { return bindGenerateVector; }
	virtual void setBindGenerateVector( std::vector< double > *bind_generate_vector ) { bindGenerateVector = bind_generate_vector; }
	virtual void syncVarVector( );
	virtual bool updateGenerateItemInfo( );
	virtual void updateEditorNodeInfoLayout( );
protected:
	void resizeEvent( QResizeEvent * ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // FLOATGENERATENODEEDITOR_H_H_HEAD__FILE__
