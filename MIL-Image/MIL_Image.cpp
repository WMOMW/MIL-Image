#include "stdafx.h"

namedImage Source_Image;
namedImage Destination_Image;
namedImage Data_Image;
QLinkedList<Result_Info> s_Info;
QLinkedList<Result_Info> f_Info;

MIL_Image::MIL_Image(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	SVM_path = ".\\SVMs\\";
	file_path = ".\\";
	s = false;
	f = false;
	Success_W = new ImageReasult_Widget(this);
	Failed_W = new ImageReasult_Widget(this);

	connect(ui.action_OpenImage, SIGNAL(triggered()), this, SLOT(open_Images()));
	connect(ui.action_LoadSVMs, SIGNAL(triggered()), this, SLOT(load_SVMs()));
	connect(ui.action_SaveImage, SIGNAL(triggered()), this, SLOT(save_Image()));
	connect(ui.action_SaveImageAs, SIGNAL(triggered()), this, SLOT(save_Image_as()));
	connect(ui.action_removeallImages, SIGNAL(triggered()), this, SLOT(remove_all_Images()));
	connect(ui.action_Exit, SIGNAL(triggered()), this, SLOT(close()));

	connect(ui.action_AnalyzeImage, SIGNAL(triggered()), this, SLOT(get_ImageInfo()));
	connect(ui.action_GetGrayScale, SIGNAL(triggered()), this, SLOT(get_GrayscaleImage()));
	connect(ui.action_BinaryImage, SIGNAL(triggered()), this, SLOT(get_BinaryImage()));
	connect(ui.action_GetFeature, SIGNAL(triggered()), this, SLOT(get_FeatureImage()));
	connect(ui.action_createClassifier, SIGNAL(triggered()), this, SLOT(Create_Classifier()));
	connect(ui.action_RunSVM, SIGNAL(triggered()), this, SLOT(Class_test()));

	connect(ui.action_ImageView, SIGNAL(triggered()), this, SLOT(show_ImageView()));
	connect(ui.action_SVMView, SIGNAL(triggered()), this, SLOT(show_SVMView()));
	connect(ui.action_outputView, SIGNAL(triggered()), this, SLOT(show_outputView()));
	connect(ui.action_outImageView, SIGNAL(triggered()), this, SLOT(show_outImageView()));
	connect(ui.action_about, SIGNAL(triggered()), this, SLOT(show_actionAbout()));
	connect(ui.to_Right, SIGNAL(clicked()), this, SLOT(Source_to_Destination()));
	connect(ui.to_Left, SIGNAL(clicked()), this, SLOT(Destination_to_Source()));

	connect(ui.tableWidget_Images, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(open_Image_from_table(QTableWidgetItem*)));
	connect(ui.tableWidget_Images, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_ImageView_menu(QPoint)));
	connect(ui.action_ImageList_open, SIGNAL(triggered()), this, SLOT(open_Image_from_table_byAction()));
	connect(ui.action_ImageList_remove, SIGNAL(triggered()), this, SLOT(remove_Image_from_table_byAction()));
	connect(ui.action_ImageList_copyPath, SIGNAL(triggered()), this, SLOT(copy_ImagePath_from_table_byAction()));
	connect(ui.tableWidget_SVMs, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_SVMs_menu(QPoint)));
	connect(ui.action_SVMs_remove, SIGNAL(triggered()), this, SLOT(remove_SVM_from_table_byAction()));
	connect(ui.action_SVMs_removeAll, SIGNAL(triggered()), this, SLOT(remove_allSVM_from_table_byAction()));
	connect(ui.action_SVMs_copyPath, SIGNAL(triggered()), this, SLOT(copy_SVMPath_from_table_byAction()));
	connect(ui.tableWidget_SVMs, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(select_SVM(QTableWidgetItem*)));

	connect(ui.dock_outputText, &QDockWidget::topLevelChanged, this, [=](bool is_float) {
		resizeDock(ui.dock_outputText, is_float);
	});
	connect(ui.dock_SVMList, &QDockWidget::topLevelChanged, this, [=](bool is_float) {
		resizeDock(ui.dock_SVMList, is_float);
	});
	connect(ui.dock_ImageList, &QDockWidget::topLevelChanged, this, [=](bool is_float) {
		resizeDock(ui.dock_ImageList, is_float);
	});
	connect(ui.dock_outputImage, &QDockWidget::topLevelChanged, this, [=](bool is_float) {
		resizeDock(ui.dock_outputImage, is_float);
	});

	connect(ui.to_Left, SIGNAL(clicked()), this, SLOT(ttt()));
}

