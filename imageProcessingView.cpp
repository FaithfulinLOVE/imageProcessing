// imageProcessingView.cpp: CimageProcessingView 类的实现
//
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include "framework.h"
#include "imageProcessing.h"
#include "imageProcessingDoc.h"
#include "imageProcessingView.h"
#include "_GlobalCommon.h"
#include "GetPixelDlg.h"
#include "SET_PIXEL_DLG.h"
#include "MedianFilterDlg.h"
#include "GaussianFilterDlg.h"
#include "InterpolDlg.h"
#include "BilateralfilterDlg.h"
#include "SharpenDlg.h"
#include "CannyEdgeDlg.h"

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
	InterpolDlg dlg;
	int newWidth = 500;
	int newHeight = 490;
	if (dlg.DoModal() == IDOK) {
		newWidth = dlg.width;
		newHeight = dlg.height;
		char* pNewImage = NULL;
		if (dlg.nearest == -1) {
			/*char buf[100];
			sprintf(buf, "最邻近插值法 %d %d", dlg.nearest, dlg.double_linear);
			AfxMessageBox(buf);*/
			pNewImage = ImageInterpolation(pFileBuf, newWidth, newHeight, 1);
		}
		else {
			/*char buf[100];
			sprintf(buf, "双线性插值法 %d %d", dlg.nearest, dlg.double_linear);
			AfxMessageBox(buf);*/
			pNewImage = ImageInterpolation(pFileBuf, newWidth, newHeight, 0);
		}
		delete[] pFileBuf;
		pFileBuf = pNewImage;
		Invalidate();
		UpdateWindow();
	}
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

	// 获取文件头和图像信息
	BITMAPFILEHEADER* pFileHeader = (BITMAPFILEHEADER*)pFileBuf;
	BITMAPINFOHEADER* pDIBInfo = (BITMAPINFOHEADER*)(pFileBuf + sizeof(BITMAPFILEHEADER));
	int width = pDIBInfo->biWidth;
	int height = abs(pDIBInfo->biHeight);
	int bpp = GetColorBits(pFileBuf);
	int colorBits = pDIBInfo->biBitCount;
	bool isGray = (bpp == 8);
	//if (isGray) AfxMessageBox("isGray!");

	// 确定高斯核的参数
	int kernelSize = 5;  // 常见的大小
	double sigma = 1.0;  // 标准差

	GaussianFilterDlg dlg;
	if (dlg.DoModal() == IDOK) {
		sigma = dlg.sigma;
	}
	// 创建高斯核
	std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize));
	double sum = 0.0;
	int kHalf = kernelSize / 2;
	for (int i = 0; i < kernelSize; i++) {
		for (int j = 0; j < kernelSize; j++) {
			double x = i - kHalf;
			double y = j - kHalf;
			kernel[i][j] = exp(-(x * x + y * y) / (2 * sigma * sigma));
			sum += kernel[i][j];
		}
	}

	// 归一化高斯核
	for (int i = 0; i < kernelSize; i++) {
		for (int j = 0; j < kernelSize; j++) {
			kernel[i][j] /= sum;
		}
	}

	// 创建新的图像缓冲区
	char* pNewBmpFileBuf = new char[pFileHeader->bfSize];
	memcpy(pNewBmpFileBuf, pFileBuf, pFileHeader->bfSize);

	// 应用高斯平滑
	for (int y = kHalf; y < height - kHalf; y++) {
		for (int x = kHalf; x < width - kHalf; x++) {
			double newR = 0.0, newG = 0.0, newB = 0.0, newValue = 0.0;
			for (int dy = -kHalf; dy <= kHalf; dy++) {
				for (int dx = -kHalf; dx <= kHalf; dx++) {
					RGBQUAD rgb;
					GetPixel(pFileBuf, x + dx, y + dy, &rgb);
					if (isGray) {
						newValue += rgb.rgbRed * kernel[dy + kHalf][dx + kHalf];
					}
					else {
						newB += rgb.rgbBlue * kernel[dy + kHalf][dx + kHalf];
						newG += rgb.rgbGreen * kernel[dy + kHalf][dx + kHalf];
						newR += rgb.rgbRed * kernel[dy + kHalf][dx + kHalf];
					}
				}
			}
			if (isGray) {
				/*char buf[100];
				sprintf(buf, "newValue = %.2f", newValue);
				AfxMessageBox(buf);*/
				BYTE newGrayValue = (BYTE)min(max((int)newValue, 0), 255);
				RGBQUAD newRgb = { newGrayValue, newGrayValue, newGrayValue, newGrayValue };	//Error: fourth value needs to be set!(GrayScale image)
				SetPixel(pNewBmpFileBuf, x, y, newRgb);
			}
			else {
				RGBQUAD newRgb = {
				(BYTE)min(max((int)newB, 0), 255),
				(BYTE)min(max((int)newG, 0), 255),
				(BYTE)min(max((int)newR, 0), 255)
				};
				SetPixel(pNewBmpFileBuf, x, y, newRgb);
			}
		}
	}

	// 释放旧的图像缓冲区，使用新的高斯平滑处理后的图像数据
	delete[] pFileBuf;
	pFileBuf = pNewBmpFileBuf;

	Invalidate();
	UpdateWindow();
}

