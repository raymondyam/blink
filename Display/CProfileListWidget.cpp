#include "CProfileListWidget.h"

CProfileListWidget::CProfileListWidget(QWidget *parent)
: QTreeView(parent)
{
	QFont currentFont = static_cast <QWidget*> (this)->font(); 

	profileFontSize_ = currentFont.pointSize();
}

void CProfileListWidget::updateProfileListWidget()
{
	resizeColumnToContents(0);
	resizeColumnToContents(1);
	resizeColumnToContents(2);
    resizeColumnToContents(3); 
}

void CProfileListWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	emit profileItemTriggered(); 
    QTreeView::mouseDoubleClickEvent(event);
}

void CProfileListWidget::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Return) {
		emit profileItemTriggered(); 
	} else if ((event->key() == Qt::Key_Equal) && (event->modifiers() == Qt::ControlModifier)) { 
		profileZoomIn();
	} else if ((event->key() == Qt::Key_Minus) && (event->modifiers() == Qt::ControlModifier)) { 
		profileZoomOut();
	} 
	
	QTreeView::keyPressEvent(event);
}

void CProfileListWidget::updateProfileFont(const QFont& profileFont) 
{
	QFont currentFont = static_cast <QWidget*> (this)->font();

	if (currentFont != profileFont) { 
		static_cast <QWidget*> (this)->setFont(profileFont);
		profileFontSize_ = profileFont.pointSize(); 
		updateProfileListWidget();
	}
}

void CProfileListWidget::profileZoomIn()
{
	profileFontSize_++;
	QFont fnt = static_cast <QWidget*> (this)->font();;
	fnt.setPointSize(profileFontSize_); 
	static_cast <QWidget*> (this)->setFont(fnt);

	updateProfileListWidget();
}

void CProfileListWidget::profileZoomOut()
{
	if (profileFontSize_ > 1) {
		profileFontSize_--;
		QFont fnt = static_cast <QWidget*> (this)->font();
		fnt.setPointSize(profileFontSize_); 
		static_cast <QWidget*> (this)->setFont(fnt);

		updateProfileListWidget(); 
	}
}

void CProfileListWidget::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() == Qt::ControlModifier) {
        e->accept();
        if (e->delta() > 0) {
		   profileZoomIn();
		} else {
		   profileZoomOut();
		}
	}
	QTreeView::wheelEvent(e); 
}