void MIL_Image::output_Text(QString message, int state, QString about) {
	if (!message.isEmpty())
	{
		ui.text_output->insertPlainText(message);
	}
	switch (state)
	{
	case 0:
		ui.text_output->insertPlainText(QString::fromLocal8Bit("\t【失败】"));
		break;
	case 1:
		ui.text_output->insertPlainText(QString::fromLocal8Bit("\t【完成】"));
		break;
	}
	if (!about.isEmpty())
	{
		ui.text_output->insertPlainText("\n--------------------\n" + about + "-------------------|\n");
	}
	ui.text_output->insertPlainText("\n");
	ui.text_output->repaint();
	ui.text_output->moveCursor(QTextCursor::MoveOperation::End);	//将滚动条置底
}

bool MIL_Image::update_Source() {
	if (!Source_Image.isEmpty())
	{
		Source_QImage = cvMatToQImage(Source_Image.get_image());
		ui.Image_1->setPixmap((QPixmap(QPixmap::fromImage(Source_QImage)).scaled(ui.Image_1->size(), Qt::KeepAspectRatio)));
		return true;
	}
	return false;
}

bool MIL_Image::update_Destination() {
	if (!Destination_Image.isEmpty())
	{
		Destination_QImage = cvMatToQImage(Destination_Image.get_image());
		ui.Image_2->setPixmap((QPixmap(QPixmap::fromImage(Destination_QImage)).scaled(ui.Image_2->size(), Qt::KeepAspectRatio)));
		return true;
	}
	return false;
}

bool MIL_Image::update_DataImage() {
	if (!Data_Image.isEmpty())
	{
		Data_QImage = cvMatToQImage(Data_Image.get_image());
		ui.Image_dockImage->setPixmap((QPixmap(QPixmap::fromImage(Data_QImage)).scaled(ui.Image_dockImage->size(), Qt::KeepAspectRatio)));
		return true;
	}
	return false;
}

void MIL_Image::resizeDock(QDockWidget *dock, bool is_float) {
	if (is_float)
	{
		int x = dock->height(), y = dock->width();
		if (x < y)
		{
			if (y > (x * 2))
			{
				x = x < 200 ? 200 : x;
				dock->resize(x * 2, x);
			}
		}
		else
		{
			if (x > (y * 2))
			{
				dock->resize(y, y * 2);
			}
		}
	}
}

void MIL_Image::ttt() {
	/*QLinkedList<Result_Info> info_1, info_2;
	Result_Info ss, tt;
	ss.set_Image_path(QString::fromLocal8Bit("F:/毕业设计/Demo/Demo1/Demo1/0 - 副本.jpg"));
	ss.set_outputClass({ "1","2" });
	info_1.push_back(ss);
	tt.set_Image_path(QString::fromLocal8Bit("F:/毕业设计/Demo/Demo1/Demo1/1 - 副本.jpg"));
	tt.set_outputClass({ "4","5" });
	ss.set_outputClass({ "y","i" });
	info_1.push_back(ss);
	ss.set_outputClass({ "ttttt","5464574" });
	info_1.push_back(ss);
	info_2.push_back(tt);
	if (s)
	{
		s = false;
		Success_W->setInfo(info_1);
		Failed_W->setInfo(info_2);
	}
	else
	{
		s = true;
		Success_W->setInfo(info_2);
		Failed_W->setInfo(info_1);
	}
	Success_W->move(100, 100);
	Success_W->show();
	Failed_W->move(300, 100);
	Failed_W->show();
	Success_W->setFocus();*/
	/*SVM_Trainer *a = new SVM_Trainer(this);
	a->show();*/
	//ImageTools_Interface::get_Features(Source_Image.get_image(), Destination_Image.get_image(), QString());
	/*if (QFile::exists("4.txt"))
	{
		FILE *f;
		f = fopen("4.txt", "ab+");
		long f_length = filelength(fileno(f));
		LockFile(f, 0, 0, 0, 0);
		system("pause");
		UnlockFile(f, 0, 0, 0, 0);
		fclose(f);
	}*/
}

