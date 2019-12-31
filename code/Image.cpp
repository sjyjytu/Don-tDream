#include "jyImage.h"

// ���¶���opengl�еĳ�������ֵ������ȫһ�������������Ϳ��Բ�����glut.h�ȿ���
#define jyGL_RGB		0x1907
#define jyGL_RGBA		0x1908
#define jyGL_BGR_EXT	0x80E0
#define jyGL_BGRA_EXT	0x80E1

CjyImage::CjyImage()
{
	m_width = 0;
	m_height = 0;
	Picdata = NULL;

	// TGAͼ��ָ��
	texture.imageData = NULL;
	nHasAlpha = 0; // Ĭ��ͼ������Ahphaֵ

	m_imageType = 0; // ͼ���������ͣ�GL_RGB,GL_RBGA,
	Alignment = 0;
	BytePerPixel = 0;

}

CjyImage::~CjyImage()
{
	if (Picdata != NULL)
		delete[] Picdata;

	// TGAͼ��ָ��
	if (texture.imageData != NULL)
		delete[] texture.imageData;
}

int CjyImage::GetWidth()
{
	return m_width;
}


int CjyImage::GetHeight()
{
	return m_height;
}

int CjyImage::CheckAlpha()
{
	return nHasAlpha;
}


uchar* CjyImage::GetImagePt()
{
	return pImage;
}

uint CjyImage::GetAlignment()
{
	return Alignment;
}

uint CjyImage::GetImageType()
{
	return m_imageType;
}

bool CjyImage::bIsValid()
{
	if (m_width <= 0 || m_height <= 0)
		return false;
	else
		return true;
}

CjyImage::CjyImage(CString filePath)
{
	m_width = 0;
	m_height = 0;
	Picdata = NULL;
	m_imageType = 0; // ͼ���������ͣ�GL_RGB,GL_RBGA,
	Alignment = 0;
	BytePerPixel = 0;
	nHasAlpha = 0;

	filePath.TrimLeft();
	filePath.TrimRight();

	// ����ļ��Ƿ����---------------------------------------
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	hFind = FindFirstFile(filePath, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);

		// �����ж���ʲô��ʽ��ͼ���ļ��������tga��ʽ�������ö�ȡTga�ļ��ĺ�����������atl������ȡͼ���ļ�
		CString pszExtension = PathFindExtension(filePath); // ��ȡͼƬ�ļ���չ��
		pszExtension.MakeUpper(); // ��չ��ͳһΪ��д��ĸ�����������ж��Ǻ��ָ�ʽ
		if (pszExtension == ".TGA") // TGA��ʽ��ͼƬ��Ҫ����������Ϊalt�е�CImage���ܶ�TGA��ʽ��ͼ��
			LoadTGA(filePath);
		else
			LoadATL(filePath);
	}
}


