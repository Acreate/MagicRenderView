#include "./errorMsgWidget.h"

#include <QLabel>
#include <QVBoxLayout>

ErrorMsgWidget::ErrorMsgWidget( QWidget *parent, const QString &error_msg ) : IInfoWidget( parent, error_msg ) {
}

