#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_stereo_calib.h"
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

class stereo_calib : public QMainWindow
{
	Q_OBJECT

public:
	stereo_calib(QWidget *parent = Q_NULLPTR);

	QImage Mat2QImage(const cv::Mat& mat);
	void image_show(const cv::Mat& img);

	void create_object_points(int, int, int);



	private slots:
	void on_actionCalib_triggered();
	void on_actionStereo_triggered();

	void chessboard_size_slot(int, int, double);


private:
	Ui::stereo_calibClass ui;


	cv::Size img_size_;
	cv::Mat M_, K_;

	//标准世界坐标
	std::vector<cv::Point3f> object_points_;
	std::vector<std::vector<cv::Point3f>> object_points_vec_;

	//图片路径
	QStringList m_image_list_;
	std::vector<std::vector<cv::Point2f>> corners_vec_;
	QString m_parent_path_ = ".";
	cv::Size chessboard_size_;

	//立体标定
	struct Stereo
	{
		cv::Mat M_1, M_2, K_1, K_2;
		std::vector<std::vector<cv::Point2f>> corners_vec_1;
		std::vector<std::vector<cv::Point2f>> corners_vec_2;
		std::vector<std::vector<cv::Point3f>> object_points_vec;
		cv::Mat R, T;
	};
	Stereo stereo_;
};
