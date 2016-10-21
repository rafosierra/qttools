#ifndef FILEPATHLISTEDITOR_H
#define FILEPATHLISTEDITOR_H

#include <QPlainTextEdit>
#include <string>
#include <vector>
#include <iostream>

class FilePathListEditor: public QWidget {
Q_OBJECT
public:
	explicit FilePathListEditor(QWidget *parent = 0);

	void setFileList(const QString &files) {
		if (mTextEdit->toPlainText() != files) {
			mTextEdit->setPlainText(files);
		}
	}
	QString fileList() const {
		return mTextEdit->toPlainText();
	}
	void setFilter(const QString &filter) {
		mFilter = filter;
	}
	QString filter() const {
		return mFilter;
	}
signals:
	void filePathChanged();
protected:
	void focusInEvent(QFocusEvent *e);
	void focusOutEvent(QFocusEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
private slots:
	void buttonClicked();
private:
	QPlainTextEdit *mTextEdit;
	QString mFilter;
};

#endif // FILEPATHLISTEDITOR_H
