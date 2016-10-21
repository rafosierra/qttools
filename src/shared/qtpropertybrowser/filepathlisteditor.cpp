#include "filepathlisteditor.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include <QFocusEvent>

FilePathListEditor::FilePathListEditor(QWidget *parent) :
		QWidget(parent)
{
	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	mTextEdit = new QPlainTextEdit(this);
	mTextEdit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
	QToolButton *button = new QToolButton(this);
	button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
	button->setText(QLatin1String("..."));
	layout->addWidget(mTextEdit);
	layout->addWidget(button);
	setFocusProxy(mTextEdit);
	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_InputMethodEnabled);
	connect(mTextEdit, SIGNAL(textChanged()), this, SIGNAL(filePathChanged()));
	connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void FilePathListEditor::buttonClicked() {
	QString filePath = QFileDialog::getOpenFileName(this, tr("Choose a file"), QString(), mFilter);
	if (filePath.isNull()) {
		return;
	}
	mTextEdit->appendPlainText(filePath);
	emit filePathChanged();
}

void FilePathListEditor::focusInEvent(QFocusEvent *e) {
	if (e->reason() == Qt::TabFocusReason || e->reason() == Qt::BacktabFocusReason) {
		mTextEdit->selectAll();
	}
	QWidget::focusInEvent(e);
}

void FilePathListEditor::focusOutEvent(QFocusEvent *e) {

	QWidget::focusOutEvent(e);
}

void FilePathListEditor::keyPressEvent(QKeyEvent *e) {

}

void FilePathListEditor::keyReleaseEvent(QKeyEvent *e) {

}