void MIL_Image::show_Resualt(bool flag, QString Title, QString RealClass) {
	if (flag)
	{
		Success_W->setTitle(Title);
		Success_W->setInfo(s_Info);
		Success_W->setRealClass(RealClass);
		if (!s)
		{
			Success_W->move(100, 100);
			s = true;
		}
		Success_W->show();
		Success_W->setFocus();
	}
	else
	{
		Failed_W->setTitle(Title);
		Failed_W->setInfo(f_Info);
		Failed_W->setRealClass(RealClass);
		if (!f)
		{
			Failed_W->move(550, 100);
			f = true;
		}
		Failed_W->show();
		Failed_W->setFocus();
	}
}

void MIL_Image::begin_Algorithm() {
	this->setEnabled(false);
}

void MIL_Image::end_Algorithm(QString message, int state, QString about) {
	update_Destination();
	update_DataImage();
	output_Text(message, state, about);
	this->setEnabled(true);
}

void MIL_Image::open_Images() {
	QStringList files_names = QFileDialog::getOpenFileNames(
		this,
		QString::fromLocal8Bit("预加载图片"),
		file_path,
		"Images (*.png , *.jpg)");
	if (!files_names.isEmpty())
	{
		file_path = *files_names.begin();
		int rows = ui.tableWidget_Images->rowCount();
		int rows_temp = rows;
		int successful = 0, failed = 0;
		for (auto p : files_names)
		{
			QFileInfo f(p);
			if (f.suffix().compare("jpg", Qt::CaseInsensitive) && f.suffix().compare("png", Qt::CaseInsensitive))
			{
				continue;
			}
			if (opened_Images.find(p) == opened_Images.end())
			{
				opened_Images.insert(p);
				ui.tableWidget_Images->insertRow(rows);
				ui.tableWidget_Images->setItem(rows, 0, new QTableWidgetItem(f.fileName()));
				ui.tableWidget_Images->setItem(rows, 1, new QTableWidgetItem(p));
				++rows;
				++successful;
			}
			else
			{
				++failed;
				output_Text(QString::fromLocal8Bit("预加载  ") + p, 0, QString::fromLocal8Bit("已经被导入\n"));
			}
		}
		Source_Image.open_Image(file_path);
		if (update_Source())
		{
			output_Text(QString::fromLocal8Bit("打开  ") + file_path, 1);
		}
		else
		{
			output_Text(QString::fromLocal8Bit("打开  ") + file_path, 0);
		}
		ui.tableWidget_Images->selectRow(rows_temp);
		show_ImageView();
		output_Text(QString::fromLocal8Bit("预加载图片   (") + QString::number(successful, 10) + '/' + QString::number(successful + failed, 10) + ')', 1);
	}
}

void MIL_Image::load_SVMs() {
	QStringList SVMs_names = QFileDialog::getOpenFileNames(
		this,
		QString::fromLocal8Bit("预加载SVM"),
		SVM_path,
		QString::fromLocal8Bit("XML文件 (*.xml)"));
	if (!SVMs_names.isEmpty())
	{
		SVM_path = *SVMs_names.begin();
		int rows = ui.tableWidget_SVMs->rowCount();
		int rows_temp = rows;
		int successful = 0, failed = 0;
		for (auto p : SVMs_names)
		{
			QFileInfo f(p);
			if (f.suffix().compare("xml", Qt::CaseInsensitive))
			{
				++failed;
				output_Text(QString::fromLocal8Bit("预加载  ") + p, 0, QString::fromLocal8Bit("文件类型不匹配\n"));
				continue;
			}
			if (opened_SVMs.find(p) == opened_SVMs.end())
			{
				QTableWidgetItem *item = new QTableWidgetItem(f.fileName());
				item->setCheckState(Qt::Unchecked);
				opened_SVMs.insert(p);
				ui.tableWidget_SVMs->insertRow(rows);
				ui.tableWidget_SVMs->setItem(rows, 0, item);
				ui.tableWidget_SVMs->setItem(rows, 1, new QTableWidgetItem(p));
				++rows;
				++successful;
			}
			else
			{
				++failed;
				output_Text(QString::fromLocal8Bit("预加载  ") + p, 0, QString::fromLocal8Bit("已经被导入\n"));
			}
		}
		ui.tableWidget_SVMs->selectRow(rows_temp);
		show_SVMView();
		output_Text(QString::fromLocal8Bit("预加载SVM   (") + QString::number(successful, 10) + '/' + QString::number(successful + failed, 10) + ')', 1);
	}
}

