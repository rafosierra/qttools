#ifndef FILEPATHFACTORY_H
#define FILEPATHFACTORY_H

#include "qtpropertybrowser.h"
#include "filepathmanager.h"

class FilePathEditor;

class FilePathFactory: public QtAbstractEditorFactory<FilePathManager> {
Q_OBJECT
public:
	FilePathFactory(QObject *parent = 0) :
			QtAbstractEditorFactory<FilePathManager>(parent) {
	}
	virtual ~FilePathFactory();
protected:
	virtual void connectPropertyManager(FilePathManager *manager);
	virtual QWidget *createEditor(FilePathManager *manager, QtProperty *property, QWidget *parent);
	virtual void disconnectPropertyManager(FilePathManager *manager);
private slots:
	void slotPropertyChanged(QtProperty *property, const QString &value);
	void slotFilterChanged(QtProperty *property, const QString &filter);
	void slotSetValue(const QString &value);
	void slotEditorDestroyed(QObject *object);
private:
	QMap<QtProperty *, QList<FilePathEditor *> > mEditorsMap;
	QMap<FilePathEditor *, QtProperty *> mPropertiesMap;
};

#endif