//Median filtering 中值滤波
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


// 辅助函数：计算高斯权重
float GaussianWeight(float distance, float sigma) {
	return exp(-(distance * distance) / (2 * sigma * sigma));
}
//Bilateral filtering 双边滤波
void CimageProcessingView::OnImageprocessBilateralfilter()
{
	if (pFileBuf == NULL) return;

	int bpp = GetColorBits(pFileBuf);
	bool isGray = (bpp == 8);

	BITMAPFILEHEADER* pFileHeader = (BITMAPFILEHEADER*)pFileBuf;
	BITMAPINFOHEADER* pDIBInfo = (BITMAPINFOHEADER*)(pFileBuf + sizeof(BITMAPFILEHEADER));
	int orgWidth = pDIBInfo->biWidth;
	int orgHeight = abs(pDIBInfo->biHeight);

	char* pNewBmpFileBuf = new char[pFileHeader->bfSize];
	memcpy(pNewBmpFileBuf, pFileBuf, pFileHeader->bfSize);

	// Bilateral filtering parameters
	float spatialSigma = 2.0f;  // 空间标准差
	float intensitySigma = 50.0f; // 灰度值差异标准差
	int filterSize = 5; // 滤波器大小

	BilateralfilterDlg dlg;
	if (dlg.DoModal() == IDOK) {
		spatialSigma = dlg.sigma_d;
		intensitySigma = dlg.sigma_R;
	}

	// 对每个像素应用双边滤波
	for (int y = 0; y < orgHeight; y++) {
		for (int x = 0; x < orgWidth; x++) {
			float filteredValueR = 0.0f;//彩色
			float filteredValueG = 0.0f;
			float filteredValueB = 0.0f;
			float filteredValue = 0.0f;	//灰度
			float sumWeights = 0.0f;

			for (int j = -filterSize / 2; j <= filterSize / 2; j++) {
				for (int i = -filterSize / 2; i <= filterSize / 2; i++) {
					// 获取当前像素的空间距离
					float spatialDist = sqrt(i * i + j * j);

					// 若为灰度图像
					if (bpp == 8) {
						// 获取当前像素的灰度值差异
						RGBQUAD currentPixel, neighborPixel;
						GetPixel(pFileBuf, x, y, &currentPixel);
						GetPixel(pFileBuf, x + i, y + j, &neighborPixel);
						float intensityDist = abs(currentPixel.rgbBlue - neighborPixel.rgbBlue);

						// 计算空间权重和灰度值权重
						float spatialWeight = GaussianWeight(spatialDist, spatialSigma);
						float intensityWeight = GaussianWeight(intensityDist, intensitySigma);

						// 计算总权重
						float weight = spatialWeight * intensityWeight;

						// 更新滤波后的像素值和权重和
						filteredValue += neighborPixel.rgbBlue * weight;
						sumWeights += weight;
					}
					else {
						//若为彩色图像
						// 获取当前像素的颜色值差异（三个通道）
						RGBQUAD currentPixel, neighborPixel;
						GetPixel(pFileBuf, x, y, &currentPixel);
						GetPixel(pFileBuf, x + i, y + j, &neighborPixel);
						float intensityDistR = abs(currentPixel.rgbRed - neighborPixel.rgbRed);
						float intensityDistG = abs(currentPixel.rgbGreen - neighborPixel.rgbGreen);
						float intensityDistB = abs(currentPixel.rgbBlue - neighborPixel.rgbBlue);

						// 计算空间权重和颜色值权重（三个通道分别计算）
						float spatialWeight = GaussianWeight(spatialDist, spatialSigma);
						float intensityWeightR = GaussianWeight(intensityDistR, intensitySigma);
						float intensityWeightG = GaussianWeight(intensityDistG, intensitySigma);
						float intensityWeightB = GaussianWeight(intensityDistB, intensitySigma);

						// 计算总权重
						float weight = spatialWeight * intensityWeightR * intensityWeightG * intensityWeightB;

						// 更新滤波后的像素值和权重和（三个通道分别计算）
						filteredValueR += neighborPixel.rgbRed * weight;
						filteredValueG += neighborPixel.rgbGreen * weight;
						filteredValueB += neighborPixel.rgbBlue * weight;
						sumWeights += weight;
					}
					
					
				}
			}

			// 计算最终的像素值
			if (bpp == 8) {
				filteredValue /= sumWeights;

				// 将结果限制在[0, 255]范围内
				filteredValue = max(filteredValue, 0.0f);
				filteredValue = min(filteredValue, 255.0f);

				RGBQUAD filteredPixel;
				filteredPixel.rgbBlue = filteredValue;
				filteredPixel.rgbGreen = filteredValue;
				filteredPixel.rgbRed = filteredValue;
				filteredPixel.rgbReserved = filteredValue;
				SetPixel(pNewBmpFileBuf, x, y, filteredPixel);
			}
			else {
				// 彩色图像三个通道分别计算）
				filteredValueR /= sumWeights;
				filteredValueG /= sumWeights;
				filteredValueB /= sumWeights;

				// 将结果限制在[0, 255]范围内
				filteredValueR = max(filteredValueR, 0.0f);
				filteredValueR = min(filteredValueR, 255.0f);
				filteredValueG = max(filteredValueG, 0.0f);
				filteredValueG = min(filteredValueG, 255.0f);
				filteredValueB = max(filteredValueB, 0.0f);
				filteredValueB = min(filteredValueB, 255.0f);

				// 更新图像数据（三个通道分别处理）
				RGBQUAD filteredPixel;
				filteredPixel.rgbRed = filteredValueR;
				filteredPixel.rgbGreen = filteredValueG;
				filteredPixel.rgbBlue = filteredValueB;
				filteredPixel.rgbReserved = 255; // 保留通道设为255
				SetPixel(pNewBmpFileBuf, x, y, filteredPixel);
			}
		}
	}

	// 更新输出
	delete[] pFileBuf;
	pFileBuf = pNewBmpFileBuf;

	Invalidate();
	UpdateWindow();
}