void MIL_Image::save_Image() {
	if (Destination_Image.isEmpty())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("要保存的图像(目的图像)为空"), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	QString path = Source_Image.get_imagePath();
	if (path.isEmpty())
	{
		output_Text(QString::fromLocal8Bit("保存图像"), 0, QString::fromLocal8Bit("源图像路径为空\n"));
		return;
	}
	QFileInfo f(path);
	if (f.suffix().compare("jpg", Qt::CaseInsensitive) && f.suffix().compare("png", Qt::CaseInsensitive))
	{
		output_Text(QString::fromLocal8Bit("保存图像"), 0, QString::fromLocal8Bit("文件不能为*.jpg或*.png之外的格式\n"));
		return;
	}
	if (cv::imwrite(path.toLocal8Bit().toStdString(), Destination_Image.get_image()))
	{
		ui.Image_1->setPixmap((QPixmap(QPixmap::fromImage(Destination_QImage)).scaled(ui.Image_1->size(), Qt::KeepAspectRatio)));
		Source_Image.set_imageClone(Destination_Image.get_image());
		output_Text(QString::fromLocal8Bit("保存至  ") + path, 1);
	}
	else
	{
		output_Text(QString::fromLocal8Bit("保存至  ") + path, 0);
	}
}

void MIL_Image::save_Image_as() {
	if (Destination_Image.isEmpty())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("要保存的图像(目的图像)为空"), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	QString path = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("另存为"), QFileInfo(Source_Image.get_imagePath()).baseName(), "JPG Images (*.jpg);;PNG Images (*.png)");
	if (path.isEmpty())
	{
		return;
	}
	QFileInfo f(path);
	if (f.suffix().compare("jpg", Qt::CaseInsensitive) && f.suffix().compare("png", Qt::CaseInsensitive))
	{
		output_Text(QString::fromLocal8Bit("另存为图像"), 0, QString::fromLocal8Bit("文件不能为*.jpg或*.png之外的格式\n"));
		return;
	}
	else
	{
		if (cv::imwrite(path.toLocal8Bit().toStdString(), Destination_Image.get_image()))
		{
			output_Text(QString::fromLocal8Bit("保存至  ") + path, 1);
		}
		else
		{
			output_Text(QString::fromLocal8Bit("保存至  ") + path, 0);
		}
	}
}

void MIL_Image::remove_all_Images() {
	opened_Images.clear();
	Source_Image.eraseImage();
	Destination_Image.eraseImage();
	Data_Image.eraseImage();
	ui.Image_1->clear();
	ui.Image_2->clear();
	ui.Image_dockImage->clear();

	ui.tableWidget_Images->clearContents();
	ui.tableWidget_Images->setRowCount(0);

	output_Text(QString::fromLocal8Bit("移除全部图像"), 1);
}

void MIL_Image::get_ImageInfo() {
	if (Source_Image.isEmpty())
	{
		output_Text(QString::fromLocal8Bit("获取图像信息"), 0, QString::fromLocal8Bit("源图为空\n"));
		return;
	}
	output_Text(QString::fromLocal8Bit("正在获取图像信息......"));
	begin_Algorithm();
	ImageInfo_Thread *thread = new ImageInfo_Thread(this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(end_Algorithm(QString, int, QString)), this, SLOT(end_Algorithm(QString, int, QString)));
	connect(thread, SIGNAL(show_outImageView()), this, SLOT(show_outImageView()));
	thread->start();
}

