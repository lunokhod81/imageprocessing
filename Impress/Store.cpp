
#include "stdafx.h"
#include "math.h"
#include "misc.h"
#include "Transfrm.h"
#include "MainFrm.h"
#include "Store.h"


rgba::rgba(float R,float G,float B,float A):rgb(R,G,B)
{if(A>255)A=255; else if(A<0)A=0;a=A;}



Store::~Store()
{
	Free();
}


Store::Store()
{
	//Data=NULL;Height=0;Width=0;Depth=0;BPP=0;Aligned32Width=0;
	Data=NULL;Height=51;Width=51;Depth=24;BPP=3;Aligned32Width=156;
	Allocate(51,51,24);
}





Store::Store(UINT newWidth,UINT newHeight,UINT newDepth)
{
	Data=NULL;Height=0;Width=0;Depth=0;BPP=0;Aligned32Width=0;
	Allocate(newWidth,newHeight,newDepth);
	//	UpdateHeader();
}

Store& Store::operator=(Store& S1)
{

	if(this==&S1) return *this;
	
	if(S1.Width != Width || S1.Height!=Height || S1.Depth !=Depth)
	{
		Allocate(S1.Width,S1.Height,S1.Depth);
		Height=S1.Height;
		Width=S1.Width;
		Depth=S1.Depth;
	}
	
	
	Aligned32Width=S1.Aligned32Width;
	Shift=S1.Shift;
	BPP=S1.BPP;
	ImageHeader=S1.ImageHeader;
	memcpy(Data,S1.Data,Height*Aligned32Width);
	return *this;
	
}




int Store::Allocate(UINT newWidth,UINT newHeight,UINT newDepth)
{
	Free(); //Delete old data
	
	UINT newBPP=newDepth/8; //Calculate BPP
	ASSERT(newBPP == 3 || newBPP == 4); //Dealing only with 24 and 32 bit images
	
	
	//Calculating Shift
	SetNewAligned32Width(newWidth,newDepth);	
	
	Data=new unsigned char[newHeight*Aligned32Width];
	
	if(Data == NULL)
	{
		TRACE("CStore::Allocate : Can't allocate memory\n");
		AfxMessageBox("CStore::Allocate : Can't allocate memory\n");
		return 0;
	}
	
	// Set members variables
	Width = newWidth;	
	Height = newHeight;
	Depth = newDepth;	
	UpdateHeader();
	
	return 1;
}

void Store::Free()
{
	if(Data != NULL)
	{
		delete [] Data;
		Data = NULL;
	}
	
	Width = 0;
	Height = 0;
	Depth = 0;
	BPP=0;
	Aligned32Width=0;
}



