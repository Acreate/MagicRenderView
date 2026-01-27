#ifndef IMAGECREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define IMAGECREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class ValidatorWidget;
class QVBoxLayout;
class ImageCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class ImageCreateUnityNodeEditorWidget;
protected:
	QImage currentVar;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	ValidatorWidget *currentEditorValidator;
	std::vector< ValidatorWidget * > lineFinishedEditorVector;
protected:
	ImageCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, const QImage &current_var );
	void releaseResource( ) override;
public:
	bool initNode( Node *init_node ) override;
	~ImageCreateUnityNodeEditorScrollArea( ) override;
	virtual const QImage & getCurrentVar( ) const { return currentVar; }
	virtual void setCurrentVar( const QImage &current_var );
Q_SIGNALS:
	void editingFinished_Signal( const QImage &var );
};

#endif // IMAGECREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