void MIL_Image::get_GrayscaleImage() {
	if (Source_Image.isEmpty())
	{
		output_Text(QString::fromLocal8Bit("计算灰度图"), 0, QString::fromLocal8Bit("源图为空\n"));
		return;
	}
	output_Text(QString::fromLocal8Bit("正在计算灰度图......"));
	begin_Algorithm();
	GrayscaleImage_Thread *thread = new GrayscaleImage_Thread(this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(end_Algorithm(QString, int, QString)), this, SLOT(end_Algorithm(QString, int, QString)));
	thread->start();
}

void MIL_Image::get_FeatureImage() {
	if (Source_Image.isEmpty())
	{
		output_Text(QString::fromLocal8Bit("获取特征图"), 0, QString::fromLocal8Bit("源图为空\n"));
		return;
	}
	output_Text(QString::fromLocal8Bit("正在计算特征图......"));
	begin_Algorithm();
	FeatureImage_Thread *thread = new FeatureImage_Thread(this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(end_Algorithm(QString, int, QString)), this, SLOT(end_Algorithm(QString, int, QString)));
	thread->start();
}

void MIL_Image::get_BinaryImage() {
	if (Source_Image.isEmpty())
	{
		output_Text(QString::fromLocal8Bit("计算二值化图像"), 0, QString::fromLocal8Bit("源图为空\n"));
		return;
	}
	output_Text(QString::fromLocal8Bit("正在计算二值化图像......"));
	begin_Algorithm();
	BinaryImage_Thread *thread = new BinaryImage_Thread(this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(end_Algorithm(QString, int, QString)), this, SLOT(end_Algorithm(QString, int, QString)));
	thread->start();
}

void MIL_Image::Create_Classifier() {
	SVM_Trainer *a = new SVM_Trainer(this);
	a->setAttribute(Qt::WA_DeleteOnClose);
	connect(a, SIGNAL(output_to_main(QString, int, QString)), this, SLOT(output_Text(QString, int, QString)));
	a->show();
}

void MIL_Image::Class_test() {
	int Img_rows = ui.tableWidget_Images->rowCount();
	int SVM_rows = ui.tableWidget_SVMs->rowCount();
	QStringList Images_path, SVMs_path;
	if (Img_rows == 0 || SVM_rows == 0)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("预加载图片或SVM为空"), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	for (int i = 0; i < Img_rows; ++i)
	{
		QString path = ui.tableWidget_Images->item(i, 1)->text();
		if (cv::imread(path.toLocal8Bit().toStdString(), 1).empty())
		{
			if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), path + QString::fromLocal8Bit("为空") + QString::fromLocal8Bit("\n移除该无效项并继续执行?"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
			{
				remove_Image_from_table(ui.tableWidget_Images->item(i, 0));
				--i;
				--Img_rows;
				continue;
			}
			else
			{
				return;
			}
		}
		Images_path.push_back(path);
	}
	if (Img_rows == 0 || SVM_rows == 0)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("预加载图片或SVM为空"), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	for (int i = 0; i < SVM_rows; ++i)
	{
		if (ui.tableWidget_SVMs->item(i, 0)->checkState() == Qt::CheckState::Unchecked)
		{
			continue;
		}
		QString path = ui.tableWidget_SVMs->item(i, 1)->text();
		if (!QFile::exists(path))
		{
			if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), path + QString::fromLocal8Bit("为空") + QString::fromLocal8Bit("\n移除该无效项并继续执行?"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
			{
				remove_SVM_from_table(ui.tableWidget_SVMs->item(i, 0));
				--i;
				--SVM_rows;
				continue;
			}
			else
			{
				return;
			}
		}
		SVMs_path.push_back(path);
	}
	QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("即将开始算法，其间会跳过无法打开的文件，但算法不会终止。"), QMessageBox::Ok, QMessageBox::Ok);
	output_Text(QString::fromLocal8Bit("正在分类......"));
	begin_Algorithm();

	ClassTest_Thread *thread = new ClassTest_Thread(Images_path, SVMs_path, this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(end_Algorithm(QString, int, QString)), this, SLOT(end_Algorithm(QString, int, QString)));
	connect(thread, SIGNAL(output_to_main(QString, int, QString)), this, SLOT(output_Text(QString, int, QString)));
	connect(thread, SIGNAL(show_Resualt(bool, QString, QString)), this, SLOT(show_Resualt(bool, QString, QString)));
	thread->start();
}

