#include "jyImage.h"

// 重新定义opengl中的常量，数值必须完全一样，但这样做就可以不包含glut.h等库了
#define jyGL_RGB		0x1907
#define jyGL_RGBA		0x1908
#define jyGL_BGR_EXT	0x80E0
#define jyGL_BGRA_EXT	0x80E1

CjyImage::CjyImage()
{
	m_width = 0;
	m_height = 0;
	Picdata = NULL;

	// TGA图象指针
	texture.imageData = NULL;
	nHasAlpha = 0; // 默认图象中无Ahpha值

	m_imageType = 0; // 图象数据类型，GL_RGB,GL_RBGA,
	Alignment = 0;
	BytePerPixel = 0;

}

CjyImage::~CjyImage()
{
	if (Picdata != NULL)
		delete[] Picdata;

	// TGA图象指针
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
	m_imageType = 0; // 图象数据类型，GL_RGB,GL_RBGA,
	Alignment = 0;
	BytePerPixel = 0;
	nHasAlpha = 0;

	filePath.TrimLeft();
	filePath.TrimRight();

	// 检查文件是否存在---------------------------------------
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	hFind = FindFirstFile(filePath, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);

		// 首先判断是什么格式的图像文件，如果是tga格式，则利用读取Tga文件的函数，否则用atl方法读取图像文件
		CString pszExtension = PathFindExtension(filePath); // 获取图片文件扩展名
		pszExtension.MakeUpper(); // 扩展名统一为大写字母，方便下面判断是何种格式
		if (pszExtension == ".TGA") // TGA格式的图片需要单独处理，因为alt中的CImage不能读TGA格式的图像
			LoadTGA(filePath);
		else
			LoadATL(filePath);
	}
}


