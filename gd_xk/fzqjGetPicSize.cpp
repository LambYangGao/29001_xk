#include "fzqjGetPicSize.h"

fzqjGetPicSize::fzqjGetPicSize(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.windShowPicVi, &RectLabel::sig_painter_size, this, &fzqjGetPicSize::updatePainterSizeVi);
	connect(ui.windShowPicIr, &RectLabel::sig_painter_size, this, &fzqjGetPicSize::updatePainterSizeIr);
	connect(ui.windShowPicVi, &RectLabel::sig_current_wind, this, &fzqjGetPicSize::updateCurrentStateVi);
	connect(ui.windShowPicIr, &RectLabel::sig_current_wind, this, &fzqjGetPicSize::updateCurrentStateIr);
}

fzqjGetPicSize::~fzqjGetPicSize()
{
}

QImage fzqjGetPicSize::cvMat2Qimage(const cv::Mat& mat)
{
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		uchar* pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar* pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	else if (mat.type() == CV_8UC3)
	{
		const uchar* pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		const uchar* pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR:mat could not be converted to QImage";
		return QImage();
	}

}

cv::Point fzqjGetPicSize::qpointToPoint(QPoint qpoint)
{
	int x = qpoint.x();
	int y = qpoint.y();
	return cv::Point(x, y);
}

float fzqjGetPicSize::calRealSize(float pixe_size, int pixe_num, float dis, float focal_len)
{
	float H = 0;
	H = (pixe_size * pixe_num * dis) / (focal_len);
	return H;
}


void fzqjGetPicSize::updateImageMat(cv::Mat in_mat_vi, cv::Mat in_mat_ir)
{
	mat_vi = in_mat_vi;
	mat_ir = in_mat_ir;
}

void fzqjGetPicSize::updatePainterSizeVi(QPoint startPT, QPoint endPT, float width, float height)
{
	int get_width = width;
	int get_height = height;
	if (width < 0 || height < 0)
	{
		get_width = abs(width);
		get_height = abs(height);
	}
	ui.editWidth->setText(QString::number(get_width));
	ui.editHeight->setText(QString::number(get_height));

	if (scale_image_vi.empty())
	{
		return;
	}
	else
	{
		cv::Point cv_start_point = qpointToPoint(startPT);
		cv::Point cv_end_point = qpointToPoint(endPT);
		cv::Rect box(cv_start_point, cv_end_point);

		cv::Mat Roi(scale_image_vi, box);
		int pixel_count = Roi.rows;
		/*ui.editMatCount->setText(QString::number(pixel_count));*/
	}
}

void fzqjGetPicSize::updatePainterSizeIr(QPoint startPT, QPoint endPT, float width, float height)
{

	if (width < 0 || height < 0)
	{
		width = abs(width);
		height = abs(height);
	}
	ui.editWidth->setText(QString::number(width));
	ui.editHeight->setText(QString::number(height));
	if (scale_image_ir.empty())
	{
		return;
	}
	else
	{
		cv::Point cv_start_point = qpointToPoint(startPT);
		cv::Point cv_end_point = qpointToPoint(endPT);
		cv::Rect box(cv_start_point, cv_end_point);

		cv::Mat Roi(scale_image_ir, box);
		int pixel_count = Roi.total();
		//ui.editMatCount->setText(QString::number(pixel_count));
	}
}

void fzqjGetPicSize::on_btnCount_clicked(void)
{
	focal_length = ui.editFocusValue->text().toFloat() * 0.001;//米
	real_dis = ui.editDisValue->text().toFloat();//米
	pixe_num = ui.editHeight->text().toInt();
	float pixe_size = 0;
	if (is_current_vi)
	{
		pixe_size = vi_pixe_size;
	}
	else
	{
		pixe_size = ir_pixe_size;
	}
	float obj_real_size = calRealSize(pixe_size, pixe_num, real_dis, focal_length);
	ui.editSize->setText(QString::number(obj_real_size));


}

void fzqjGetPicSize::updateCurrentStateVi(bool current_state)
{
	if (current_state)
	{
		is_current_vi = true;
		ui.editFocusValue->setText(QString::number(get_vi_focal_length));


	}
}

void fzqjGetPicSize::updateCurrentStateIr(bool current_state)
{
	if (current_state)
	{
		is_current_vi = false;
		ui.editFocusValue->setText(QString::number(get_ir_focal_length));
	}
}

void fzqjGetPicSize::updateFocalLength(int vi_num, int ir_num)
{
	in_vi_focal_length = vi_num;
	in_ir_focal_length = ir_num;
}




void fzqjGetPicSize::on_btnImageRefresh_clicked(void)
{
	if (mat_ir.empty())
	{
		//
	}
	else
	{
		int cols = ui.windShowPicIr->width();
		int rows = ui.windShowPicIr->height();
		cv::resize(mat_ir, scale_image_ir, cv::Size(cols, rows));
		QImage ir_Image = cvMat2Qimage(scale_image_ir);
		ui.windShowPicIr->setPixmap(QPixmap::fromImage(ir_Image));
	}
	if (mat_vi.empty())
	{
		//
	}
	else
	{
		int cols = ui.windShowPicVi->width();
		int rows = ui.windShowPicVi->height();

		cv::resize(mat_vi, scale_image_vi, cv::Size(cols, rows));
		QImage vi_Image = cvMat2Qimage(scale_image_vi);
		ui.windShowPicVi->setPixmap(QPixmap::fromImage(vi_Image));

	}

	get_vi_focal_length = in_vi_focal_length;
	get_ir_focal_length = in_ir_focal_length;
	if (is_current_vi)
	{
		ui.editFocusValue->setText(QString::number(get_vi_focal_length));
	}
	else
	{
		ui.editFocusValue->setText(QString::number(get_ir_focal_length));
	}
}