void MIL_Image::show_ImageView() {
	ui.dock_ImageList->setVisible(true);
	ui.dock_ImageList->activateWindow();
	ui.dock_ImageList->raise();
}

void MIL_Image::show_SVMView() {
	ui.dock_SVMList->setVisible(true);
	ui.dock_SVMList->activateWindow();
	ui.dock_SVMList->raise();
}

void MIL_Image::show_outputView() {
	ui.dock_outputText->setVisible(true);
	ui.dock_outputText->activateWindow();
	ui.dock_outputText->raise();
}

void MIL_Image::show_outImageView() {
	ui.dock_outputImage->setVisible(true);
	ui.dock_outputImage->activateWindow();
	ui.dock_outputImage->raise();
}

void MIL_Image::show_actionAbout() {
	QMessageBox::information(this, QString::fromLocal8Bit("about"), QString::fromLocal8Bit("基于特征空间变换的多示例图像分类系统\n\t\t20152104  刘晓东"));
}

void MIL_Image::Source_to_Destination() {
	if (Source_Image.isEmpty() || Source_QImage.isNull())
	{
		output_Text(QString::fromLocal8Bit("源图像-------->目的图像"), 0, QString::fromLocal8Bit("源图像为空\n"));
	}
	else
	{
		Destination_Image = Source_Image;
		Destination_QImage = Source_QImage.copy();
		ui.Image_2->setPixmap((QPixmap(QPixmap::fromImage(Source_QImage)).scaled(ui.Image_2->size(), Qt::KeepAspectRatio)));
		output_Text(QString::fromLocal8Bit("源图像-------->目的图像"), 1);
	}
}

void MIL_Image::Destination_to_Source() {
	if (Destination_Image.isEmpty() || Destination_QImage.isNull())
	{
		output_Text(QString::fromLocal8Bit("目的图像-------->源图像"), 0, QString::fromLocal8Bit("目的图像为空\n"));
	}
	else
	{
		Source_Image = Destination_Image;
		Source_QImage = Destination_QImage.copy();
		ui.Image_1->setPixmap((QPixmap(QPixmap::fromImage(Source_QImage)).scaled(ui.Image_2->size(), Qt::KeepAspectRatio)));
		output_Text(QString::fromLocal8Bit("目的图像-------->源图像"), 1);
	}
}

void MIL_Image::show_ImageView_menu(QPoint) {
	if (!(ui.tableWidget_Images->currentRow() < 0))
	{
		ui.menu_ImageList->move(cursor().pos());
		ui.menu_ImageList->show();
	}
}

void MIL_Image::open_Image_from_table_byAction() {
	QString path = ui.tableWidget_Images->item(ui.tableWidget_Images->currentRow(), 1)->text();
	if (Source_Image.open_Image(path))
	{
		Source_QImage = cvMatToQImage(Source_Image.get_image());
		ui.Image_1->setPixmap((QPixmap(QPixmap::fromImage(Source_QImage)).scaled(ui.Image_1->size(), Qt::KeepAspectRatio)));
		output_Text(QString::fromLocal8Bit("打开  ") + path, 1);
	}
	else
	{
		output_Text(QString::fromLocal8Bit("打开") + path, 0, QString::fromLocal8Bit("文件正在被占用或已被删除\n"));
		if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), QString::fromLocal8Bit("是否移除该无效项？"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
		{
			remove_Image_from_table_byAction();
		}
	}
}