void CjyImage::LoadATL(const CString  filePath)
{
	img.Load(filePath); //  ͨ��ͼƬ�ļ�����������ͼ��
	m_width = img.GetWidth();
	m_height = img.GetHeight();
	BytePerPixel = img.GetBPP() / 8; // GetBPP�������ÿ������ռ����bits������8�õ��ֽ���

	// ͼ���������� 
	if (BytePerPixel == 4)
	{
		m_imageType = jyGL_BGRA_EXT;
		nHasAlpha = 1;
	}
	else if (BytePerPixel == 3)
		m_imageType = jyGL_BGR_EXT;

	/* ��CImage�У�һ�е������������4byte������������Ҫ��ǿ�Ʋ����4byte���������ġ�
	����һ��355*120�Ĳ�ɫͼƬ����CImage��һ�е�����ƫ������pitch�����ǣ�355*3+3��/4*4 = 1068 byte��
	��width*bitCount = 355*3 = 1065 byte�����Լ���һ�����ص����ڴ��е�λ��ʱ�������ã�y*width+x��*bitCount��Ҫ��y*pitch + x*bitCount��
	GetBpp()�������ص���ͼƬ�������߼��ϵĿ�ʼλ�ã����������ڴ��еĿ�ʼλ�á��ڼ������ص����ڴ�Ŀ�ʼλ��ʱ��Ӧ�����ʹ��GetPitch()������
	���GetPitch()�ķ���ֵС���㣬��ôӦ����GetBpp()������õ����ص��߼���ʼ��ַ�����ϣ�height-1��*pitch��
	*/
	if (img.GetPitch() < 0) //GetBits�����þ��ǻ�������λ��Ϣ������ָ�룬���λͼ�Ǵ��µ��ϣ� ��ָ�򻺳���ĩ�ˣ�����ָ�򻺳����׶ˡ���img.GetPitch ����������ж����ã�С�� 0 ָ��ĩ��
		pImage = (uchar*)img.GetBits() + (img.GetPitch() * (img.GetHeight() - 1));
	else
		pImage = (uchar*)img.GetBits();

	Alignment = 4;
	if (BytePerPixel <= 1) // BytePerPixel=1������� gif��ʽ�� BMP 256ɫ��ʽ��ÿ������ռ1���ֽڣ�BytePerPixel<1,����16ɫ�͵�ɫBMP�ļ���ÿ����ռ4��bits��1��bit����ͨ������img.GetBPP()�۲졿��
	{
		COLORREF color;
		Picdata = new DWORD[img.GetWidth() * img.GetHeight()];
		long k = 0;
		for (int i = img.GetHeight() - 1; i >= 0; i--)
			for (int j = 0; j < img.GetWidth(); j++)
			{
				color = img.GetPixel(j, i);
				Picdata[k++] = color;
			}
		pImage = (uchar*)Picdata;
		m_imageType = jyGL_RGBA;
		nHasAlpha = 0;
		Alignment = 4;
	}
}


//-----------------------------------------------------------------------
// ������    : Image::LoadTGA
// ˵��      : ����TGAͼƬ
// ����      : BOOL 
// ����      : TexImage* texture
// ����      : LPCSTR filename 
// ����      : Teng
// ����ʱ��  : 2010-4-14 15:35:32
// ����޸�  : 2010-4-14
//-----------------------------------------------------------------------
void CjyImage::LoadTGA(LPCTSTR filename)
{

	Header uTGAcompare = { 0, 0, 2, 0, 0, 0, 0, 0 };		//2Ϊ��ѹ��RGB��ʽ		3  -  δѹ���ģ��ڰ�ͼ��
	Header cTGAcompare = { 0, 0, 10, 0, 0, 0, 0, 0 };		//10Ϊѹ��RGB��ʽ

	TGAHeader header;
	FILE* file;
	_wfopen_s(&file, (TCHAR*)filename, L"rb");
	if (fread(&header, 1, sizeof(TGAHeader), file) != sizeof(TGAHeader)) {		//��ȡTGA����ͷ�ṹ��
		if (file)
			fclose(file);
	}

	texture.width = header.width;
	texture.height = header.height;
	texture.bpp = header.bpp;
	BytePerPixel = texture.bpp / 8;

	if (BytePerPixel == 4)
	{
		texture.imageType = jyGL_BGRA_EXT;
		nHasAlpha = 1;
	}
	else if (BytePerPixel = 3)
		texture.imageType = jyGL_BGR_EXT;
	else
		return;

	m_imageType = texture.imageType; // ͼ������ 

	if (header.head.imageType == 2)//δѹ��TGA
	{
		texture.bCompressed = FALSE;
		LoadUncompressedTGA(&texture, file);
	}
	else if (header.head.imageType == 10)//ѹ��TGA
	{
		texture.bCompressed = TRUE;
		LoadCompressedTGA(&texture, file);
	}
	else
		return;

	m_width = texture.width;
	m_height = texture.height;
	pImage = texture.imageData;
	Alignment = 1;
}