//Histogram equalization 直方图均衡化
void CimageProcessingView::OnImageprocessHistoequalization()
{
	if (pFileBuf == NULL) return;
	//if (GetColorBits(pFileBuf) != 8) return;//只处理灰度图像

	int width = GetImageWidth(pFileBuf);
	int height = GetImageHeight(pFileBuf);
	int bpp = GetColorBits(pFileBuf);

	//1. 遍历像素点，统计每个灰度值的像素点个数
	int grayScale[300] = { 0 };
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			RGBQUAD rgb;
			bool isGray;
			long offset = GetPixel(pFileBuf, x, y, &rgb, &isGray);
			if (offset >= 0 && isGray) {
				int grayValue = rgb.rgbRed;	//三个通道值相等
				grayScale[grayValue]++;
			}
		}
	}
	//2. 得到直方图，计算累计直方图
	int totNum = height * width;//像素点个数
	double his[300] = {0};
	for (int i = 0; i <= 255; i++) his[i] = (double)grayScale[i] / totNum;//原始直方图
	for (int i = 1; i <= 255; i++) his[i] += his[i-1];//累计直方图

	//3. 计算旧灰度值i对应的新灰度值newScale[i]
	int newScale[300] = { 0 };
	for (int i = 0; i <= 255; i++) newScale[i] = his[i] * 255;

	//4, 更新像素点并输出
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			RGBQUAD rgb;
			bool isGray;
			long offset = GetPixel(pFileBuf, x, y, &rgb, &isGray);
			rgb.rgbReserved = newScale[rgb.rgbReserved];
			SetPixel(pFileBuf, x, y, rgb);
		}
	}

	Invalidate();
	UpdateWindow();
}

