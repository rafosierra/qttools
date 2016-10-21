#include "filepathlistfactory.h"
#include "filepathlisteditor.h"

FilePathListFactory::~FilePathListFactory() {
	QList<FilePathListEditor *> editors = mPropertiesMap.keys();
	QListIterator<FilePathListEditor *> it(editors);
	while (it.hasNext()) {
		delete it.next();
	}
}

void FilePathListFactory::connectPropertyManager(FilePathManager *manager) {
	connect(manager, SIGNAL(valueChanged(QtProperty *, const QString &)), this, SLOT(slotPropertyChanged(QtProperty *, const QString &)));
	connect(manager, SIGNAL(filterChanged(QtProperty *, const QString &)), this, SLOT(slotFilterChanged(QtProperty *, const QString &)));
}

QWidget *FilePathListFactory::createEditor(FilePathManager *manager, QtProperty *property, QWidget *parent) {
	FilePathListEditor *editor = new FilePathListEditor(parent);
	editor->setFileList(manager->value(property));
	editor->setFilter(manager->filter(property));
	mEditorsMap[property].append(editor);
	mPropertiesMap[editor] = property;

	connect(editor, SIGNAL(filePathChanged()), this, SLOT(slotSetValue()));
	connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
	return editor;
}

void FilePathListFactory::disconnectPropertyManager(FilePathManager *manager) {
	disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QString &)), this, SLOT(slotPropertyChanged(QtProperty *, const QString &)));
	disconnect(manager, SIGNAL(filterChanged(QtProperty *, const QString &)), this, SLOT(slotFilterChanged(QtProperty *, const QString &)));
}

void FilePathListFactory::slotPropertyChanged(QtProperty *property, const QString &value) {
	if (!mEditorsMap.contains(property)) {
		return;
	}

	QList<FilePathListEditor *> editors = mEditorsMap[property];
	QListIterator<FilePathListEditor *> itEditor(editors);
	while (itEditor.hasNext()) {
		itEditor.next()->setFileList(value);
	}
}

void FilePathListFactory::slotFilterChanged(QtProperty *property,
		const QString &filter) {
	if (!mEditorsMap.contains(property)) {
		return;
	}

	QList<FilePathListEditor *> editors = mEditorsMap[property];
	QListIterator<FilePathListEditor *> itEditor(editors);
	while (itEditor.hasNext()) {
		itEditor.next()->setFilter(filter);
	}
}

void FilePathListFactory::slotSetValue() {
	QObject *object = sender();
	QMap<FilePathListEditor *, QtProperty *>::ConstIterator itEditor = mPropertiesMap.constBegin();
	while (itEditor != mPropertiesMap.constEnd()) {
		if (itEditor.key() == object) {
			QtProperty *property = itEditor.value();
			FilePathListEditor * textEdit = itEditor.key();
			FilePathManager *manager = propertyManager(property);
			if (!manager)
				return;
			manager->setValue(property, textEdit->fileList());
			return;
		}
		itEditor++;
	}
}

void FilePathListFactory::slotEditorDestroyed(QObject *object) {
	QMap<FilePathListEditor *, QtProperty *>::ConstIterator itEditor = mPropertiesMap.constBegin();
	while (itEditor != mPropertiesMap.constEnd()) {
		if (itEditor.key() == object) {
			FilePathListEditor *editor = itEditor.key();
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
