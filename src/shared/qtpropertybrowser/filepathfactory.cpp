#include "filepathfactory.h"
#include "filepatheditor.h"

FilePathFactory::~FilePathFactory() {
	QList<FilePathEditor *> editors = mPropertiesMap.keys();
	QListIterator<FilePathEditor *> it(editors);
	while (it.hasNext()) {
		delete it.next();
	}
}

void FilePathFactory::connectPropertyManager(FilePathManager *manager) {
	connect(manager, SIGNAL(valueChanged(QtProperty *, const QString &)), this,
			SLOT(slotPropertyChanged(QtProperty *, const QString &)));
	connect(manager, SIGNAL(filterChanged(QtProperty *, const QString &)), this,
			SLOT(slotFilterChanged(QtProperty *, const QString &)));
}

QWidget *FilePathFactory::createEditor(FilePathManager *manager, QtProperty *property, QWidget *parent) {
	FilePathEditor *editor = new FilePathEditor(parent);
	editor->setFilePath(manager->value(property));
	editor->setFilter(manager->filter(property));
	mEditorsMap[property].append(editor);
	mPropertiesMap[editor] = property;

	connect(editor, SIGNAL(filePathChanged(const QString &)), this, SLOT(slotSetValue(const QString &)));
	connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
	return editor;
}

void FilePathFactory::disconnectPropertyManager(FilePathManager *manager) {
	disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QString &)), this, SLOT(slotPropertyChanged(QtProperty *, const QString &)));
	disconnect(manager, SIGNAL(filterChanged(QtProperty *, const QString &)), this, SLOT(slotFilterChanged(QtProperty *, const QString &)));
}

void FilePathFactory::slotPropertyChanged(QtProperty *property, const QString &value) {
	if (!mEditorsMap.contains(property)) {
		return;
	}

	QList<FilePathEditor *> editors = mEditorsMap[property];
	QListIterator<FilePathEditor *> itEditor(editors);
	while (itEditor.hasNext()) {
		itEditor.next()->setFilePath(value);
	}
}

void FilePathFactory::slotFilterChanged(QtProperty *property,
		const QString &filter) {
	if (!mEditorsMap.contains(property))
		return;

	QList<FilePathEditor *> editors = mEditorsMap[property];
	QListIterator<FilePathEditor *> itEditor(editors);
	while (itEditor.hasNext())
		itEditor.next()->setFilter(filter);
}

void FilePathFactory::slotSetValue(const QString &value) {
	QObject *object = sender();
	QMap<FilePathEditor *, QtProperty *>::ConstIterator itEditor = mPropertiesMap.constBegin();
	while (itEditor != mPropertiesMap.constEnd()) {
		if (itEditor.key() == object) {
			QtProperty *property = itEditor.value();
			FilePathManager *manager = propertyManager(property);
			if (!manager)
				return;
			manager->setValue(property, value);
			return;
		}
		itEditor++;
	}
}

void FilePathFactory::slotEditorDestroyed(QObject *object) {
	QMap<FilePathEditor *, QtProperty *>::ConstIterator itEditor = mPropertiesMap.constBegin();
	while (itEditor != mPropertiesMap.constEnd()) {
		if (itEditor.key() == object) {
			FilePathEditor *editor = itEditor.key();
			QtProperty *property = itEditor.value();
			mPropertiesMap.remove(editor);
			mEditorsMap[property].removeAll(editor);
			if (mEditorsMap[property].isEmpty())
				mEditorsMap.remove(property);
			return;
		}
		itEditor++;
	}
}