//Sharpening by gradient
//实现基于梯度的图像锐化，所需参数从对话框中获取，将锐化结果显示出来。
void CimageProcessingView::OnImageprocessSharpengrad() {
	if (pFileBuf == NULL) return;

	BITMAPFILEHEADER* pFileHeader = (BITMAPFILEHEADER*)pFileBuf;
	BITMAPINFOHEADER* pDIBInfo = (BITMAPINFOHEADER*)(pFileBuf + sizeof(BITMAPFILEHEADER));
	int orgWidth = pDIBInfo->biWidth;
	int orgHeight = abs(pDIBInfo->biHeight);
	int colorBits = pDIBInfo->biBitCount;

	int mask[3][3] = { { -1, -1, -1 }, { -1, 8, -1 }, { -1, -1, -1 } }; //定义锐化卷积核

	char* pNewBmpFileBuf = new char[pFileHeader->bfSize];
	char* pResultBmpFileBuf = new char[pFileHeader->bfSize];
	memcpy(pNewBmpFileBuf, pFileBuf, pFileHeader->bfSize);
	memcpy(pResultBmpFileBuf, pFileBuf, pFileHeader->bfSize);

	//input parameters
	SharpenDlg dlg;
	double k1 = 1, k2 = 1;
	if (dlg.DoModal() == IDOK) {
		k1 = dlg.k1;
		k2 = dlg.k2;
	}

	for (int y = 1; y < orgHeight - 1; y++) {
		for (int x = 1; x < orgWidth - 1; x++) {
			RGBQUAD rgb;
			GetPixel(pFileBuf, x, y, &rgb);

			int sumR = 0, sumG = 0, sumB = 0;
			for (int dy = -1; dy <= 1; dy++) {
				for (int dx = -1; dx <= 1; dx++) {
					RGBQUAD pixel;
					GetPixel(pFileBuf, x + dx, y + dy, &pixel);

					sumR += mask[dy + 1][dx + 1] * pixel.rgbRed;
					sumG += mask[dy + 1][dx + 1] * pixel.rgbGreen;
					sumB += mask[dy + 1][dx + 1] * pixel.rgbBlue;
				}
			}

			sumR = min(max(sumR, 0), 255);
			sumG = min(max(sumG, 0), 255);
			sumB = min(max(sumB, 0), 255);

			rgb.rgbRed = sumR;
			rgb.rgbGreen = sumG;
			rgb.rgbBlue = sumB;

			SetPixel(pNewBmpFileBuf, x, y, rgb);

			// 将锐化前和锐化后的像素相加
			RGBQUAD originalRgb;
			GetPixel(pResultBmpFileBuf, x, y, &originalRgb);
			rgb.rgbRed = min(max(k2*rgb.rgbRed + k1*originalRgb.rgbRed, 0), 255);
			rgb.rgbGreen = min(max(k2*rgb.rgbGreen + k1*originalRgb.rgbGreen, 0), 255);
			rgb.rgbBlue = min(max(k2*rgb.rgbBlue + k1*originalRgb.rgbBlue, 0), 255);

			SetPixel(pResultBmpFileBuf, x, y, rgb);
		}
	}

	delete[] pFileBuf;
	pFileBuf = pResultBmpFileBuf;

	delete[] pNewBmpFileBuf;

	Invalidate();
	UpdateWindow();
}


struct Pixel {
	int x;
	int y;
};
// 创建一个队列来存储待拓展的像素点
std::queue<Pixel> pixelQueue;

