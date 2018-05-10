#include "stereo_calib.h"
#include "start_page.h"

stereo_calib::stereo_calib(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	start_page s;
	connect(&s, SIGNAL(myClose(int, int, double)), this, SLOT(chessboard_size_slot(int, int, double)));
	s.exec();
	//设置显示误差柱状图
	ui.customPlot->addGraph();
	ui.customPlot->setInteraction(QCP::iRangeDrag, true);
	//qDebug() << object_points_.size();
}


QImage stereo_calib::Mat2QImage(const cv::Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}


void stereo_calib::image_show(const cv::Mat& img)
{
	QPixmap pixmap = QPixmap::fromImage(Mat2QImage(img));
	pixmap = pixmap.scaled(ui.label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label->setPixmap(pixmap);
}

void stereo_calib::create_object_points(int row, int col, int d)
{
	//creat object points
	//std::vector<cv::Point3f> object_points;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			object_points_.push_back(cv::Point3f(j * d, i * d, 0));
		}
	}
}

void stereo_calib::on_actionCalib_triggered()
{
	m_image_list_ = QFileDialog::getOpenFileNames(this, QStringLiteral("打开图片文件"), m_parent_path_, "Image(*.bmp *.png *.jpg)");
	if (m_image_list_.size() == 0)
	{
		QMessageBox::warning(this, QStringLiteral("未选择图片"), QStringLiteral("未选择图片"));
		return;
	}
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	//////////////////////////////////////////////////////////////////////////
	//记录上级目录
	QDir dir_temp(m_image_list_[0]);
	dir_temp.cdUp();
	m_parent_path_ = dir_temp.absolutePath();
	//////////////////////////////////////////////////////////////////////////

	corners_vec_.clear();

	for each (QString img_path in m_image_list_)
	{
		//qDebug() << img_path;
		cv::Mat img_t = cv::imread(img_path.toLocal8Bit().toStdString(), 0);
		std::vector<cv::Point2f> corners_t;
		if (!img_t.empty())
		{
			img_size_ = img_t.size();

			//查找棋盘格角点
			bool found_t = findChessboardCorners(img_t, chessboard_size_, corners_t,
				cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

			if (found_t)
			{
				//亚像素优化角点
				find4QuadCornerSubpix(img_t, corners_t, chessboard_size_);
				corners_vec_.push_back(corners_t);

#if 1
				cv::Mat img_color_t;
				cvtColor(img_t, img_color_t, CV_GRAY2BGR);
				cv::drawChessboardCorners(img_color_t, chessboard_size_, corners_t, found_t);
#if 0 //显示角点编号 
				for (int j = 0; j < corners_t.size(); ++j)
				{
					cv::putText(img_color_t, std::to_string(j), corners_t[j],
						cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
				}
#endif

				QDir dir_t(img_path);
				QString name_ = dir_t.dirName();

				cv::putText(img_color_t, name_.toStdString(), cv::Point(50, 50),
					cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);

				image_show(img_color_t);
				QApplication::processEvents();
#endif
			}
			else
			{
				qDebug() << "not found:" << img_path;
			}
		}
	}
	object_points_vec_.clear();
	if (corners_vec_.size() >= 5)
	{
		//初始化标准世界坐标数组
		for (int i = 0; i < corners_vec_.size(); ++i)
		{
			object_points_vec_.push_back(object_points_);
		}
	}
	else
	{
		return;
	}

	M_ = cv::Mat::eye(3, 3, CV_64F);

	cv::Mat perViewErrors;
	double rms = calibrateCamera(object_points_vec_, corners_vec_, img_size_, M_, K_,
		cv::noArray(), cv::noArray(), cv::noArray(), cv::noArray(), perViewErrors,
		CV_CALIB_FIX_K3 + CV_CALIB_FIX_ASPECT_RATIO + CV_CALIB_ZERO_TANGENT_DIST,
		cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, DBL_EPSILON));


	//////////////////////////////////////////////////////////////////////////
	//设置显示误差柱状图
	QVector<double> x, y, y_avg;
	for (int i = 0; i < perViewErrors.rows; i++)
	{
		x.push_back(i + 1);
		y.push_back(perViewErrors.at<double>(i, 0));
		y_avg.push_back(rms);
	}

	ui.customPlot->clearPlottables();

	QCPBars *error = new QCPBars(ui.customPlot->xAxis, ui.customPlot->yAxis);
	error->setName("Fossil fuels");
	error->setPen(QPen(QColor(250, 170, 20).lighter(170)));
	error->setBrush(QColor(250, 170, 20));
	error->setData(x, y);
	ui.customPlot->rescaleAxes(true);
	ui.customPlot->addGraph();
	ui.customPlot->graph(0)->setPen(QPen(QColor(255, 0, 0)));
	ui.customPlot->graph(0)->setData(x, y_avg);
	ui.customPlot->xAxis->ticker()->setTickCount(perViewErrors.rows);
	ui.customPlot->replot();

	QApplication::restoreOverrideCursor();
	QMessageBox::information(this, QStringLiteral("标定完成"), QStringLiteral("标定误差:%1").arg(rms));


#if 0 //保存xml
	QString xml_filename_ = m_parent_path_ + "/calib_result.xml";
	xml_filename_ = QFileDialog::getSaveFileName(this, QStringLiteral("保存标定参数"), xml_filename_, "XML(*.xml)");
	if (!xml_filename_.isEmpty())
	{
		cv::FileStorage fs(xml_filename_.toLocal8Bit().toStdString(), cv::FileStorage::WRITE);
		fs << "error" << rms;
		fs << "cameraMatrix" << M_;
		fs << "distCoeffs" << K_;
		fs.release();
	}
#endif
}

void stereo_calib::on_actionStereo_triggered()
{
	//标定左摄像机
	emit on_actionCalib_triggered();
	stereo_.M_1 = M_.clone();
	stereo_.K_1 = K_.clone();
	stereo_.corners_vec_1 = corners_vec_;
	stereo_.object_points_vec = object_points_vec_;

	emit on_actionCalib_triggered();
	stereo_.M_2 = M_.clone();
	stereo_.K_2 = K_.clone();
	stereo_.corners_vec_2 = corners_vec_;

	if (stereo_.corners_vec_1.size() != stereo_.corners_vec_2.size())
	{
		QMessageBox::warning(this, QStringLiteral("左右图像有效数目不等"), QStringLiteral("左右图像有效数目不等"));
		return;
	}

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	cv::Mat E, F;
	double e = cv::stereoCalibrate(stereo_.object_points_vec, stereo_.corners_vec_1, stereo_.corners_vec_2,
		stereo_.M_1, stereo_.K_1, stereo_.M_2, stereo_.K_2, img_size_, stereo_.R, stereo_.T, E, F,
		CV_CALIB_FIX_INTRINSIC);

	QMessageBox::information(this, QStringLiteral("双目标定完成"), QStringLiteral("标定误差:%1").arg(e));

	QString xml_filename_ = m_parent_path_ + "/stereo_calib_result.xml";
	xml_filename_ = QFileDialog::getSaveFileName(this, QStringLiteral("保存标定参数"), xml_filename_, "XML(*.xml)");
	if (!xml_filename_.isEmpty())
	{
		cv::FileStorage fs(xml_filename_.toLocal8Bit().toStdString(), cv::FileStorage::WRITE);
		fs << "error" << e;
		fs << "cameraMatrix1" << stereo_.M_1;
		fs << "distCoeffs1" << stereo_.K_1;
		fs << "cameraMatrix2" << stereo_.M_2;
		fs << "distCoeffs2" << stereo_.K_2;
		fs << "R" << stereo_.R;
		fs << "T" << stereo_.T;
		fs.release();
	}
	QApplication::restoreOverrideCursor();
}

void stereo_calib::chessboard_size_slot(int row, int col, double d)
{
	chessboard_size_.height = row;
	chessboard_size_.width = col;
	create_object_points(row, col, d);
}
