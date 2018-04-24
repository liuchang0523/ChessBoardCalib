#pragma once

#include <QDialog>
#include "ui_start_page.h"
#include <opencv2/opencv.hpp>
#include <QDebug>


class start_page : public QDialog
{
	Q_OBJECT

public:
	start_page(QWidget *parent = Q_NULLPTR);
	~start_page();

	QImage Mat2QImage(const cv::Mat& mat);

	void MakeChessboardPattern(cv::Mat &outChessboard, int inRows, int inCols,
		int inSquareSize = 100, cv::Scalar color1 = CV_RGB(0, 0, 0),
		cv::Scalar color2 = CV_RGB(255, 255, 255));


	private slots:
	void on_spinBox_row_valueChanged(int);
	void on_spinBox_col_valueChanged(int);
	void on_pushButton_save_clicked();
	void on_pushButton_clicked();
	void closeEvent(QCloseEvent *e);

signals:
	void myClose(int, int, double);

private:
	Ui::start_page ui;
	cv::Mat chessboard_img;
	QImage img_show;
};
