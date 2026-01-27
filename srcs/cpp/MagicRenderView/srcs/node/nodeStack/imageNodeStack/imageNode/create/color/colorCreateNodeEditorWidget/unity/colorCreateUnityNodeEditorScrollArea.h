#ifndef COLORCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define COLORCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class ValidatorWidget;
class QVBoxLayout;
class ColorCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class ColorCreateUnityNodeEditorWidget;
protected:
	QColor currentVar;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	ValidatorWidget *currentEditorValidator;
	std::vector< ValidatorWidget * > lineFinishedEditorVector;
protected:
	ColorCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, QColor current_var );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
	~ColorCreateUnityNodeEditorScrollArea( ) override;
	virtual QColor getCurrentVar( ) const { return currentVar; }
	virtual void setCurrentVar( QColor current_var );

Q_SIGNALS:
	void editingFinished_Signal( QColor var );
};

#endif // COLORCREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
