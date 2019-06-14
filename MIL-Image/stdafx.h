#pragma once

#include <Windows.h>
#include <io.h>

#include <QtWidgets\QApplication>
#include <QtWidgets>
#include <qfile.h>
#include <qfiledialog.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qtextcursor.h>
#include <QtWidgets/QMainWindow>

#include <opencv2\opencv.hpp>

#include "MIL_Image.h"
#include "SVM_Trainer.h"
#include "namedImage.h"
#include "Result_Info.h"
#include "cvMatToQImage.h"
#include "ImageTools.h"
#include "TrainingTools.h"

extern namedImage Source_Image;
extern namedImage Destination_Image;
extern namedImage Data_Image;
extern QLinkedList<Result_Info> s_Info;
extern QLinkedList<Result_Info> f_Info;