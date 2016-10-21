#ifndef FILEPATHEDITOR_H
#define FILEPATHEDITOR_H

#include <QLineEdit>

class FilePathEditor: public QWidget {
Q_OBJECT
public:
	FilePathEditor(QWidget *parent = 0);
	void setFilePath(const QString &filePath) {
		if (mLineEdit->text() != filePath) {
			mLineEdit->setText(filePath);
		}
	}
	QString filePath() const {
		return mLineEdit->text();
	}
	void setFilter(const QString &filter) {
		mFilter = filter;
	}
	QString filter() const {
		return mFilter;
	}
signals:
	void filePathChanged(const QString &filePath);
protected:
	void focusInEvent(QFocusEvent *e);
	void focusOutEvent(QFocusEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
private slots:
	void buttonClicked();
private:
	QLineEdit *mLineEdit;
	QString mFilter;
};

#endif
