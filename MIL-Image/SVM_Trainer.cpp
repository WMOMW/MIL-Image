#include "stdafx.h"

SVM_Trainer::SVM_Trainer(QWidget *parent)
	:QMainWindow(parent)
{
	this->parent = parent;

	ui.setupUi(this);
	setWindowModality(Qt::WindowModal);

	connect(ui.add_bags, SIGNAL(clicked()), this, SLOT(open_Bags()));
	connect(ui.add_Nbags, SIGNAL(clicked()), this, SLOT(open_NBags()));
	connect(ui.training_and_save, SIGNAL(clicked()), this, SLOT(save_SVM()));

	connect(ui.tableWidget_bags, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_bagsView_menu(QPoint)));
	connect(ui.tableWidget_Nbags, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_NbagsView_menu(QPoint)));

	connect(ui.action_bagsView_open, SIGNAL(triggered()), this, SLOT(open_Image_from_bagsView_byAction()));
	connect(ui.action_bagsView_remove, SIGNAL(triggered()), this, SLOT(remove_Image_from_bagsView_byAction()));
	connect(ui.action_bagsView_removeAll, SIGNAL(triggered()), this, SLOT(remove_allImage_from_bagsView_byAction()));
	connect(ui.action_bagsView_copyPath, SIGNAL(triggered()), this, SLOT(copy_ImagePath_from_bagsView_byAction()));
	connect(ui.action_NbagsView_open, SIGNAL(triggered()), this, SLOT(open_Image_from_NbagsView_byAction()));
	connect(ui.action_NbagsView_remove, SIGNAL(triggered()), this, SLOT(remove_Image_from_NbagsView_byAction()));
	connect(ui.action_NbagsView_removeAll, SIGNAL(triggered()), this, SLOT(remove_allImage_from_NbagsView_byAction()));
	connect(ui.action_NbagsView_copyPath, SIGNAL(triggered()), this, SLOT(copy_ImagePath_from_NbagsView_byAction()));

	connect(ui.tableWidget_bags, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(open_Image_from_bagsView(QTableWidgetItem*)));
	connect(ui.tableWidget_Nbags, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(open_Image_from_NbagsView(QTableWidgetItem*)));

	connect(ui.training_and_save, SIGNAL(clicked()), this, SLOT(ttt()));
}

void SVM_Trainer::ttt() {
	//TrainingTools_Interface::test();
	//TrainingTools_Interface::Create_Classifier();

}

void SVM_Trainer::open_Bags() {
	QStringList files_names = QFileDialog::getOpenFileNames(
		this,
		QString::fromLocal8Bit("预加载正包"),
		file_path,
		"Images (*.png , *.jpg)");
	if (!files_names.isEmpty())
	{
		int rows = ui.tableWidget_bags->rowCount();
		int rows_temp = rows;
		int successful = 0, failed = 0;
		for (auto p : files_names)
		{
			QFileInfo f(p);
			if (f.suffix().compare("jpg", Qt::CaseInsensitive) && f.suffix().compare("png", Qt::CaseInsensitive))
			{
				continue;
			}
			if (opened_features.find(p) == opened_features.end())
			{
				opened_features.insert(p);
				ui.tableWidget_bags->insertRow(rows);
				ui.tableWidget_bags->setItem(rows, 0, new QTableWidgetItem(f.fileName()));
				ui.tableWidget_bags->setItem(rows, 1, new QTableWidgetItem(p));
				++rows;
				++successful;
			}
			else
			{
				++failed;
				output_to_main(QString::fromLocal8Bit("预加载正包  ") + p, 0, QString::fromLocal8Bit("已经被导入\n"));
			}
		}
		ui.tableWidget_bags->selectRow(rows_temp);
		if (ui.tableWidget_bags->currentRow() >= 0)
		{
			file_path = ui.tableWidget_bags->item(ui.tableWidget_bags->currentRow(), 1)->text();
			QPixmap img;
			if (img.load(file_path))
			{
				ui.Image_bag->setPixmap((img.scaled(ui.Image_bag->size(), Qt::KeepAspectRatio)));
				path_bagImage = file_path;
				output_to_main(QString::fromLocal8Bit("打开  ") + file_path, 1);
			}
			else
			{
				output_to_main(QString::fromLocal8Bit("打开  ") + file_path, 0);
			}
		}
		output_to_main(QString::fromLocal8Bit("预加载正包   (") + QString::number(successful, 10) + '/' + QString::number(successful + failed, 10) + ')', 1);
	}
}

