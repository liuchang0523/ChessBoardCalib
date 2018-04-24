#include "start_page.h"
#include <QFileDialog>

start_page::start_page(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	MakeChessboardPattern(chessboard_img, ui.spinBox_row->value(), ui.spinBox_col->value());
	img_show = Mat2QImage(chessboard_img);
	img_show = img_show.scaled(ui.label_show->width(), ui.label_show->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_show->setPixmap(QPixmap::fromImage(img_show));
}

start_page::~start_page()
{
}


QImage start_page::Mat2QImage(const cv::Mat& mat)
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


void start_page::MakeChessboardPattern(cv::Mat &outChessboard, int inRows, int inCols,
	int inSquareSize, cv::Scalar color1, cv::Scalar color2)
{
	CV_Assert(inRows > 1 && inCols > 1);
	CV_Assert(inSquareSize > 0);

	int chessboardImgCols = inCols * inSquareSize;
	int chessboardImgRows = inRows * inSquareSize;
	outChessboard = cv::Mat(chessboardImgRows, chessboardImgCols, CV_8UC3, cv::Scalar(0, 0, 0));

	for (size_t rows = 0, rowNum = 0; rows < chessboardImgRows; rows += inSquareSize, rowNum++)
	{
		for (size_t cols = 0, colNum = 0; cols < chessboardImgCols; cols += inSquareSize, colNum++)
		{
			cv::Rect rec(cols, rows, inSquareSize, inSquareSize);
			if ((rowNum + colNum) % 2 == 0)
				rectangle(outChessboard, rec, color1, -1, 8);
			else
				rectangle(outChessboard, rec, color2, -1, 8);
		}
	}
}

void start_page::on_spinBox_row_valueChanged(int)
{
	MakeChessboardPattern(chessboard_img, ui.spinBox_row->value(), ui.spinBox_col->value());
	img_show = Mat2QImage(chessboard_img);
	img_show = img_show.scaled(ui.label_show->width(), ui.label_show->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_show->setPixmap(QPixmap::fromImage(img_show));
}

void start_page::on_spinBox_col_valueChanged(int)
{
	MakeChessboardPattern(chessboard_img, ui.spinBox_row->value(), ui.spinBox_col->value());
	img_show = Mat2QImage(chessboard_img);
	img_show = img_show.scaled(ui.label_show->width(), ui.label_show->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_show->setPixmap(QPixmap::fromImage(img_show));
}

void start_page::on_pushButton_save_clicked()
{
	if (!chessboard_img.empty())
	{
		QString filename = QFileDialog::getSaveFileName(this, QStringLiteral("保存"), "./Chessboard.bmp", "*.bmp");
		if (filename.isEmpty())
		{
			return;
		}
		cv::imwrite(filename.toLocal8Bit().toStdString(), chessboard_img);
	}
}

void start_page::on_pushButton_clicked()
{
	this->close();
}

void start_page::closeEvent(QCloseEvent *e)
{
	emit myClose(ui.spinBox_row->value() - 1, ui.spinBox_col->value() - 1, ui.doubleSpinBox->value());
}
