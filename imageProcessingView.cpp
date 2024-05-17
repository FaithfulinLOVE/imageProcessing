// imageProcessingView.cpp: CimageProcessingView 类的实现
//
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <algorithm>
#include <cmath>
#include "framework.h"
#include "imageProcessing.h"
#include "imageProcessingDoc.h"
#include "imageProcessingView.h"
#include "_GlobalCommon.h"
#include "GetPixelDlg.h"
#include "SET_PIXEL_DLG.h"
#include "MedianFilterDlg.h"
#include "GaussianFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CimageProcessingView, CView)

BEGIN_MESSAGE_MAP(CimageProcessingView, CView)
	ON_COMMAND(ID_IMAGEPROCESS_OPENBMPFILE, &CimageProcessingView::OnImageprocessOpenbmpfile)
	ON_COMMAND(ID_IMAGEPROCESS_SAVETOFILE, &CimageProcessingView::OnImageprocessSavetofile)
	ON_COMMAND(ID_IMAGEPROCESS_DISPLAYFILEHEADER, &CimageProcessingView::OnImageprocessDisplayfileheader)
	ON_COMMAND(ID_IMAGEPROCESS_DISPLAYPALETTE, &CimageProcessingView::OnImageprocessDisplaypalette)
	ON_COMMAND(ID_IMAGEPROCESS_GETPIXELVALUE, &CimageProcessingView::OnImageprocessGetpixelvalue)
	ON_COMMAND(ID_IMAGEPROCESS_SETPIXELVALUE, &CimageProcessingView::OnImageprocessSetpixelvalue)
	ON_COMMAND(ID_IMAGEPROCESS_INERPOLATION, &CimageProcessingView::OnImageprocessInerpolation)
	ON_COMMAND(ID_IMAGEPROCESS_GAUSSSMOOTH, &CimageProcessingView::OnImageprocessGausssmooth)
	ON_COMMAND(ID_IMAGEPROCESS_MEDIANFILTER, &CimageProcessingView::OnImageprocessMedianfilter)
	ON_COMMAND(ID_IMAGEPROCESS_BILATERALFILTER, &CimageProcessingView::OnImageprocessBilateralfilter)
	ON_COMMAND(ID_IMAGEPROCESS_HISTOEQUALIZATION, &CimageProcessingView::OnImageprocessHistoequalization)
	ON_COMMAND(ID_IMAGEPROCESS_SHARPENGRAD, &CimageProcessingView::OnImageprocessSharpengrad)
	ON_COMMAND(ID_IMAGEPROCESS_CANNYEDGE, &CimageProcessingView::OnImageprocessCannyedge)
	ON_COMMAND(ID_IMAGEPROCESS_OTSUSEGMENT, &CimageProcessingView::OnImageprocessOtsusegment)
END_MESSAGE_MAP()

CimageProcessingView::CimageProcessingView() noexcept
{
	pFileBuf = NULL;
}

CimageProcessingView::~CimageProcessingView()
{
	if( pFileBuf ) 
	{
		delete [] pFileBuf;
		pFileBuf = 0;
	}
}