void SVM_Trainer::save_SVM() {
	int rows_bags = ui.tableWidget_bags->rowCount();
	int rows_Nbags = ui.tableWidget_Nbags->rowCount();
	QStringList bags_path, Nbags_path;
	cv::Mat temp;
	if (rows_bags == 0 || rows_Nbags == 0)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("正包示例或者反包示例为空"), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	for (int i = 0; i < rows_bags; ++i)
	{
		QString path = ui.tableWidget_bags->item(i, 1)->text();
		temp = cv::imread(path.toLocal8Bit().toStdString(), 1);
		if (temp.empty())
		{
			if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), path + QString::fromLocal8Bit("为空") + QString::fromLocal8Bit("\n移除该无效项并继续执行?"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
			{
				remove_Image_from_bagsView(ui.tableWidget_bags->item(i, 0));
				--i;
				--rows_bags;
				continue;
			}
			else
			{
				return;
			}
		}
		temp.release();
		bags_path.push_back(path);
	}
	if (rows_bags == 0 || rows_Nbags == 0)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("正包示例或者反包示例为空"), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	for (int i = 0; i < rows_Nbags; ++i)
	{
		QString path = ui.tableWidget_Nbags->item(i, 1)->text();
		if (cv::imread(path.toLocal8Bit().toStdString(), 1).empty())
		{
			if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), path + QString::fromLocal8Bit("为空") + QString::fromLocal8Bit("\n移除该无效项并继续执行?"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
			{
				remove_Image_from_NbagsView(ui.tableWidget_Nbags->item(i, 0));
				--i;
				--rows_Nbags;
				continue;
			}
			else
			{
				return;
			}
		}
		Nbags_path.push_back(ui.tableWidget_Nbags->item(i, 1)->text());
	}
	QString save_path = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("另存为"), ".\\SVMs", " (*.xml)");
	if (save_path.isEmpty())
	{
		return;
	}
	QFileInfo f(save_path);
	if (f.suffix().compare("xml", Qt::CaseInsensitive))
	{
		output_to_main(QString::fromLocal8Bit("保存SVM分类器"), 0, QString::fromLocal8Bit("文件不能为 *.xml 之外的格式\n"));
		return;
	}
	QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("即将开始算法，其间会跳过无法打开的文件，但算法不会终止。\n即使关闭窗口分类训练也会在后台继续执行。"), QMessageBox::Ok, QMessageBox::Ok);

	output_to_main(QString::fromLocal8Bit("正在训练分类器......"));
	begin_Algorithm();
	CreateClassifier_Thread *thread = new CreateClassifier_Thread(bags_path, Nbags_path, save_path, this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(end_Algorithm(QString, int, QString)), this, SLOT(end_Algorithm(QString, int, QString)));
	connect(thread, SIGNAL(output_to_main(QString, int, QString)), this, SIGNAL(output_to_main(QString, int, QString)));
	thread->start();
}

void SVM_Trainer::open_Image_from_bagsView_byAction() {
	QString path = ui.tableWidget_bags->item(ui.tableWidget_bags->currentRow(), 1)->text();
	QPixmap img;
	if (img.load(path))
	{
		path_bagImage = path;
		ui.Image_bag->setPixmap((img.scaled(ui.Image_bag->size(), Qt::KeepAspectRatio)));
		output_to_main(QString::fromLocal8Bit("打开  ") + path, 1);
	}
	else
	{
		output_to_main(QString::fromLocal8Bit("打开") + path, 0, QString::fromLocal8Bit("文件正在被占用或已被删除\n"));
		if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), QString::fromLocal8Bit("是否移除该无效项？"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
		{
			remove_Image_from_bagsView_byAction();
		}
	}
}

void SVM_Trainer::remove_Image_from_bagsView_byAction() {
	int row = ui.tableWidget_bags->currentRow();
	QString path = ui.tableWidget_bags->item(row, 1)->text();
	if (!path.compare(path_bagImage))
	{
		path_bagImage.clear();
		ui.Image_bag->clear();
	}
	opened_features.remove(path);
	ui.tableWidget_bags->removeRow(row);
	output_to_main(QString::fromLocal8Bit("移除正包  ") + path, 1);
}

