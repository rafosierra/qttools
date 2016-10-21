#ifndef FILEPATHLISTFACTORY_H
#define FILEPATHLISTFACTORY_H

#include "qtpropertybrowser.h"
#include "filepathmanager.h"

class FilePathListEditor;

class FilePathListFactory: public QtAbstractEditorFactory<FilePathManager> {
Q_OBJECT
public:
	FilePathListFactory(QObject *parent = 0) :
			QtAbstractEditorFactory<FilePathManager>(parent) {
	}
	virtual ~FilePathListFactory();
protected:
	virtual void connectPropertyManager(FilePathManager *manager);
	virtual QWidget *createEditor(FilePathManager *manager,
			QtProperty *property, QWidget *parent);
	virtual void disconnectPropertyManager(FilePathManager *manager);
private slots:
	void slotPropertyChanged(QtProperty *property, const QString &value);
	void slotFilterChanged(QtProperty *property, const QString &filter);
	void slotSetValue();
	void slotEditorDestroyed(QObject *object);
private:
	QMap<QtProperty *, QList<FilePathListEditor *> > mEditorsMap;
	QMap<FilePathListEditor *, QtProperty *> mPropertiesMap;
};

#endif // FILEPATHLISTFACTORY_H