//Canny edge detection		Limit:300x300!
void CimageProcessingView::OnImageprocessCannyedge()
{
	if (pFileBuf == NULL) return;

	//1. 高斯滤波
	CimageProcessingView::OnImageprocessGausssmooth();
	AfxMessageBox("高斯滤波完成");

	int width = GetImageWidth(pFileBuf);
	int height = GetImageHeight(pFileBuf);
	int bpp = GetColorBits(pFileBuf);

	int sobelOperatorX[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	int sobelOperatorY[3][3] = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };
	int gra_x[300][300] = { 0 };
	int gra_y[300][300] = { 0 };
	
	//2. 计算dx、dy 得到梯度
	double max_grad = 0.0;
	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {
			int dx = 0;
			int dy = 0;
			// dx
			for (int j = -1; j <= 1; j++) {
				for (int i = -1; i <= 1; i++) {
					RGBQUAD neighborPixel;
					bool isGray;
					GetPixel(pFileBuf, x + i, y + j, &neighborPixel, &isGray);
					int grayValue = neighborPixel.rgbRed; // 灰度

					dx += grayValue * sobelOperatorX[j + 1][i + 1];
				}
			}

			// dy
			for (int j = -1; j <= 1; j++) {
				for (int i = -1; i <= 1; i++) {
					RGBQUAD neighborPixel;
					bool isGray;
					GetPixel(pFileBuf, x + i, y + j, &neighborPixel, &isGray);
					int grayValue = neighborPixel.rgbRed; // 灰度

					dy += grayValue * sobelOperatorY[j + 1][i + 1];
				}
			}

			// 梯度gra:dx、dy,归一化
			double gra = sqrt(dx * dx + dy * dy);
			if (gra > max_grad) max_grad = gra;

			/*char buf[100];
			sprintf(buf, "threshold = %.2f", gra);
			AfxMessageBox(buf);*/
			
			gra_x[x][y] = dx;
			gra_y[x][y] = dy;
		}
	}

	//3. 得到梯度方向的两个像素点，比较，决定是否保留中心点s
	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {
			
			double angle = atan2(gra_x[x][y], gra_y[x][y]);

			int x1 = x + cos(angle);
			int y1 = y + sin(angle);

			int x2 = x - cos(angle);
			int y2 = y - sin(angle);

			double gra0 = sqrt(gra_x[x][y] * gra_x[x][y] + gra_y[x][y] * gra_y[x][y]);
			double gra1 = sqrt(gra_x[x1][y1] * gra_x[x1][y1] + gra_y[x1][y1] * gra_y[x1][y1]);
			double gra2 = sqrt(gra_x[x2][y2] * gra_x[x2][y2] + gra_y[x2][y2] * gra_y[x2][y2]);
			if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
				if (gra0 < gra1) gra_x[x][y] = gra_y[x][y] = 0;
			}
			if (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height) {
				if (gra0 < gra2) gra_x[x][y] = gra_y[x][y] = 0;
			}
		}
	}

	//4. 得到图像2，读入阈值，对图像1和图像2分别作阈值处理
	int imageSize = width * height * sizeof(RGBQUAD);
	char* pFileBuf2 = new char[width * height * (bpp / 8)];
	memcpy(pFileBuf2, pFileBuf, width * height * (bpp / 8));

	double th1=0.1, th2=0.3;
	CannyEdgeDlg dlg;
	if (dlg.DoModal() == IDOK) {
		th2 = dlg.th2;
		th1 = dlg.th1;
	}
	//th1 = 0.4 * th2;

	//图像1
	//RGBQUAD rgb0 = { 0,0,0,0 };
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double grad = sqrt(gra_x[x][y] * gra_x[x][y] + gra_y[x][y] * gra_y[x][y]);
			if (grad/max_grad < th1) {
				RGBQUAD rgb;
				bool isGray;
				long offset = GetPixel(pFileBuf, x, y, &rgb, &isGray);
				rgb.rgbReserved = 0;
				SetPixel(pFileBuf, x, y, rgb);
			}
		}
	}

	/*Invalidate();
	UpdateWindow();
	AfxMessageBox("图像1");*/
	
	//图像2
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double grad = sqrt(gra_x[x][y] * gra_x[x][y] + gra_y[x][y] * gra_y[x][y]);
			if (grad/max_grad < th2) {
				RGBQUAD rgb;
				bool isGray;
				long offset = GetPixel(pFileBuf2, x, y, &rgb, &isGray);
				rgb.rgbReserved = 0;
				SetPixel(pFileBuf2, x, y, rgb);
			}
		}
	}

	/*char* tmp = pFileBuf;
	pFileBuf = pFileBuf2;
	Invalidate();
	UpdateWindow();
	AfxMessageBox("图像2");
	pFileBuf = tmp;*/

	//5. 边缘链接
	bool checked[300][300] = {0};
	int stepx[8] = { -1,0,1,-1,1,-1,0,1 };
	int stepy[8] = { -1,-1,-1,0,0,1,1,1 };
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			//已经拓展过
			if (checked[x][y]) continue;
			
			//如果图2中是边缘点，开始拓展
			RGBQUAD rgb2;
			bool isGray;
			long offset = GetPixel(pFileBuf, x, y, &rgb2, &isGray);
			if (rgb2.rgbReserved == 0) continue;
			//DFS(x, y, pFileBuf, pFileBuf2);
			
			//创建一个队列v，队列中元素是一对int值
			//初始化，(x,y)入队 
			Pixel startPixel = { x, y };
			pixelQueue.push(startPixel);

			int xx = -1, yy = -1;

			//DFS
			while (!pixelQueue.empty()) {
				//取出队首元素赋值给xx和yy
				Pixel currentPixel = pixelQueue.front();
				pixelQueue.pop();

				int xx = currentPixel.x;
				int yy = currentPixel.y;

				checked[xx][yy] = true;

				//向八个方向拓展
				for (int st = 0; st < 8; st++) {
					int gox = xx + stepx[st];
					int goy = yy + stepy[st];
					if (checked[gox][goy]) continue;
					
					//如果它在图2中本身是边缘点那就不管了，之后会拓展的
					RGBQUAD rgb2;
					bool isGray;
					GetPixel(pFileBuf, x, y, &rgb2, &isGray);
					if (rgb2.rgbReserved != 0) continue;

					//取出图1中的点值，如果不为0，说明需要拓展
					RGBQUAD rgb1;
					GetPixel(pFileBuf, x, y, &rgb1, &isGray);
					if (rgb1.rgbReserved == 0) continue;

					//拓展！
					SetPixel(pFileBuf2, gox, goy, rgb1);
					//增加入队代码,将gox、goy入队
					Pixel newPixel = { gox, goy };
					pixelQueue.push(newPixel);
				}
			}
		}
	}

	//释放旧的图像缓冲区，使用新的图像数据
	delete[] pFileBuf;
	pFileBuf = pFileBuf2;
	Invalidate();
	UpdateWindow();
}