void SVM_Trainer::remove_allImage_from_bagsView_byAction() {
	int max_row = ui.tableWidget_bags->rowCount();
	if (max_row >= 0)
	{
		for (int row = 0; row < max_row; ++row)
		{
			opened_features.remove(ui.tableWidget_bags->item(row, 1)->text());
		}
		ui.tableWidget_bags->clearContents();
		ui.tableWidget_bags->setRowCount(0);
		path_bagImage.clear();
		ui.Image_bag->clear();
		output_to_main(QString::fromLocal8Bit("移除全部正包"), 1);
	}
}

void SVM_Trainer::copy_ImagePath_from_bagsView_byAction() {
	QString path = ui.tableWidget_bags->item(ui.tableWidget_bags->currentRow(), 1)->text();
	QApplication::clipboard()->setText(path);
	output_to_main(QString::fromLocal8Bit("已复制路径到剪贴板"), 2, path + QString::fromLocal8Bit("\n"));
}

void SVM_Trainer::open_NBags() {
	QStringList files_names = QFileDialog::getOpenFileNames(
		this,
		QString::fromLocal8Bit("预加载反包"),
		file_path,
		"Images (*.png , *.jpg)");
	if (!files_names.isEmpty())
	{
		int rows = ui.tableWidget_Nbags->rowCount();
		int rows_temp = rows;
		int successful = 0, failed = 0;
		for (auto p : files_names)
		{
			QFileInfo f(p);
			if (f.suffix().compare("jpg", Qt::CaseInsensitive) && f.suffix().compare("png", Qt::CaseInsensitive))
			{
				continue;
			}
			if (opened_features.find(p) == opened_features.end())
			{
				opened_features.insert(p);
				ui.tableWidget_Nbags->insertRow(rows);
				ui.tableWidget_Nbags->setItem(rows, 0, new QTableWidgetItem(f.fileName()));
				ui.tableWidget_Nbags->setItem(rows, 1, new QTableWidgetItem(p));
				++rows;
				++successful;
			}
			else
			{
				++failed;
				output_to_main(QString::fromLocal8Bit("预加载反包  ") + p, 0, QString::fromLocal8Bit("已经被导入\n"));
			}
		}
		ui.tableWidget_Nbags->selectRow(rows_temp);
		if (ui.tableWidget_Nbags->currentRow() >= 0)
		{
			file_path = ui.tableWidget_Nbags->item(ui.tableWidget_Nbags->currentRow(), 1)->text();
			QPixmap img;
			if (img.load(file_path))
			{
				ui.Image_Nbag->setPixmap((img.scaled(ui.Image_Nbag->size(), Qt::KeepAspectRatio)));
				path_NbagImage = file_path;
				output_to_main(QString::fromLocal8Bit("打开  ") + file_path, 1);
			}
			else
			{
				output_to_main(QString::fromLocal8Bit("打开  ") + file_path, 0);
			}
		}
		output_to_main(QString::fromLocal8Bit("预加载反包   (") + QString::number(successful, 10) + '/' + QString::number(successful + failed, 10) + ')', 1);
	}
}

void SVM_Trainer::open_Image_from_NbagsView_byAction() {
	QString path = ui.tableWidget_Nbags->item(ui.tableWidget_Nbags->currentRow(), 1)->text();
	QPixmap img;
	if (img.load(path))
	{
		path_NbagImage = path;
		ui.Image_Nbag->setPixmap((img.scaled(ui.Image_Nbag->size(), Qt::KeepAspectRatio)));
		output_to_main(QString::fromLocal8Bit("打开  ") + path, 1);
	}
	else
	{
		output_to_main(QString::fromLocal8Bit("打开") + path, 0, QString::fromLocal8Bit("文件正在被占用或已被删除\n"));
		if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), QString::fromLocal8Bit("是否移除该无效项？"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
		{
			remove_Image_from_NbagsView_byAction();
		}
	}
}

void SVM_Trainer::remove_Image_from_NbagsView_byAction() {
	int row = ui.tableWidget_Nbags->currentRow();
	QString path = ui.tableWidget_Nbags->item(row, 1)->text();
	if (!path.compare(path_NbagImage))
	{
		path_NbagImage.clear();
		ui.Image_Nbag->clear();
	}
	opened_features.remove(path);
	ui.tableWidget_Nbags->removeRow(row);
	output_to_main(QString::fromLocal8Bit("移除反包  ") + path, 1);
}

