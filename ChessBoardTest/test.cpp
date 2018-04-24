#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int chessboard_row = 9;
int chessboard_col = 6;
int img_num = 23;


static double computeReprojectionErrors(const vector<vector<Point3f> >& objectPoints,
	const vector<vector<Point2f> >& imagePoints,
	const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	const Mat& cameraMatrix, const Mat& distCoeffs,
	vector<double>& perViewErrors)
{
	vector<Point2f> imagePoints2;
	int i, totalPoints = 0;
	double totalErr = 0, err;
	perViewErrors.resize(objectPoints.size());

	for (i = 0; i < (int)objectPoints.size(); ++i)
	{
		projectPoints(Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix,
			distCoeffs, imagePoints2);
		err = norm(Mat(imagePoints[i]), Mat(imagePoints2), CV_L2);

		int n = (int)objectPoints[i].size();
		perViewErrors[i] = (double)std::sqrt(err*err / n);
		totalErr += err * err;
		totalPoints += n;
	}

	return std::sqrt(totalErr / totalPoints);
}



int main()
{
	std::vector<std::vector<Point2f>> corners_vec;
	std::string name = "./images/R/R_";
	cv::Size img_size;
	for (int i = 1; i < img_num + 1; ++i)
	{
		std::string imgname = name + std::to_string(i) + ".bmp";

		cv::Mat img = imread(imgname, 0);
		std::vector<Point2f> corners;
		if (!img.empty())
		{
			img_size = img.size();
			//查找棋盘格角点
			bool found = findChessboardCorners(img, Size(chessboard_row, chessboard_col), corners,
				CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);

			if (found)
			{
				//亚像素优化角点
				find4QuadCornerSubpix(img, corners, Size(chessboard_row, chessboard_col));
				corners_vec.push_back(corners);
			}
#if 0
			cv::Mat img_color;
			cvtColor(img, img_color, CV_GRAY2BGR);
			drawChessboardCorners(img_color, Size(chessboard_row, chessboard_col), corners, found);
			for (int j = 0; j < corners.size(); ++j)
			{
				putText(img_color, std::to_string(j), corners[j], FONT_HERSHEY_SCRIPT_SIMPLEX, 1,
					Scalar(0, 0, 255), 2);
			}

			putText(img_color, std::to_string(i), Point(100, 100), FONT_HERSHEY_SCRIPT_SIMPLEX, 3,
				Scalar(0, 0, 255), 3);
			imshow("chessboard", img_color);
			waitKey();
#endif
		}
	}


	float d = 26.5;
	//creat object points
	std::vector<Point3f> object_points;
	for (int i = 0; i < chessboard_col; ++i)
	{
		for (int j = 0; j < chessboard_row; ++j)
		{
			object_points.push_back(cv::Point3f(j * d, i * d, 0));
		}
	}

	std::vector<std::vector<Point3f>> object_points_vec;
	for (int i = 0; i < corners_vec.size(); ++i)
	{
		object_points_vec.push_back(object_points);
	}

	Mat M = cv::Mat(3, 3, CV_64F, cv::Scalar::all(0));
	M.at<double>(0, 0) = 1;
	M.at<double>(1, 1) = 1;

	Mat K = cv::Mat(1, 5, CV_64F, cv::Scalar::all(0));
	K.at<double>(0, 4) = 0;

	Mat stdI, stdE, perViewErrors;
	vector<Mat> rvecs, tvecs;
	double rms = calibrateCamera(object_points_vec, corners_vec, img_size, M, K,
		rvecs, tvecs, stdI, stdE, perViewErrors, CV_CALIB_FIX_K3 /*CV_CALIB_FIX_ASPECT_RATIO*/,
		cv::TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 30, DBL_EPSILON));

	bool ok = checkRange(M) && checkRange(K);
	if (not ok)
	{
		return -1;
	}

	std::cout << rms;

	//vector<double> errors;
	//double error = computeReprojectionErrors(object_points_vec, corners_vec, rvecs, tvecs, M, K, errors);

	FileStorage fs("result.xml", FileStorage::WRITE);
	fs << "cameraMatrix" << M;
	fs << "distCoeffs" << K;
	fs.release();

	ofstream file("test.csv");
	file << format(M, Formatter::FMT_CSV);
	file.close();


	cv::Mat img = imread("./img/R_2.bmp", 0);
	cv::Mat result_img;
	undistort(img, result_img, M, K);
	imshow("undistort", result_img);
	waitKey();
	return 0;
}