BOOL CimageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CimageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CimageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CimageProcessingDoc *CimageProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CimageProcessingDoc)));
	return (CimageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

// CimageProcessingView 绘图
void CimageProcessingView::OnDraw(CDC *pDC)
{
	CimageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if( pFileBuf != NULL )
	{
		DisplayImage(pDC,pFileBuf,10,10,0,0,0);
	}
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//Here are the functions to be programmed by you!

//Open a BMP file
void CimageProcessingView::OnImageprocessOpenbmpfile()
{
	LPCTSTR lpszFilter = "BMP Files (*.bmp)|*.bmp||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_NOCHANGEDIR,lpszFilter,NULL);
	if( dlg.DoModal() != IDOK ) return;
	if( pFileBuf != NULL )
	{
		delete [] pFileBuf;
	}
	pFileBuf = OpenBMPfile( dlg.GetPathName() );
	Invalidate();
	UpdateWindow();
}

//Save to a new BMP file
void CimageProcessingView::OnImageprocessSavetofile()
{
	if(pFileBuf == NULL) return;
	LPCTSTR lpszFilter = _T("Bitmap Files (*.bmp)|*.bmp | All Files (*.*)|*.* ||");
	CFileDialog dlg(FALSE, _T(".bmp"), NULL, OFN_OVERWRITEPROMPT, lpszFilter, NULL); 
	if (dlg.DoModal() != IDOK) return;
	//Add your code to choose the new BMP filename
	CString strBmpFile = dlg.GetPathName();
	SaveDIB(pFileBuf, strBmpFile);
}

//Display BMP file header
void CimageProcessingView::OnImageprocessDisplayfileheader()
{
	if(pFileBuf == NULL) return;
	/**/
	DisplayHeaderMessage(pFileBuf);
}

//Display Pallete
void CimageProcessingView::OnImageprocessDisplaypalette()
{
	if(pFileBuf == NULL) return;
	/**/
	int num = 0;
	RGBQUAD *pallete = GetDIBPaletteData(pFileBuf,&num);
	if( pallete == NULL )
	{
		AfxMessageBox("No palette");
	}
	else
	{
		//Here are your code
		// 顶端显示一串颜色
		CDC* pDC = GetDC();
		for (int i = 0; i < num; i++)
		{
			CBrush brush(RGB(pallete[i].rgbRed, pallete[i].rgbGreen, pallete[i].rgbBlue));
			pDC->SelectObject(&brush);
			pDC->Rectangle(i * 20, 0, (i + 1) * 20, 20);
		}
		ReleaseDC(pDC);
		//输出数据
		CString strPaletteColors;
		for (int i = 0; i < num; i++)
		{
			strPaletteColors.AppendFormat("Palette Color %d - RGB(%d, %d, %d)\n", i + 1, pallete[i].rgbRed, pallete[i].rgbGreen, pallete[i].rgbBlue);
		}
		AfxMessageBox(strPaletteColors);
	}
}

//Get pixel value
void CimageProcessingView::OnImageprocessGetpixelvalue()
{
	if(pFileBuf == NULL) return;
	/**/
	GetPixelDlg dlg;
	int x=100, y=100;
	if (dlg.DoModal() == IDOK) {
		x = dlg.m_nX;
		y = dlg.m_nY;
	}
	//Add your code to choose the coordinate (x,y)
	RGBQUAD rgb;
	bool bGray;
	GetPixel(pFileBuf,x,y,&rgb,&bGray);
	char buf[100];
	if( bGray )
		sprintf(buf, "(%d,%d) = %d",x,y,rgb.rgbReserved);
	else
		sprintf(buf, "(%d,%d) = (%d,%d,%d)",x,y,rgb.rgbRed,rgb.rgbGreen,rgb.rgbBlue);
	AfxMessageBox( buf );
}

//Set pixel value
void CimageProcessingView::OnImageprocessSetpixelvalue()
{
	if(pFileBuf == NULL) return;
	/**/
	SET_PIXEL_DLG dlg;
	int x ;
	int y ;
	RGBQUAD rgb;
	//Add your code to choose the coordinate (x,y)
	if (dlg.DoModal() == IDOK) {
		x = dlg.set_X;
		y = dlg.set_Y;
		rgb.rgbReserved = dlg.set_Res;
		rgb.rgbRed = dlg.set_R;
		rgb.rgbGreen = dlg.set_G;
		rgb.rgbBlue = dlg.set_B;
	}
	SetPixel(pFileBuf,x,y,rgb);
	Invalidate();
	UpdateWindow();
}

//Image interpolaion
void CimageProcessingView::OnImageprocessInerpolation()
{
	if(pFileBuf == NULL) return;
	/**/
	//Add your code to choose method (nearest or bilinear) and zoom factors
	int newWidth  = 500;
	int newHeight = 490;
	char *pNewImage = ImageInterpolation(pFileBuf,newWidth,newHeight,0);
	delete [] pFileBuf;
	pFileBuf = pNewImage;
	Invalidate();
	UpdateWindow();
}

/*
// 功能函数1：应用高斯滤波器
double ApplyGaussianFilter(const std::vector<double>& values, const std::vector<double>& weights) {
	if (values.size() != weights.size()) {
		// 如果值和权重数组的大小不一致，返回0
		return 0.0;
	}

	double result = 0.0;
	for (size_t i = 0; i < values.size(); i++) {
		result += values[i] * weights[i];
	}

	return result;
}
//功能函数2：计算高斯滤波的权重
std::vector<double> GaussianWeights(double sigma, int kernelSize) {
	std::vector<double> weights;
	weights.reserve(kernelSize);

	double sum = 0.0;
	for (int i = 0; i < kernelSize; i++) {
		int x = i - kernelSize / 2;
		double weight = exp(-(x * x) / (2 * sigma * sigma));
		weights.push_back(weight);
		sum += weight;
	}

	// 归一化权重
	for (int i = 0; i < kernelSize; i++) {
		weights[i] /= sum;
	}

	return weights;
}
*/
//Gaussian smoothing高斯滤波
void CimageProcessingView::OnImageprocessGausssmooth()
{
	if (pFileBuf == NULL) return;

	int width = GetImageWidth(pFileBuf);
	int height = GetImageHeight(pFileBuf);
	int bpp = GetColorBits(pFileBuf);

	// 创建一个新的图像缓冲区用于存储高斯平滑后的图像
	char* pNewImage = new char[width * height * (bpp / 8)];
	memcpy(pNewImage, pFileBuf, width * height * (bpp / 8));

	// 设置高斯平滑的参数
	GaussianFilterDlg dlg;
	double sigma = 1.0;
	double kernelSize = 2 * sigma + 1;
	if (dlg.DoModal() == IDOK) {
		sigma = dlg.sigma;
		kernelSize = 2 * sigma + 1;
	}

	// 对图像进行高斯平滑处理
	double kernelRadius = kernelSize / 2;
	double* kernel = new double[kernelSize];
	double sum = 0.0;

	// 生成高斯核
	for (int i = 0; i < kernelSize; i++) {
		double x = i - kernelRadius;
		kernel[i] = exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * 3.14159265358979323846) * sigma);
		sum += kernel[i];
	}

	// 归一化高斯核
	for (int i = 0; i < kernelSize; i++) {
		kernel[i] /= sum;
	}

	// 对图像进行高斯平滑处理
	// 对图像进行高斯平滑处理
	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {
			for (int c = 0; c < bpp / 8; c++) {
				double sum = 0.0;
				//double totalWeight = 0.0;	//归一化，防止图像饱和度变高
				for (int j = -1; j <= 1; j++) {
					for (int i = -1; i <= 1; i++) {
						int index = ((y + j) * width + (x + i)) * (bpp / 8) + c;
						double weight = exp(-(i * i + j * j) / (2 * sigma * sigma));
						sum += pFileBuf[index] * weight;
						//totalWeight += weight;
					}
				}
				pNewImage[(y * width + x) * (bpp / 8) + c] = sum / (2 * 3.14159 * sigma * sigma);
				//pNewImage[(y * width + x) * (bpp / 8) + c] = (char)(sum / totalWeight);
			}
		}
	}


	// 释放旧的图像缓冲区，使用新的高斯平滑处理后的图像数据
	delete[] pFileBuf;
	pFileBuf = pNewImage;

	Invalidate();
	UpdateWindow();
}

