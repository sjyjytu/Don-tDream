#ifndef _jyIMAGE_H_
#define _jyIMAGE_H_

#include <atlimage.h>

// ��Щ�Ƕ�ȡTGAͼ���ļ������++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <windows.h>

// #include <stdio.h>
// #include "glut.h"
typedef unsigned char	uchar;
typedef unsigned int	uint;
typedef unsigned short  ushort;

#pragma pack ( push,1)   /* ָ����2�ֽڶ��� */  

// These defines are used to tell us about the type of TARGA file it is
#define TGA_RGB		 2		// This tells us it's a normal RGB (really BGR) file
#define TGA_A		 3		// This tells us it's a ALPHA file
#define TGA_RLE		10		// This tells us that the targa is Run-Length Encoded (RLE)

typedef struct
{ // TGA�ļ���ʽ�ṹ��ǰ12���ֽڡ��ο�TGA��ʽ˵��
	uchar	descLen;	//0 
	uchar	cmapType;	//0
	uchar	imageType;	// 2--δѹ��ͼ��10ѹ��ͼ��
	short	cmapStart;
	ushort	cmapEntries;
	uchar	cmapBits;
	ushort	xOffset;
	ushort	yOffset;
}Header;

typedef struct
{ // TGA�ļ���ʽ�ṹ����18���ֽڡ��ο�TGA��ʽ˵��
	Header			head;	// ǰ12�ֽ�
	ushort	width;	// ͼ����
	ushort	height; // ͼ��߶�
	uchar	bpp;	// ÿ��λ����24��32λ
	uchar	attrib;
}TGAHeader;


typedef struct _tTexImage
{
	uchar* imageData;	//ͼ������
	uint		width;		//ͼ����
	uint		height;		//ͼ��߶�
	uint		bpp;		//�������Image color depth in bits per pixel
	uint		imageType;	//24λͼ���32λͼ��
	bool		bCompressed;//�Ƿ���ѹ����ʽ��־ Compressed or Uncompressed
	_tTexImage() :imageData(NULL) {}
}TexImage;

#pragma pack ( pop )   /* �ָ�Ĭ�϶��� */  
// TGA�������++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


class CjyImage
{
private:
	CImage	img;
	int		m_width;
	int		m_height;
	uint	m_imageType; // ͼ���������ͣ�GL_RGB,GL_RBGA,
	uint	Alignment;
	uchar* pImage; // ͼ������ָ��
	// ÿ�����ص�ռ�����ֽڣ�=1����gif �� BMP256ɫ��ʽ��ÿ������ռ1���ֽڣ�<1����16ɫ�͵�ɫBMP�ļ���ÿ����ռ4��bits��1��bit����ͨ������img.GetBPP()�۲졿��
	// ÿ������ռ3���ֽ�RGBģʽ; ÿ������ռ4���ֽ�RGBAģʽ
	int		BytePerPixel;
	DWORD* Picdata; // BytePerPixel<=1 ʱ��ͼ������ָ�룻
	int		nHasAlpha; // ͼ�����Ƿ���ahphaֵ�����û�о���0���о���1,��������glTextImage2D(���еĵ�3������������Ϊ "GL_RGB + bHasAlpha"

	// ������TGAͼ�������
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
	//����TGAͼ�� 
	void LoadTGA(const LPCTSTR filename);
	BOOL LoadUncompressedTGA(TexImage* texture, FILE* file);
	BOOL LoadCompressedTGA(TexImage* texture, FILE* file);
};

#endif