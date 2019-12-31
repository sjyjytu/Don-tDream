#ifndef _jyIMAGE_H_
#define _jyIMAGE_H_

#include <atlimage.h>

// 这些是读取TGA图象文件所需的++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <windows.h>

// #include <stdio.h>
// #include "glut.h"
typedef unsigned char	uchar;
typedef unsigned int	uint;
typedef unsigned short  ushort;

#pragma pack ( push,1)   /* 指定按2字节对齐 */  

// These defines are used to tell us about the type of TARGA file it is
#define TGA_RGB		 2		// This tells us it's a normal RGB (really BGR) file
#define TGA_A		 3		// This tells us it's a ALPHA file
#define TGA_RLE		10		// This tells us that the targa is Run-Length Encoded (RLE)

typedef struct
{ // TGA文件格式结构，前12个字节。参考TGA格式说明
	uchar	descLen;	//0 
	uchar	cmapType;	//0
	uchar	imageType;	// 2--未压缩图像，10压缩图像
	short	cmapStart;
	ushort	cmapEntries;
	uchar	cmapBits;
	ushort	xOffset;
	ushort	yOffset;
}Header;

typedef struct
{ // TGA文件格式结构，共18个字节。参考TGA格式说明
	Header			head;	// 前12字节
	ushort	width;	// 图像宽度
	ushort	height; // 图像高度
	uchar	bpp;	// 每点位数，24或32位
	uchar	attrib;
}TGAHeader;


typedef struct _tTexImage
{
	uchar* imageData;	//图像数据
	uint		width;		//图像宽度
	uint		height;		//图像高度
	uint		bpp;		//像素深度Image color depth in bits per pixel
	uint		imageType;	//24位图像或32位图像
	bool		bCompressed;//是否是压缩格式标志 Compressed or Uncompressed
	_tTexImage() :imageData(NULL) {}
}TexImage;

#pragma pack ( pop )   /* 恢复默认对齐 */  
// TGA定义结束++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


class CjyImage
{
private:
	CImage	img;
	int		m_width;
	int		m_height;
	uint	m_imageType; // 图象数据类型，GL_RGB,GL_RBGA,
	uint	Alignment;
	uchar* pImage; // 图象数据指针
	// 每个像素点占几个字节：=1包括gif 和 BMP256色格式，每个像素占1个字节；<1包括16色和单色BMP文件，每个点占4个bits或1个bit【可通过监视img.GetBPP()观察】；
	// 每个像素占3个字节RGB模式; 每个像素占4个字节RGBA模式
	int		BytePerPixel;
	DWORD* Picdata; // BytePerPixel<=1 时的图象数据指针；
	int		nHasAlpha; // 图象中是否含有ahpha值，如果没有就置0，有就置1,。这样在glTextImage2D(）中的第3个参数可设置为 "GL_RGB + bHasAlpha"

	// 下面是TGA图象操作用
	TexImage texture;

public:
	CjyImage();
	CjyImage(CString filePath);
	~CjyImage();
	int		GetWidth();
	int		GetHeight();
	bool	bIsValid();
	uchar* GetImagePt();
	uint	GetImageType();
	uint	GetAlignment();
	int		CheckAlpha();
private:
	void LoadATL(const CString  filePath);
	//加载TGA图像 
	void LoadTGA(const LPCTSTR filename);
	BOOL LoadUncompressedTGA(TexImage* texture, FILE* file);
	BOOL LoadCompressedTGA(TexImage* texture, FILE* file);
};

#endif