//Median filtering
void CimageProcessingView::OnImageprocessMedianfilter()
{
	if (pFileBuf == NULL) return;
	/**/
	int width = GetImageWidth(pFileBuf);
	int height = GetImageHeight(pFileBuf);
	int bpp = GetColorBits(pFileBuf);
	
	// Check if the image is grayscale
	bool isGrayscale = (bpp == 8); // Assuming 8-bit grayscale image

	//创建一个新的图像缓冲区用于存储中值滤波后的图像
	char* pNewImage = new char[width * height * (bpp / 8)];
	memcpy(pNewImage, pFileBuf, width * height * (bpp / 8));

	//设置中值滤波器的窗口大小
	MedianFilterDlg dlg;
	int windowSize = 3;
	if (dlg.DoModal() == IDOK) {
		windowSize = dlg.winSize;
	}

	/*if (isGrayscale) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				std::vector<char> windowValues;

				// 构建窗口
				for (int wy = -windowSize / 2; wy <= windowSize / 2; wy++) {
					for (int wx = -windowSize / 2; wx <= windowSize / 2; wx++) {
						int nx = std::max(0, std::min(width - 1, x + wx));
						int ny = std::max(0, std::min(height - 1, y + wy));
						windowValues.push_back(pFileBuf[ny * width + nx]);
					}
				}

				// 对窗口内像素值进行排序
				std::sort(windowValues.begin(), windowValues.end());

				// 取中值作为当前像素的值
				pNewImage[y * width + x] = windowValues[windowSize * windowSize / 2];
			}
		}

		//释放旧的图像缓冲区，使用新的中值滤波处理后的图像数据
		delete[] pFileBuf;
		pFileBuf = pNewImage;

		Invalidate();
		UpdateWindow();
		return;
	}*/
	//对图像进行中值滤波处理
	for (int y = windowSize / 2; y < height - windowSize / 2; y++)
	{
		for (int x = windowSize / 2; x < width - windowSize / 2; x++)
		{
			std::vector<unsigned char> valuesR;
			std::vector<unsigned char> valuesG;
			std::vector<unsigned char> valuesB;

			//获取窗口内像素值
			for (int j = -windowSize / 2; j <= windowSize / 2; j++)
			{
				for (int i = -windowSize / 2; i <= windowSize / 2; i++)
				{
					int pixelIndex = ((y + j) * width + (x + i)) * (bpp / 8);
					valuesR.push_back(pFileBuf[pixelIndex + 2]); //红色通道
					valuesG.push_back(pFileBuf[pixelIndex + 1]); //绿色通道
					valuesB.push_back(pFileBuf[pixelIndex]); //蓝色通道
				}
			}

			//对窗口内像素值进行排序
			std::sort(valuesR.begin(), valuesR.end());
			std::sort(valuesG.begin(), valuesG.end());
			std::sort(valuesB.begin(), valuesB.end());

			//取中值作为新的像素值
			int medianIndex = valuesR.size() / 2;
			int pixelIndex = (y * width + x) * (bpp / 8);
			pNewImage[pixelIndex + 2] = valuesR[medianIndex]; //红色通道
			pNewImage[pixelIndex + 1] = valuesG[medianIndex]; //绿色通道
			pNewImage[pixelIndex] = valuesB[medianIndex]; //蓝色通道
		}
	}


	//释放旧的图像缓冲区，使用新的中值滤波处理后的图像数据
	delete[] pFileBuf;
	pFileBuf = pNewImage;

	Invalidate();
	UpdateWindow();
}

//Bilateral filtering
void CimageProcessingView::OnImageprocessBilateralfilter()
{
}

//Histogram equalization
void CimageProcessingView::OnImageprocessHistoequalization()
{
	
}

//Sharpening by gradient
void CimageProcessingView::OnImageprocessSharpengrad()
{

}

//Cany edge detection
void CimageProcessingView::OnImageprocessCannyedge()
{
}

//Otsu segmentation
void CimageProcessingView::OnImageprocessOtsusegment()
{
}