void CjyImage::LoadATL(const CString  filePath)
{
	img.Load(filePath); //  通过图片文件名字来加载图像
	m_width = img.GetWidth();
	m_height = img.GetHeight();
	BytePerPixel = img.GetBPP() / 8; // GetBPP（）获得每个像素占多少bits，除以8得到字节数

	// 图象数据类型 
	if (BytePerPixel == 4)
	{
		m_imageType = jyGL_BGRA_EXT;
		nHasAlpha = 1;
	}
	else if (BytePerPixel == 3)
		m_imageType = jyGL_BGR_EXT;

	/* 在CImage中，一行的数据如果不是4byte的整数倍，是要被强制补足成4byte的整数倍的。
	比如一张355*120的彩色图片，在CImage中一行的数据偏移量（pitch），是（355*3+3）/4*4 = 1068 byte。
	而width*bitCount = 355*3 = 1065 byte。所以计算一个像素点在内存中的位置时，不能用（y*width+x）*bitCount，要用y*pitch + x*bitCount。
	GetBpp()方法返回的是图片数据在逻辑上的开始位置，而不是在内存中的开始位置。在计算像素点在内存的开始位置时，应当结合使用GetPitch()函数，
	如果GetPitch()的返回值小于零，那么应该用GetBpp()方法获得的像素点逻辑开始地址，加上（height-1）*pitch。
	*/
	if (img.GetPitch() < 0) //GetBits的作用就是获得纹理的位信息缓冲区指针，如果位图是从下到上， 则指向缓冲区末端，否则指向缓冲区首端。而img.GetPitch 就是起这个判断作用，小于 0 指向末端
		pImage = (uchar*)img.GetBits() + (img.GetPitch() * (img.GetHeight() - 1));
	else
		pImage = (uchar*)img.GetBits();

	Alignment = 4;
	if (BytePerPixel <= 1) // BytePerPixel=1情况包括 gif格式和 BMP 256色格式，每个像素占1个字节；BytePerPixel<1,包括16色和单色BMP文件，每个点占4个bits或1个bit【可通过监视img.GetBPP()观察】；
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
// 函数名    : Image::LoadTGA
// 说明      : 加载TGA图片
// 返回      : BOOL 
// 参数      : TexImage* texture
// 参数      : LPCSTR filename 
// 作者      : Teng
// 创建时间  : 2010-4-14 15:35:32
// 最后修改  : 2010-4-14
//-----------------------------------------------------------------------
void CjyImage::LoadTGA(LPCTSTR filename)
{

	Header uTGAcompare = { 0, 0, 2, 0, 0, 0, 0, 0 };		//2为非压缩RGB格式		3  -  未压缩的，黑白图像
	Header cTGAcompare = { 0, 0, 10, 0, 0, 0, 0, 0 };		//10为压缩RGB格式

	TGAHeader header;
	FILE* file;
	_wfopen_s(&file, (TCHAR*)filename, L"rb");
	if (fread(&header, 1, sizeof(TGAHeader), file) != sizeof(TGAHeader)) {		//读取TGA整个头结构体
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

	m_imageType = texture.imageType; // 图象类型 

	if (header.head.imageType == 2)//未压缩TGA
	{
		texture.bCompressed = FALSE;
		LoadUncompressedTGA(&texture, file);
	}
	else if (header.head.imageType == 10)//压缩TGA
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
// 函数名    : Image::loadUncompressedTGA
// 说明      : 加载未压缩TGA纹理
// 返回      : BOOL 
// 参数      : TexImage* texture
// 参数      : FILE* file		当前file指针，指向TGA图像第一个像素地址
// 作者      : Teng
// 创建时间  : 2010-4-14 14:39:22
// 最后修改  : 2010-4-14
//-----------------------------------------------------------------------
BOOL CjyImage::LoadUncompressedTGA(TexImage* texture, FILE* file)
{
	uint bytePerPixel = texture->bpp / 8;
	uint imgSize = texture->width * texture->height * bytePerPixel;				//图像总字节数
	texture->imageData = new uchar[imgSize];

	if (fread(texture->imageData, 1, imgSize, file) != imgSize)
		return FALSE;

	//TGA采用了逆OpenGL的格式,要将BGR转换成为RGB(or use GL_BGR_EXT verses GL_RGB)
	//	for (int i = 0; i < (int)imgSize; i += bytePerPixel)
	//		texture->imageData[i] ^= texture->imageData[i + 2] ^= texture->imageData[i] ^= texture->imageData[i + 2];		//位操作提高速度,更换B,R分量

	fclose(file);
	return TRUE;
}

//-----------------------------------------------------------------------
// 函数名    : Image::loadCompressedTGA
// 说明      : 加载压缩TGA纹理
// 返回      : BOOL 
// 参数      : TexImage* texture
// 参数      : FILE* file 
// 作者      : Teng
// 创建时间  : 2010-4-14 14:38:55
// 最后修改  : 2010-4-14
//-----------------------------------------------------------------------
BOOL CjyImage::LoadCompressedTGA(TexImage* texture, FILE* file)
{
	uint bytePerPixel = texture->bpp / 8;
	uint imgSize = texture->width * texture->height * bytePerPixel;
	texture->imageData = new uchar[imgSize];

	uint pixelcount = texture->width * texture->height;
	uint currentPixel = 0;		//当前正在读取的像素
	uint currentByte = 0;			//当前正在向图像中写入的像素
	uchar* colorbuffer = new uchar[bytePerPixel];	// 一个像素的存储空间s

	do
	{
		uchar chunkHeader = 0;		//存储ID块值的变量
		if (!fread(&chunkHeader, sizeof(uchar), 1, file))
			return FALSE;
		if (chunkHeader < 128)			//RAW块
		{
			chunkHeader++;				// 变量值加1以获取RAW像素的总数
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
		else		//下一段处理描述RLE段的“块”头。首先我们将chunkheader减去127来得到获取下一个颜色重复的次数。 
		{
			chunkHeader -= 127;			//减去127获得ID bit 的rid	开始循环拷贝我们多次读到内存中的像素，这由RLE头中的值规定。
			if (fread(colorbuffer, 1, bytePerPixel, file) != bytePerPixel)
				return FALSE;
			for (int i = 0; i < chunkHeader; i++)
			{
				texture->imageData[currentByte] = colorbuffer[0];			// 拷贝“B”字节
				texture->imageData[currentByte + 1] = colorbuffer[1];			// 拷贝“G”字节
				texture->imageData[currentByte + 2] = colorbuffer[2];			// 拷贝“R”字节
				if (bytePerPixel == 4)
					texture->imageData[currentByte + 3] = colorbuffer[3];			// 拷贝“A”字节

				currentPixel++;
				currentByte += bytePerPixel;
			}
		}
	} while (currentPixel < pixelcount);

	fclose(file);
	delete[] colorbuffer;
	return TRUE;
}