int Store::ReadBMPFile(CString filename)
{
	// Check for valid bmp file
	CFile file;
	CFileException ex;
	
	// Try to open file
	if(!file.Open(filename, CFile::modeRead | CFile::typeBinary |CFile::shareDenyNone,&ex))
	{
#ifdef _DEBUG
		afxDump << "File could not be opened " << ex.m_cause << "\n";
#endif
		AfxMessageBox("Unable to open file for reading");
		return 0;
	}
	
	// File header
	BITMAPFILEHEADER FileHeader;
	TRY
	{
		file.Read(&FileHeader,sizeof(BITMAPFILEHEADER));
	}
	CATCH(CFileException, e)
	{
#ifdef _DEBUG
		afxDump << "Error during reading " << e->m_cause << "\n";
#endif
		AfxMessageBox("Error during reading file header");
		file.Close();
		return 0;
	}
	END_CATCH
		
		TRACE("FileHeader.bfType : %d\n",FileHeader.bfType);
	TRACE("FileHeader.bfSize : %d\n",FileHeader.bfSize);
	TRACE("FileHeader.bfReserved1 : %d\n",FileHeader.bfReserved1);
	TRACE("FileHeader.bfReserved2 : %d\n",FileHeader.bfReserved2);
	TRACE("FileHeader.bfOffBits : %d\n",FileHeader.bfOffBits);
	
	// Is it a Windows BMP file ? (BM)
	WORD sign = ((WORD) ('M' << 8) | 'B');
	if(FileHeader.bfType != sign)
	{
		AfxMessageBox("Invalid BMP file");
		file.Close();
		return 0;
	}
	
	// Image header
	TRY
	{
		file.Read(&ImageHeader,sizeof(BITMAPINFOHEADER));
	}
	CATCH(CFileException, e)
	{
#ifdef _DEBUG
		afxDump << "Error during reading " << e->m_cause << "\n";
#endif
		AfxMessageBox("Error during reading image header");
		file.Close();
		return 0;
	}
	END_CATCH
		
		// DEBUG
		TRACE("\n");
	TRACE("**** IMAGE HEADER :\n");
	TRACE("**** biSize : %d\n",ImageHeader.biSize);
	TRACE("**** biWidth : %d\n",ImageHeader.biWidth);
	TRACE("**** biHeight : %d\n",ImageHeader.biHeight);
	TRACE("**** biPlanes : %d\n",ImageHeader.biPlanes);
	TRACE("**** biBitCount : %d\n",ImageHeader.biBitCount);
	TRACE("**** biCompression : %d\n",ImageHeader.biCompression);
	TRACE("**** biSizeImage : %d\n",ImageHeader.biSizeImage);
	TRACE("**** biXPelsPerMeter : %d\n",ImageHeader.biXPelsPerMeter);
	TRACE("**** biYPelsPerMeter : %d\n",ImageHeader.biYPelsPerMeter);
	TRACE("**** biClrUsed : %d\n",ImageHeader.biClrUsed);
	TRACE("**** biClrImportant : %d\n",ImageHeader.biClrImportant);
	
	if ((ImageHeader.biBitCount!=24)&&(ImageHeader.biBitCount!=8)&&(ImageHeader.biBitCount!=4)&&(ImageHeader.biBitCount!=1)) {
		AfxMessageBox("Unknown BMP format");
		file.Close();
		return 0;
	}

	// Alloc (does call Free before)
	int	OriginalBits = ImageHeader.biBitCount;
	Allocate(ImageHeader.biWidth, ImageHeader.biHeight, 24);
	unsigned char	*Temp;
	unsigned char	*Pal=new unsigned char[256*4];
	int	ImLen;
	int	ImW = Width;
	int	ImH = Height;
	int	i, j, x, c;
	
	if(Data == NULL)
	{
		AfxMessageBox("Insufficient memory");
		file.Close();
		return 0;
	}
	switch (OriginalBits) {
		case 24 : {
			TRY
			{
				file.Read(Data,Height*Aligned32Width);
			}
			CATCH(CFileException, e)
			{
				#ifdef _DEBUG
					afxDump << "Error during reading " << e->m_cause << "\n";
				#endif	
				AfxMessageBox("Error during reading image");
				file.Close();
				return 0;
			}
			END_CATCH
			break;
		}
		case 8 : {
			file.Read(Pal, 256*4);
			file.Seek(FileHeader.bfOffBits,CFile::begin);
			ImLen = ImW; if (ImLen%4) ImLen += 4 - ImLen%4; ImLen *= ImH;
			Temp = new unsigned char[ImLen];
			TRY
			{
				file.Read(Temp,ImLen);
			}
			CATCH(CFileException, e)
			{
				#ifdef _DEBUG
					afxDump << "Error during reading " << e->m_cause << "\n";
				#endif	
				AfxMessageBox("Error during reading image");
				file.Close();
				return 0;
			}
			END_CATCH
			x = 0;
			for (i=ImH-1;i>=0;i--) {
				for (j=0;j<ImW;j++) {
					SetPixel(j, ImH-1-i, rgb(Pal[(*(Temp+x))*4+2], Pal[(*(Temp+x))*4+1], Pal[(*(Temp+x))*4]));
					x++;
				}
				if (x%4) x += 4 - x%4;
			}
			delete Temp;
			break;
		}
		case 4 : {
			file.Read(Pal, 16*4);
			file.Seek(FileHeader.bfOffBits,CFile::begin);
			ImLen = ImW; if (ImLen%8) ImLen += 8 - ImLen%8; ImLen /= 2; ImLen *= ImH;
			Temp = new unsigned char[ImLen];
			TRY
			{
				file.Read(Temp,ImLen);
			}
			CATCH(CFileException, e)
			{
				#ifdef _DEBUG
					afxDump << "Error during reading " << e->m_cause << "\n";
				#endif	
				AfxMessageBox("Error during reading image");
				file.Close();
				return 0;
			}
			END_CATCH
			x = 0;
			for (i=ImH-1;i>=0;i--) {
				for (j=0;j<ImW;j++) {
					c = ((*(Temp+x/2)) >> ((1-x%2)*4)) & 0xF;
					SetPixel(j, ImH-1-i, rgb(Pal[c*4+2], Pal[c*4+1], Pal[c*4]));
					x++;
				}
				if (x%8) x += 8 - x%8;
			}
			delete Temp;
			break;
		}
		case 1 : {
			file.Read(Pal, 2*4);
			file.Seek(FileHeader.bfOffBits,CFile::begin);
			ImLen = ImW; if (ImLen%32) ImLen += 32 - ImLen%32; ImLen /= 8; ImLen *= ImH;
			Temp = new unsigned char[ImLen];
			TRY
			{
				file.Read(Temp,ImLen);
			}
			CATCH(CFileException, e)
			{
				#ifdef _DEBUG
					afxDump << "Error during reading " << e->m_cause << "\n";
				#endif	
				AfxMessageBox("Error during reading image");
				file.Close();
				return 0;
			}
			END_CATCH
			x = 0;
			for (i=ImH-1;i>=0;i--) {
				for (j=0;j<ImW;j++) {
					c = ((*(Temp+x/8)) >> (7-(x%8))) & 1;
					SetPixel(j, ImH-1-i, rgb(Pal[c*4], Pal[c*4], Pal[c*4]));
					x++;
				}
				if (x%32) x += 32 - x%32;
			}
			delete Temp;
			break;
		}
	}
	
	delete Pal;
	// Close file
	file.Close();
	//SetNewAligned32Width(Width,Depth);
	FileName = filename;	
	return 1;	
}





