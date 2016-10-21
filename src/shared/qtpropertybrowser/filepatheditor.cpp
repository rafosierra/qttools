#include "filepatheditor.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include <QFocusEvent>

FilePathEditor::FilePathEditor(QWidget *parent) :
	QWidget(parent)
{
	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	mLineEdit = new QLineEdit(this);
	mLineEdit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
	QToolButton *button = new QToolButton(this);
	button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
	button->setText(QLatin1String("..."));
	layout->addWidget(mLineEdit);
	layout->addWidget(button);
	setFocusProxy(mLineEdit);
	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_InputMethodEnabled);
	connect(mLineEdit, SIGNAL(textEdited(const QString &)), this, SIGNAL(filePathChanged(const QString &)));
	connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void FilePathEditor::buttonClicked() {
	QString filePath = QFileDialog::getOpenFileName(this, tr("Choose a file"), mLineEdit->text(), mFilter);
	if (filePath.isNull()) {
		return;
	}
	mLineEdit->setText(filePath);
	emit filePathChanged(filePath);
}

void FilePathEditor::focusInEvent(QFocusEvent *e) {
	mLineEdit->event(e);
	if (e->reason() == Qt::TabFocusReason || e->reason() == Qt::BacktabFocusReason) {
		mLineEdit->selectAll();
	}
	QWidget::focusInEvent(e);
}

void FilePathEditor::focusOutEvent(QFocusEvent *e) {
	mLineEdit->event(e);
	QWidget::focusOutEvent(e);
}

void FilePathEditor::keyPressEvent(QKeyEvent *e) {
	mLineEdit->event(e);
}

void FilePathEditor::keyReleaseEvent(QKeyEvent *e) {
	mLineEdit->event(e);
}