void SVM_Trainer::remove_allImage_from_NbagsView_byAction() {
	int max_row = ui.tableWidget_Nbags->rowCount();
	if (max_row >= 0)
	{
		for (int row = 0; row < max_row; ++row)
		{
			opened_features.remove(ui.tableWidget_Nbags->item(row, 1)->text());
		}
		ui.tableWidget_Nbags->clearContents();
		ui.tableWidget_Nbags->setRowCount(0);
		path_NbagImage.clear();
		ui.Image_Nbag->clear();
		output_to_main(QString::fromLocal8Bit("移除全部反包"), 1);
	}
}

void SVM_Trainer::copy_ImagePath_from_NbagsView_byAction() {
	QString path = ui.tableWidget_Nbags->item(ui.tableWidget_Nbags->currentRow(), 1)->text();
	QApplication::clipboard()->setText(path);
	output_to_main(QString::fromLocal8Bit("已复制路径到剪贴板"), 2, path + QString::fromLocal8Bit("\n"));
}

void SVM_Trainer::show_bagsView_menu(QPoint) {
	if (!(ui.tableWidget_bags->currentRow() < 0))
	{
		ui.menu_bagsTable->move(cursor().pos());
		ui.menu_bagsTable->show();
	}
}

void SVM_Trainer::show_NbagsView_menu(QPoint) {
	if (!(ui.tableWidget_Nbags->currentRow() < 0))
	{
		ui.menu_NbagsTable->move(cursor().pos());
		ui.menu_NbagsTable->show();
	}
}

void SVM_Trainer::open_Image_from_bagsView(QTableWidgetItem *item) {
	QString path = ui.tableWidget_bags->item(item->row(), 1)->text();
	QPixmap img;
	if (img.load(path))
	{
		path_bagImage = path;
		ui.Image_bag->setPixmap((img.scaled(ui.Image_bag->size(), Qt::KeepAspectRatio)));
		output_to_main(QString::fromLocal8Bit("打开  ") + path, 1);
	}
	else
	{
		output_to_main(QString::fromLocal8Bit("打开") + path, 0, QString::fromLocal8Bit("文件正在被占用或已被删除\n"));
		if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), QString::fromLocal8Bit("是否移除该无效项？"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
		{
			remove_Image_from_bagsView(item);
		}
	}
}

void SVM_Trainer::open_Image_from_NbagsView(QTableWidgetItem *item) {
	QString path = ui.tableWidget_Nbags->item(item->row(), 1)->text();
	QPixmap img;
	if (img.load(path))
	{
		path_NbagImage = path;
		ui.Image_Nbag->setPixmap((img.scaled(ui.Image_Nbag->size(), Qt::KeepAspectRatio)));
		output_to_main(QString::fromLocal8Bit("打开  ") + path, 1);
	}
	else
	{
		output_to_main(QString::fromLocal8Bit("打开") + path, 0, QString::fromLocal8Bit("文件正在被占用或已被删除\n"));
		if (QMessageBox::question(this, QString::fromLocal8Bit("确认"), QString::fromLocal8Bit("是否移除该无效项？"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
		{
			remove_Image_from_NbagsView(item);
		}
	}
}

void SVM_Trainer::remove_Image_from_bagsView(QTableWidgetItem *item) {
	int row = item->row();
	QString path = ui.tableWidget_bags->item(row, 1)->text();
	if (!path.compare(path_bagImage))
	{
		path_bagImage.clear();
		ui.Image_bag->clear();
	}
	opened_features.remove(path);
	ui.tableWidget_bags->removeRow(row);
	output_to_main(QString::fromLocal8Bit("移除正包  ") + path, 1);
}

void SVM_Trainer::remove_Image_from_NbagsView(QTableWidgetItem *item) {
	int row = item->row();
	QString path = ui.tableWidget_Nbags->item(row, 1)->text();
	if (!path.compare(path_NbagImage))
	{
		path_NbagImage.clear();
		ui.Image_Nbag->clear();
	}
	opened_features.remove(path);
	ui.tableWidget_Nbags->removeRow(row);
	output_to_main(QString::fromLocal8Bit("移除正包  ") + path, 1);
}

void SVM_Trainer::begin_Algorithm() {
	this->setEnabled(false);
}

void SVM_Trainer::end_Algorithm(QString message, int state, QString about) {
	output_to_main(message, state, about);
	this->setEnabled(true);
}