int Store::SaveBMPFile(CString filename)
{
	if(!IsCorrect())
		return 0;
	
	
	
	// Check for valid bmp file
	CFile file;
	CFileException ex;
	
	// Try to open file
	if(!file.Open(filename,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary,&ex))
	{
#ifdef _DEBUG
		afxDump << "File could not be opened " << ex.m_cause << "\n";
#endif
		AfxMessageBox("Unable to open file for writing");
		return 0;
	}
	
	// File header
	BITMAPFILEHEADER FileHeader;
	WORD sign = ((WORD) ('M' << 8) | 'B');
	FileHeader.bfType = sign;
	FileHeader.bfSize = 14 + 40 + Aligned32Width*Height; 
	FileHeader.bfReserved1 = 0; 
	FileHeader.bfReserved2 = 0; 
	FileHeader.bfOffBits = 54; 
	
	TRACE("\nSave BMP File...\n");
	TRACE("FileHeader.bfType : %d\n",FileHeader.bfType);
	TRACE("FileHeader.bfSize : %d\n",FileHeader.bfSize);
	TRACE("FileHeader.bfReserved1 : %d\n",FileHeader.bfReserved1);
	TRACE("FileHeader.bfReserved2 : %d\n",FileHeader.bfReserved2);
	TRACE("FileHeader.bfOffBits : %d\n",FileHeader.bfOffBits);
	
	TRY
	{
		file.Write(&FileHeader,sizeof(BITMAPFILEHEADER));
	}
	CATCH(CFileException, e)
	{
#ifdef _DEBUG
		afxDump << "Error during writing " << e->m_cause << "\n";
#endif
		AfxMessageBox("Error during writing file header");
		file.Close();
		return 0;
	}
	END_CATCH
		
		// Image header
		TRY
	{
		file.Write(&ImageHeader,sizeof(BITMAPINFOHEADER));
	}
	CATCH(CFileException, e)
	{
#ifdef _DEBUG
		afxDump << "Error during writing " << e->m_cause << "\n";
#endif
		AfxMessageBox("Error during writing image header");
		file.Close();
		return 0;
	}
	END_CATCH
		
		// DEBUG
		TRACE("\n");
	TRACE("**** IMAGE HEADER :\n");
	TRACE("**** biSize : %d\n",ImageHeader.biSize);
	TRACE("**** biWidth : %d\n",ImageHeader.biWidth);
	TRACE("**** biHeight : %d\n",ImageHeader.biHeight);
	TRACE("**** biPlanes : %d\n",ImageHeader.biPlanes);
	TRACE("**** biBitCount : %d\n",ImageHeader.biBitCount);
	TRACE("**** biCompression : %d\n",ImageHeader.biCompression);
	TRACE("**** biSizeImage : %d\n",ImageHeader.biSizeImage);
	TRACE("**** biXPelsPerMeter : %d\n",ImageHeader.biXPelsPerMeter);
	TRACE("**** biYPelsPerMeter : %d\n",ImageHeader.biYPelsPerMeter);
	TRACE("**** biClrUsed : %d\n",ImageHeader.biClrUsed);
	TRACE("**** biClrImportant : %d\n",ImageHeader.biClrImportant);
	
	// Image writing
	TRY
	{
		file.Write(Data,ImageHeader.biSizeImage);
	}
	CATCH(CFileException, e)
	{
#ifdef _DEBUG
		afxDump << "Error during writing " << e->m_cause << "\n";
#endif
		AfxMessageBox("Error during writing image");
		file.Close();
		return 0;
	}
	END_CATCH
		
		// Close file
		file.Close();
	
	
	
	return 1;
}



