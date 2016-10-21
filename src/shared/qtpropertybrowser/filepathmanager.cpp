#include "filepathmanager.h"

QString FilePathManager::value(const QtProperty *property) const {
	if (!mValuesMap.contains(property)) {
		return QString();
	}
	return mValuesMap[property].value;
}

QString FilePathManager::filter(const QtProperty *property) const {
	if (!mValuesMap.contains(property)) {
		return QString();
	}
	return mValuesMap[property].filter;
}

void FilePathManager::setValue(QtProperty *property, const QString &val) {
	if (!mValuesMap.contains(property)) {
		return;
	}
	Data data = mValuesMap[property];
	if (data.value == val) {
		return;
	}
	data.value = val;
	mValuesMap[property] = data;
	emit propertyChanged(property);
	emit valueChanged(property, data.value);
}

void FilePathManager::setFilter(QtProperty *property, const QString &fil) {
	if (!mValuesMap.contains(property)) {
		return;
	}
	Data data = mValuesMap[property];
	if (data.filter == fil) {
		return;
	}
	data.filter = fil;
	mValuesMap[property] = data;
	emit filterChanged(property, data.filter);
}