//-----------------------------------------------------------------------
// ������    : Image::loadUncompressedTGA
// ˵��      : ����δѹ��TGA����
// ����      : BOOL 
// ����      : TexImage* texture
// ����      : FILE* file		��ǰfileָ�룬ָ��TGAͼ���һ�����ص�ַ
// ����      : Teng
// ����ʱ��  : 2010-4-14 14:39:22
// ����޸�  : 2010-4-14
//-----------------------------------------------------------------------
BOOL CjyImage::LoadUncompressedTGA(TexImage* texture, FILE* file)
{
	uint bytePerPixel = texture->bpp / 8;
	uint imgSize = texture->width * texture->height * bytePerPixel;				//ͼ�����ֽ���
	texture->imageData = new uchar[imgSize];

	if (fread(texture->imageData, 1, imgSize, file) != imgSize)
		return FALSE;

	//TGA��������OpenGL�ĸ�ʽ,Ҫ��BGRת����ΪRGB(or use GL_BGR_EXT verses GL_RGB)
	//	for (int i = 0; i < (int)imgSize; i += bytePerPixel)
	//		texture->imageData[i] ^= texture->imageData[i + 2] ^= texture->imageData[i] ^= texture->imageData[i + 2];		//λ��������ٶ�,����B,R����

	fclose(file);
	return TRUE;
}

//-----------------------------------------------------------------------
// ������    : Image::loadCompressedTGA
// ˵��      : ����ѹ��TGA����
// ����      : BOOL 
// ����      : TexImage* texture
// ����      : FILE* file 
// ����      : Teng
// ����ʱ��  : 2010-4-14 14:38:55
// ����޸�  : 2010-4-14
//-----------------------------------------------------------------------
BOOL CjyImage::LoadCompressedTGA(TexImage* texture, FILE* file)
{
	uint bytePerPixel = texture->bpp / 8;
	uint imgSize = texture->width * texture->height * bytePerPixel;
	texture->imageData = new uchar[imgSize];

	uint pixelcount = texture->width * texture->height;
	uint currentPixel = 0;		//��ǰ���ڶ�ȡ������
	uint currentByte = 0;			//��ǰ������ͼ����д�������
	uchar* colorbuffer = new uchar[bytePerPixel];	// һ�����صĴ洢�ռ�s

	do
	{
		uchar chunkHeader = 0;		//�洢ID��ֵ�ı���
		if (!fread(&chunkHeader, sizeof(uchar), 1, file))
			return FALSE;
		if (chunkHeader < 128)			//RAW��
		{
			chunkHeader++;				// ����ֵ��1�Ի�ȡRAW���ص�����
			for (int i = 0; i < chunkHeader; i++)
			{
				if (fread(colorbuffer, 1, bytePerPixel, file) != bytePerPixel)
					return FALSE;
				texture->imageData[currentByte] = colorbuffer[0];
				texture->imageData[currentByte + 1] = colorbuffer[1];
				texture->imageData[currentByte + 2] = colorbuffer[2];
				if (bytePerPixel == 4)
					texture->imageData[currentByte + 3] = colorbuffer[3];

				currentPixel++;
				currentByte += bytePerPixel;
			}
		}
		else		//��һ�δ�������RLE�εġ��顱ͷ���������ǽ�chunkheader��ȥ127���õ���ȡ��һ����ɫ�ظ��Ĵ����� 
		{
			chunkHeader -= 127;			//��ȥ127���ID bit ��rid	��ʼѭ���������Ƕ�ζ����ڴ��е����أ�����RLEͷ�е�ֵ�涨��
			if (fread(colorbuffer, 1, bytePerPixel, file) != bytePerPixel)
				return FALSE;
			for (int i = 0; i < chunkHeader; i++)
			{
				texture->imageData[currentByte] = colorbuffer[0];			// ������B���ֽ�
				texture->imageData[currentByte + 1] = colorbuffer[1];			// ������G���ֽ�
				texture->imageData[currentByte + 2] = colorbuffer[2];			// ������R���ֽ�
				if (bytePerPixel == 4)
					texture->imageData[currentByte + 3] = colorbuffer[3];			// ������A���ֽ�

				currentPixel++;
				currentByte += bytePerPixel;
			}
		}
	} while (currentPixel < pixelcount);

	fclose(file);
	delete[] colorbuffer;
	return TRUE;
}