int Store::SaveBMPFile(CString flename, int Depth, unsigned char *Data, unsigned char *Palette)
{
	return 0;
}




void Store::UpdateHeader()
{
	SetNewAligned32Width(Width,Depth);
	int x=13;
	
	ImageHeader.biWidth = Width;
	ImageHeader.biHeight = Height;
	ImageHeader.biSizeImage = Aligned32Width * Height;
	
	ImageHeader.biSize = 40;
	ImageHeader.biPlanes = 1;
	ImageHeader.biBitCount = Depth;
	ImageHeader.biCompression = 0;
	ImageHeader.biXPelsPerMeter = 0;
	ImageHeader.biYPelsPerMeter = 0;
	ImageHeader.biClrUsed = 0;
	ImageHeader.biClrImportant = 0;
	
}

void Store::SetNewAligned32Width(UINT newWidth,UINT newDepth)
{
	
	// 32 bits alignment (4 bytes)
	Shift=(newWidth*newDepth/8)%4;
	if(Shift != 0)
		Aligned32Width=newWidth*newDepth/8 + 4-Shift;
	else
		Aligned32Width=newWidth*newDepth/8;
	
	BPP=(UINT)(Depth/8);
	
}


int Store::Display(CDC *pDC,int xOffset,int yOffset,int width,int height)
{
	// Checking
	if(!IsCorrect())
		return 0;
	
	// Flags	
	if(width == -1)
		width = Width;
	if(height == -1)
		height = Height;
	
	// Painting
	return SetDIBitsToDevice(pDC->m_hDC,
		xOffset,
		yOffset,
		width,
		height,
		0,
		0,
		0,
		Height,
		Data,
		(CONST BITMAPINFO *)&ImageHeader,
		DIB_RGB_COLORS);
	
	
}

BOOL Store::IsCorrect()
{
	BOOL Correct = FALSE;
	Correct = (Depth == 24) || (Depth == 32);
	Correct &= (Width != 0);
	Correct &= (Height != 0);
	Correct &= (Data != NULL);
	if(!Correct)
	{
		TRACE("\n");
		TRACE("Invalid image\n");
		TRACE("Width  : %d\n",Width);
		TRACE("Height : %d\n",Height);
		TRACE("Depth  : %d\n",Depth);
		TRACE("Data   : %x\n",Data);
		return FALSE;
	}
	return TRUE;
	
}

rgb Store::GetPixel(UINT X,UINT Y)
{
	ASSERT(X>=0 && X<Width && Y>=0 && Y< Height);
	int offset=Y*Aligned32Width+X*BPP;	
	return rgb(Data[offset+2],Data[offset+1],Data[offset]);
}



rgba Store::GetPixelAlpha(UINT X, UINT Y)
{
	ASSERT(X>=0 && X<Width && Y>=0 && Y<Height);
	int offset=Y*Aligned32Width+X*BPP;		
	return rgba(Data[offset+2],Data[offset+1],Data[offset],Data[offset+3]);
}




void Store::SetPixel(UINT X,UINT Y,rgb color)
{
	ASSERT(X>=0 && X<Width && Y>=0 && Y<Height);
	
	int offset=Y*Aligned32Width+X*BPP;	
	Data[offset+2]=color.r;
	Data[offset+1]=color.g;
	Data[offset]=color.b;
}