void MIL_Image::remove_Image_from_table_byAction() {
	int row = ui.tableWidget_Images->currentRow();
	QString path = ui.tableWidget_Images->item(row, 1)->text();
	if (!path.compare(Source_Image.get_imagePath()))
	{
		Source_Image.eraseImage();
		ui.Image_1->clear();
	}
	opened_Images.remove(path);
	ui.tableWidget_Images->removeRow(row);
	output_Text(QString::fromLocal8Bit("移除  ") + path, 1);
}

void MIL_Image::copy_ImagePath_from_table_byAction() {
	QString path = ui.tableWidget_Images->item(ui.tableWidget_Images->currentRow(), 1)->text();
	QApplication::clipboard()->setText(path);
	output_Text(QString::fromLocal8Bit("已复制路径到剪贴板"), 2, path + QString::fromLocal8Bit("\n"));
}

void MIL_Image::show_SVMs_menu(QPoint) {
	if (!(ui.tableWidget_SVMs->currentRow() < 0))
	{
		ui.menu_SVMs->move(cursor().pos());
		ui.menu_SVMs->show();
	}
}

void MIL_Image::remove_SVM_from_table_byAction() {
	int row = ui.tableWidget_SVMs->currentRow();
	QString path = ui.tableWidget_SVMs->item(row, 1)->text();
	ui.tableWidget_SVMs->removeRow(row);
	opened_SVMs.remove(path);
	output_Text(QString::fromLocal8Bit("移除  ") + path, 1);
}

void MIL_Image::remove_allSVM_from_table_byAction() {
	ui.tableWidget_SVMs->clearContents();
	ui.tableWidget_SVMs->setRowCount(0);
	opened_SVMs.clear();
	output_Text(QString::fromLocal8Bit("移除全部SVM"), 1);
}

void MIL_Image::copy_SVMPath_from_table_byAction() {
	QString path = ui.tableWidget_SVMs->item(ui.tableWidget_SVMs->currentRow(), 1)->text();
	QApplication::clipboard()->setText(path);
	output_Text(QString::fromLocal8Bit("已复制路径到剪贴板"), 2, path + QString::fromLocal8Bit("\n"));
}

void MIL_Image::select_SVM(QTableWidgetItem* item) {
	if (item->column() == 0)
	{
		return;
	}
	if (Qt::Unchecked == ui.tableWidget_SVMs->item(item->row(), 0)->checkState())
	{
		ui.tableWidget_SVMs->item(item->row(), 0)->setCheckState(Qt::Checked);
	}
	else
	{
		ui.tableWidget_SVMs->item(item->row(), 0)->setCheckState(Qt::Unchecked);
	}
}

void MIL_Image::open_Image_from_table(QTableWidgetItem* item) {
	QString path = ui.tableWidget_Images->item(item->row(), 1)->text();
	if (Source_Image.open_Image(path))
	{
		Source_QImage = cvMatToQImage(Source_Image.get_image());
		ui.Image_1->setPixmap((QPixmap(QPixmap::fromImage(Source_QImage)).scaled(ui.Image_1->size(), Qt::KeepAspectRatio)));
		output_Text(QString::fromLocal8Bit("打开  ") + path, 1);
	}
	else
	{
		output_Text(QString::fromLocal8Bit("打开") + path, 0, QString::fromLocal8Bit("文件正在被占用或已被删除\n"));
		if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), QString::fromLocal8Bit("是否移除该无效项？"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
		{
			remove_Image_from_table(item);
		}
	}
}

void MIL_Image::remove_Image_from_table(QTableWidgetItem *item) {
	int row = item->row();
	QString path = ui.tableWidget_Images->item(row, 1)->text();
	if (!path.compare(Source_Image.get_imagePath()))
	{
		Source_Image.eraseImage();
		ui.Image_1->clear();
	}
	opened_Images.remove(path);
	ui.tableWidget_Images->removeRow(row);
	output_Text(QString::fromLocal8Bit("移除") + path, 1);
}

void MIL_Image::remove_SVM_from_table(QTableWidgetItem *item) {
	int row = item->row();
	QString path = ui.tableWidget_SVMs->item(row, 1)->text();
	ui.tableWidget_SVMs->removeRow(row);
	output_Text(QString::fromLocal8Bit("移除") + path, 1);
}
