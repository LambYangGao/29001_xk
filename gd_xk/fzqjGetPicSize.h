#pragma once

#include <QWidget>
#include <opencv2/opencv.hpp>
#include<qstyleoption.h>
#include<qpainter.h>
#include<QDebug>

#include "ui_fzqjGetPicSize.h"
#include <qpen.h>

class fzqjGetPicSize : public QWidget
{
	Q_OBJECT

public:
	fzqjGetPicSize(QWidget *parent = nullptr);
	~fzqjGetPicSize();

private:
	Ui::fzqjGetPicSizeClass ui;
	QImage cvMat2Qimage(const cv::Mat& mat);
	cv::Point qpointToPoint(QPoint qpoint);
	float calRealSize(float pixe_size,int pixe_num,float dis,float focal_len);
	float vi_pixe_size = 2.9*0.001*0.001;//m
	float ir_pixe_size = 15*0.001*0.001;//m
	float real_dis = 0;
	float focal_length = 0;
	float in_vi_focal_length = 0;
	float in_ir_focal_length = 0;
	float get_vi_focal_length = 0;
	float get_ir_focal_length = 0;
	int pixe_num = 0;
	bool is_current_vi = true;
	cv::Mat mat_vi;
	cv::Mat mat_ir;

	cv::Mat scale_image_vi;
	cv::Mat scale_image_ir;


public slots:
	void on_btnImageRefresh_clicked(void);
	void updateImageMat(cv::Mat in_mat_vi, cv::Mat in_mat_ir);
	void updatePainterSizeVi(QPoint startPT, QPoint endPT, float width, float height);
	void updatePainterSizeIr(QPoint startPT, QPoint endPT, float width, float height);
	void on_btnCount_clicked(void);
	void updateCurrentStateVi(bool current_state);
	void updateCurrentStateIr(bool current_state);
	void updateFocalLength(int vi_num,int ir_num);

};