void Store::SetPixelAlpha(UINT X, UINT Y, rgba color)
{
	ASSERT(X>=0 && X<Width && Y>=0 && Y<Height);
	
	if(!HasAlpha())
		return;
	
	
	int offset=Y*Aligned32Width+X*BPP;	
	
	Data[offset+3]=color.a;
	Data[offset+2]=color.r;
	Data[offset+1]=color.g;
	Data[offset]=color.b;
	
}


unsigned char Store::GetAlpha(UINT X,UINT Y)
{
	ASSERT(X>=0 && X<Width && Y>=0 && Y<Height);
	
	if(!HasAlpha())
		return 0;
	
	return	Data[Y*Aligned32Width+X*BPP+3];
	
}



void Store::SetAlpha(UINT X, UINT Y, unsigned char alpha)
{
	ASSERT(X>=0 && X<Width && Y>=0 && Y<Height);
	
	if(!HasAlpha())
		return;	
	Data[Y*Aligned32Width+X*BPP+3]=alpha;
	
}





Store::Store(Store &S1)
{
	
	if(S1.Width != Width || S1.Height!=Height || S1.Depth !=Depth)
	{
		Allocate(S1.Width,S1.Height,S1.Depth);
		Height=S1.Height;
		Width=S1.Width;
		Depth=S1.Depth;
	}
	
	Aligned32Width=S1.Aligned32Width;
	Shift=S1.Shift;
	BPP=S1.BPP;
	ImageHeader=S1.ImageHeader;
	memcpy(Data,S1.Data,Height*Aligned32Width);
	
	
}

void rgb::Invert()
{
	r=255-r;
	g=255-g;
	b=255-b;
	
}

void rgb::AddSmart(rgb color)
{
	int R=(int)color.r+(int)r;
	int G=(int)color.g+(int)g;
	int B=(int)color.b+(int)b;
	;
	if(R>255)R=255;
	if(G>255)G=255;
	if(B>255)B=255;
	
	r=(unsigned char)R;
	g=(unsigned char)G;
	b=(unsigned char)B;
	
}


void rgb::SubstractSmart(rgb color)
{
	int R=(int)color.r-(int)r;
	int G=(int)color.g-(int)g;
	int B=(int)color.b-(int)b;
	
	if(R<0)R=0;
	if(G<0)G=0;
	if(B<0)B=0;
	
	r=(unsigned char)Round(R);
	g=(unsigned char)Round(G);
	b=(unsigned char)Round(B);
}


rgb::rgb(float R, float G, float B)
{
	if(R>255)
		R=255;
	else
		if(R<0)
			R=0;
		
	if(G>255)
		G=255;
	else
		if(G<0)
			G=0;
			
	if(B>255)
		B=255;
	else
		if(B<0)
			B=0;
				
	r=(unsigned char)Round(R);
	g=(unsigned char)Round(G);
	b=(unsigned char)Round(B);
				
}






void Store::CompositePixel(UINT X, UINT Y, rgba color)
{
	ASSERT(X>=0 && X<Width && Y>=0 && Y<Height);
	
	int offset=Y*Aligned32Width+X*BPP;	
	
	
	float beta=color.a/255.0f;
	float alpha=1-beta;
	
	Data[offset]=Data[offset]*alpha+color.b*beta;
	Data[offset+1]=Data[offset+1]*alpha+color.g*beta;
	Data[offset+2]=Data[offset+2]*alpha+color.r*beta;
	
}

int Store::DisplayRect(CDC *pDC,CPoint Dest,CRect RectToUpdate)
{
	if(!IsCorrect())
		return 0;
	
	
	
	// Painting
	return SetDIBitsToDevice(pDC->m_hDC,
		Dest.x,
		Dest.y,
		RectToUpdate.Width(),
		RectToUpdate.Height(),
		RectToUpdate.left,
		Height-RectToUpdate.bottom,															 													 
		
		0,
		Height,
		Data,
		(CONST BITMAPINFO *)&ImageHeader,
		DIB_RGB_COLORS);
	
	
}



COLORREF rgb::GetRGB()
{
	return RGB(r,g,b);
}

rgb::rgb(COLORREF color)
{
	r=GetRValue(color);
	g=GetGValue(color);
	b=GetBValue(color);

}