//Otsu segmentation
void CimageProcessingView::OnImageprocessOtsusegment()
{
	if (pFileBuf == NULL) return;

	int width = GetImageWidth(pFileBuf);
	int height = GetImageHeight(pFileBuf);
	int bpp = GetColorBits(pFileBuf);
	//if (bpp != 8) return;//只处理灰度图像
	double threshold = 0.0;
	double average = 0.0;
	double variance = 0.0;

	//1. 遍历像素点，统计每个灰度值的像素点个数
	int grayScale[300] = { 0 };
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			RGBQUAD rgb;
			bool isGray;
			long offset = GetPixel(pFileBuf, x, y, &rgb, &isGray);
			if (offset >= 0 && isGray) {
				int grayValue = rgb.rgbRed;	//三个通道值相等
				grayScale[grayValue]++;
			}
		}
	}

	//2. 得到灰度直方图
	int totNum = height * width;//像素点个数
	double his[300] = { 0 };
	for (int i = 0; i <= 255; i++) his[i] = (double)grayScale[i] / totNum;//原始直方图

	//3.计算灰度图像的平均值和方差
	for (int i = 0; i <= 255; i++) average += i * his[i];
	for (int i = 0; i <= 255; i++) variance += (i - average) * (i - average) * his[i];

	//4.计算类方差阈值
	double k = 0.3; // 系数 k，再调整？
	threshold = average + k * sqrt(variance);


	//5. 遍历像素点，根据阈值更新像素点为极值
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			RGBQUAD rgb;
			bool isGray;
			long offset = GetPixel(pFileBuf, x, y, &rgb, &isGray);
			if (rgb.rgbRed > threshold)	rgb.rgbReserved = 255;
			else						rgb.rgbReserved = 0;
			SetPixel(pFileBuf, x, y, rgb);
		}
	}

	//输出阈值（弹窗）和处理后图片
	Invalidate();
	UpdateWindow();

	char buf[100];
	sprintf(buf, "threshold = %f", threshold);
	AfxMessageBox(buf);
}
