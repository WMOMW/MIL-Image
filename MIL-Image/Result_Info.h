#pragma once

#include <qstring.h>
#include <qstringlist.h>

class Result_Info {
public:
	Result_Info(QString = "", QStringList = QStringList());
	~Result_Info();

	QStringList get_outputClass();
	QString get_Image_path();

	void set_outputClass(QStringList);
	void set_Image_path(QString);

	void clear();

	Result_Info &operator=(const Result_Info);

private:
	QStringList outputClass;
	QString Image_path;
};