int Store::Quantize(int nColors, unsigned char *Data, unsigned char *Palette)
{
#define max2(i,j) (((i)>(j))?(i):(j))
#define min2(i,j) (((i)<(j))?(i):(j))
	CTransform transform;
	transform.StatusBar = &(((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar);
	int	LastPercent = 0;
	transform.StartTransform();
	transform.SetText("Converting image...");

	int	i, j, m, n, Step;
	int	Ofs;
	int	BestCube, Cube, Dimension, nPixelsInCube;
	float	Bound;
	unsigned char rmin, rmax, gmin, gmax, bmin, bmax, maxCubeD;
	struct Color {
		int	nCube;
		unsigned char	Value[3];
		int	nPixels;
	};
	rgb Col;		// Temp color
	int	iR, iG, iB;
	float *fData = new float[Width*Height*3];
	for (i=0,Ofs=0; i<Height; i++)
		for (j=0; j<Width; j++) {
			Col = GetPixel(j, i);
			fData[Ofs++] = Col.r;
			fData[Ofs++] = Col.g;
			fData[Ofs++] = Col.b;
		}
	transform.SetText("Scanning pixels...");
	// Setup starting palette...
	Color *Pal = new Color[Width*Height];
	for (i=0; i<Width*Height; i++) Pal[i].Value[0] = Pal[i].Value[1] = Pal[i].Value[2] = -1;
	int	TPalSize = 100;
	Color *TPal = new Color[TPalSize];
	for (i=0; i<TPalSize; i++) TPal[i].Value[0] = TPal[i].Value[1] = TPal[i].Value[2] = -1;
	int	nPalEntries = 0;
	int	nCubes = 1;
	Ofs = 0;
	int	nTPalEntries;
	int	MaxI;
	int	PalI1, PalI2;

		// Fill TPal...
		for (nTPalEntries=0; (nTPalEntries<TPalSize)&&(Ofs<Width*Height*3); ) {
			Col.r = fData[Ofs++];
			Col.g = fData[Ofs++];
			Col.b = fData[Ofs++];
			for (m=0; m<nTPalEntries; m++)
				if (rgb(TPal[m].Value[0],TPal[m].Value[1],TPal[m].Value[2])==Col) {
					TPal[m].nPixels++;
					break;
				}
			if (m==nTPalEntries) {
				TPal[m].Value[0] = Col.r;
				TPal[m].Value[1] = Col.g;
				TPal[m].Value[2] = Col.b;
				TPal[m].nCube = 0;
				TPal[m].nPixels = 1;
				nTPalEntries++;
			}
		}
		// Transfer TPal to Pal...
		i = nPalEntries - 1;
		for (n=0; n<nTPalEntries; n++) {		// For each entry...
			MaxI = 0;
			for (m=1; m<nPalEntries; m++)		// For each entry...
				if (rgb::Before(TPal[MaxI].Value[0], TPal[MaxI].Value[1], TPal[MaxI].Value[2], TPal[m].Value[0], TPal[m].Value[1], TPal[m].Value[2]))
					if (TPal[m].nPixels!=0)
						MaxI = m;
			// Insert maximal element into Pal...
			if (nPalEntries==0) {
			}
		}

			
			// Update progress...
//		if ((int)(100*i/(float)Height)>LastPercent+1) {
//			LastPercent = (int)(100*i/Height);
//			transform.SetProgress(LastPercent);

	
	
	
/*	for (i=0,Ofs=0; i<Height; i++) {		// For each pixel...
		for (j=0; j<Width; j++) {
			Col.r = fData[Ofs++];
			Col.g = fData[Ofs++];
			Col.b = fData[Ofs++];
			for (m=0; m<nPalEntries; m++)
				if (rgb(Pal[m].Value[0],Pal[m].Value[1],Pal[m].Value[2])==Col) {
					Pal[m].nPixels++;
					break;
				}
			if (m==nPalEntries) {
				Pal[m].Value[0] = Col.r;
				Pal[m].Value[1] = Col.g;
				Pal[m].Value[2] = Col.b;
				Pal[m].nCube = 0;
				Pal[m].nPixels = 1;
				nPalEntries++;
			}
		}
		// Update progress...
//		if ((int)(100*i/(float)Height)>LastPercent+1) {
//			LastPercent = (int)(100*i/Height);
//			transform.SetProgress(LastPercent);
	}
*/

	// COLOR MATCHING
	transform.SetText("Generating palette...");
	for (Step=0; Step<nColors-1; Step++) {
		// Select the cube and the dimension...
		maxCubeD = 0;
		i=0;
		for (Cube=0; Cube<nCubes; Cube++) {		// For each cube...
			rmin = gmin = bmin = 255;
			rmax = gmax = bmax = 0;
			while ((Pal[i].nCube==Cube)&&(i<nPalEntries)) {
				rmax = max2(rmax, Pal[i].Value[0]);
				gmax = max2(gmax, Pal[i].Value[1]);
				bmax = max2(bmax, Pal[i].Value[2]);
				rmin = min2(rmin, Pal[i].Value[0]);
				gmin = min2(gmin, Pal[i].Value[1]);
				bmin = min2(bmin, Pal[i].Value[2]);
				i++;
			}
			if (rmax-rmin>maxCubeD) {
				maxCubeD = rmax - rmin;
				BestCube = Cube;
				Dimension = 0;
			}
			if (gmax-gmin>maxCubeD) {
				maxCubeD = gmax - gmin;
				BestCube = Cube;
				Dimension = 1;
			}
			if (bmax-bmin>maxCubeD) {
				maxCubeD = bmax - bmin;
				BestCube = Cube;
				Dimension = 2;
			}
		}
		if (maxCubeD==0) break;
		// Break the cube into 2 cubes: [BestBube] and [nCubes]
		// Find the boundary...
		for (i=0; i<nPalEntries; i++) if (Pal[i].nCube==BestCube) break;		// Find pixels from best cube
		j = i;		// Store the first pixel index
		Bound = nPixelsInCube = 0;
		for (; i<nPalEntries; i++) {
			if (Pal[i].nCube!=BestCube) break;
			Bound += Pal[i].Value[Dimension] * Pal[i].nPixels;
			nPixelsInCube += Pal[i].nPixels;
		}
		Bound /= nPixelsInCube;
		// Seperate pixels...
		for (i=j; i<nPalEntries; i++) {
			if (Pal[i].nCube!=BestCube) break;
			if (Pal[i].Value[Dimension]>Bound)
				Pal[i].nCube = nCubes;
		}
		nCubes++;
		// Sort new array of cubes...
		Color *Pal1 = new Color[nPalEntries];
		j = 0;
		for (Cube=0; Cube<nCubes; Cube++)
			for (i=0; i<nPalEntries; i++)
				if (Pal[i].nCube==Cube)
					Pal1[j++] = Pal[i];
		delete Pal;
		Pal = Pal1;

		/////////////////////////////
//		char s[100];
//		sprintf(s,"BestCube = %d, Dimension = %d, Diameter = %d, Bound = %d",(int)BestCube,(int)(Dimension),(int)maxCubeD,(int)Bound);
//		MessageBox(0,s,"",0);
		/////////////////////////////
	}
	// BUILDIND A NEW IMAGE
	transform.SetText("Converting image...");
	// Select best colors...
	float	R,G,B;
	i = 0;
	for (Cube=0; Cube<nCubes; Cube++) {
		R = G = B = nPixelsInCube = 0;
		for (i=0; i<nPalEntries; i++)
			if (Pal[i].nCube==Cube) break;
		for ( ; i<nPalEntries; i++) {
			if (Pal[i].nCube!=Cube) break;
			R += Pal[i].Value[0] * Pal[i].nPixels;
			G += Pal[i].Value[1] * Pal[i].nPixels;
			B += Pal[i].Value[2] * Pal[i].nPixels;
			nPixelsInCube += Pal[i].nPixels;
		}
		R /= nPixelsInCube;
		G /= nPixelsInCube;
		B /= nPixelsInCube;
		Palette[Cube*3] = R;
		Palette[Cube*3+1] = G;
		Palette[Cube*3+2] = B;
	}
	delete Pal;

	// Error diffusion algorithm...
	int	iNearestCol;
	float	NearestDistance, CurDistance;
	float	eR, eG, eB = 0;
	float	LastER, LastEG, LastEB;
	int	cER, cEG, cEB;
	for (i=0; i<Height; i++) {
		cER = cEG = cEB = 0;
		if (j%2)
			for (j=0; j<Width; j++) {
				Ofs = (i*Width+j)*3;
				R = fData[Ofs];
				G = fData[Ofs+1];
				B = fData[Ofs+2];
				NearestDistance = 1000;
				for (m=0; m<nCubes; m++) {
					CurDistance = rgb::Distance(Palette[m*3],Palette[m*3+1],Palette[m*3+2], R,G,B);
					if (CurDistance<NearestDistance) {
						iNearestCol = m;
						NearestDistance = CurDistance;
					}
				}
				Data[i*Width+j] = iNearestCol;
				LastER = eR; LastEG = eG; LastEB = eB;
				eR = Palette[iNearestCol*3] - R;
				eG = Palette[iNearestCol*3+1] - G;
				eB = Palette[iNearestCol*3+2] - B;
				// Correct overshoots...
				if (LastER*eR>0) cER++; else cER = 0;
				if (LastEG*eG>0) cEG++; else cEG = 0;
				if (LastEB*eB>0) cEB++; else cEB = 0;
				if (cER>5) cER = eR = 0;
				if (cEG>5) cEG = eG = 0;
				if (cEB>5) cEB = eB = 0;

				if ((i<Height-1)&&(j>0)&&(j<Width-1)) {
					fData[Ofs+3] -= eR*7.0/16;
					fData[Ofs+4] -= eG*7.0/16;
					fData[Ofs+5] -= eB*7.0/16;

					fData[Ofs+Width*3+3] -= eR*1.0/16;
					fData[Ofs+Width*3+4] -= eG*1.0/16;
					fData[Ofs+Width*3+5] -= eB*1.0/16;

					fData[Ofs+Width*3] -= eR*5.0/16;
					fData[Ofs+Width*3+1] -= eG*5.0/16;
					fData[Ofs+Width*3+2] -= eB*5.0/16;

					fData[Ofs+Width*3-3] -= eR*3.0/16;
					fData[Ofs+Width*3-2] -= eG*3.0/16;
					fData[Ofs+Width*3-1] -= eB*3.0/16;
				}
			}
		else
			for (j=Width; j>=0; j--) {
				Ofs = (i*Width+j)*3;
				R = fData[Ofs];
				G = fData[Ofs+1];
				B = fData[Ofs+2];
				NearestDistance = 1000;
				for (m=0; m<nCubes; m++) {
					CurDistance = rgb::Distance(Palette[m*3],Palette[m*3+1],Palette[m*3+2], R,G,B);
					if (CurDistance<NearestDistance) {
						iNearestCol = m;
						NearestDistance = CurDistance;
					}
				}
				Data[i*Width+j] = iNearestCol;
				LastER = eR; LastEG = eG; LastEB = eB;
				eR = Palette[iNearestCol*3] - R;
				eG = Palette[iNearestCol*3+1] - G;
				eB = Palette[iNearestCol*3+2] - B;
				// Correct overshoots...
				if (LastER*eR>0) cER++; else cER = 0;
				if (LastEG*eG>0) cEG++; else cEG = 0;
				if (LastEB*eB>0) cEB++; else cEB = 0;
				if (cER>5) cER = eR = 0;
				if (cEG>5) cEG = eG = 0;
				if (cEB>5) cEB = eB = 0;

				if ((i<Height-1)&&(j>0)&&(j<Width-1)) {
					fData[Ofs-3] -= eR*7.0/16;
					fData[Ofs-2] -= eG*7.0/16;
					fData[Ofs-1] -= eB*7.0/16;

					fData[Ofs+Width*3-3] -= eR*1.0/16;
					fData[Ofs+Width*3-2] -= eG*1.0/16;
					fData[Ofs+Width*3-1] -= eB*1.0/16;

					fData[Ofs+Width*3] -= eR*5.0/16;
					fData[Ofs+Width*3+1] -= eG*5.0/16;
					fData[Ofs+Width*3+2] -= eB*5.0/16;

					fData[Ofs+Width*3+3] -= eR*3.0/16;
					fData[Ofs+Width*3+4] -= eG*3.0/16;
					fData[Ofs+Width*3+5] -= eB*3.0/16;
				}
			}
	}

	unsigned char C;
	for (i=0;i<Height;i++)
		for (j=0;j<Width;j++) {
			C = Data[i*Width+j];
			SetPixel(j,i,rgb(Palette[C*3], Palette[C*3+1], Palette[C*3+2]));
		}
//	time2 = clock();
//	sprintf(str, "Time elapsed: %d ms", (int)((time2-time1)*1000/CLK_TCK));
//	MessageBox(0,str, "Message", MB_OK);
	transform.EndTransform();
	return 0;
}
