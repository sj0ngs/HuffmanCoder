
// HuffmanCompressorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "HuffmanCompressor.h"
#include "HuffmanCompressorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHuffmanCompressorDlg 대화 상자



CHuffmanCompressorDlg::CHuffmanCompressorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HUFFMANCOMPRESSOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pTree = new HuffmanTree();
}

CHuffmanCompressorDlg::~CHuffmanCompressorDlg()
{
	if (m_pTree)
	{
		delete m_pTree;
		m_pTree = nullptr;
	}
}

void CHuffmanCompressorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHuffmanCompressorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON1, &CHuffmanCompressorDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_LOADFILE, &CHuffmanCompressorDlg::OnBnClickedLoadfile)
ON_BN_CLICKED(IDC_DECOMPRESS, &CHuffmanCompressorDlg::OnBnClickedDecompress)
ON_BN_CLICKED(IDC_COMPARE, &CHuffmanCompressorDlg::OnBnClickedCompare)
END_MESSAGE_MAP()


// CHuffmanCompressorDlg 메시지 처리기

BOOL CHuffmanCompressorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHuffmanCompressorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHuffmanCompressorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHuffmanCompressorDlg::OnBnClickedLoadfile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"txt\0*.txt\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = nullptr;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	m_pTree->Clear();
	m_pTree->Create(szFilePath);


	// hfb, hft 제작
	wchar_t szFileNoEx[1024] = {};
	wcscpy_s(szFileNoEx, szFilePath);
	size_t tLen = wcslen(szFileNoEx);
	for (size_t i = tLen - 1; i > 0; i--)
	{
		if (L'.' == szFileNoEx[i])
		{
			szFileNoEx[i] = (wchar_t)0;
			break;
		}
	}

	CreateHFT(szFilePath, szFileNoEx);
	CreateHFB(szFilePath, szFileNoEx);
}


void CHuffmanCompressorDlg::OnBnClickedDecompress()
{
	// open a file name
	OPENFILENAME ofn = {};

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"hfb\0*.hfb\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = nullptr;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	m_pTree->Clear();
	m_pTree->Create(szFilePath);

	wchar_t szFileNoEx[1024] = {};
	wcscpy_s(szFileNoEx, szFilePath);
	size_t tLen = wcslen(szFileNoEx);
	for (size_t i = tLen - 1; i > 0; i--)
	{
		if (L'.' == szFileNoEx[i])
		{
			szFileNoEx[i] = (wchar_t)0;
			break;
		}
	}
	CreateTXT(szFilePath, szFileNoEx);
}

void CHuffmanCompressorDlg::CreateHFT(const wchar_t* _wcharFilePath, const wchar_t* _wcharPath)
{
	wchar_t pHFT[1024] = {};
	wcscpy_s(pHFT, _wcharPath);
	wcscat_s(pHFT, L".hft");

	FILE* pFileOrigin = nullptr;
	FILE* pFileHFT = nullptr;

	_wfopen_s(&pFileOrigin, _wcharFilePath, L"rt");
	_wfopen_s(&pFileHFT, pHFT, L"wt");

	const unordered_map<char, string>& umapCode = m_pTree->GetCode();
	const unordered_map<char, int>& umapFreq = m_pTree->GetFreq();

	if (nullptr == pFileOrigin || nullptr == pFileHFT)
		return;

	// 헤더 작성
	for (const auto& pair : umapFreq)
	{
		fprintf(pFileHFT, "%c(%d) : ", pair.first, pair.second);
		string str = m_pTree->GetString(pair.first);
		size_t iLen = str.length();
		fwrite(str.c_str(), sizeof(char), iLen, pFileHFT);
		fprintf(pFileHFT, ", ");
	}

	// 본문 작성
	char chBuff = (char)0;

	while (true)
	{
		size_t tCheck = fread(&chBuff, sizeof(char), 1, pFileOrigin);
		string str = m_pTree->GetString(chBuff);
		size_t iLen = str.length();
		fwrite(str.c_str(), sizeof(char), iLen, pFileHFT);

		if (0 == tCheck)
			break;
	}

	fclose(pFileOrigin);
	fclose(pFileHFT);
}

void CHuffmanCompressorDlg::CreateHFB(const wchar_t* _wcharFilePath, const wchar_t* _wcharPath)
{
	wchar_t pHFB[1024] = {};
	wcscpy_s(pHFB, _wcharPath);
	wcscat_s(pHFB, L".hfb");

	FILE* pFileOrigin = nullptr;
	FILE* pFileHFB = nullptr;

	_wfopen_s(&pFileOrigin, _wcharFilePath, L"rt");
	_wfopen_s(&pFileHFB, pHFB, L"wb");

	if (nullptr == pFileOrigin || nullptr == pFileHFB)
		return;

	const unordered_map<char, string>& umapCode = m_pTree->GetCode();

	// 메모장 형식 에러 때문에 한칸 비우기
	int iPadd = 0;
	fwrite(&iPadd, sizeof(int), 1, pFileHFB);

	// 헤더 작성
	// 호프만 코드 원소 개수
	size_t tSize = umapCode.size();
	fwrite(&tSize, sizeof(size_t), 1, pFileHFB);

	for (const auto& pair : umapCode)
	{
		// 문자 저장
		char cBuff = pair.first;
		fwrite(&cBuff, sizeof(char), 1, pFileHFB);

		// 호프만 코드의 유효 비트수 저장
		size_t tBits = pair.second.length();
		fwrite(&tBits, sizeof(size_t), 1, pFileHFB);

		// 실제 호프만 코드 저장
		byte buffer = 0;
		int iMsb = -1;

		for (size_t i = 0; i < tBits; i++)
		{
			if (7 == iMsb)
			{
				fwrite(&buffer, sizeof(byte), 1, pFileHFB);
				buffer = 0;
				iMsb = -1;
			}

			buffer = buffer << 1;
			if (pair.second[i] == '1')
			{
				buffer |= 1;
			}
			++iMsb;
		}

		if (-1 != iMsb)
		{
			while (7 != iMsb)
			{
				buffer = buffer << 1;
				iMsb++;
			}
			fwrite(&buffer, sizeof(byte), 1, pFileHFB);
		}
	}

	const unordered_map<char, int>& umapFreq = m_pTree->GetFreq();

	// 문자 개수 저장
	unsigned int iTotalCount = 0;
	for (const auto& pair : umapFreq)
	{
		iTotalCount += (unsigned int)pair.second;
	}

	fwrite(&iTotalCount, sizeof(unsigned int), 1, pFileHFB);

	// 본문 작성
	char chBuff = '\0';
	byte buffer = 0;
	int iMsb = -1;
	
	int count = 0;
	while (true)
	{
		size_t tCheck = fread(&chBuff, sizeof(char), 1, pFileOrigin);

		string str = m_pTree->GetString(chBuff);
		size_t tLen = str.length();

		for (size_t i = 0; i < tLen; i++)
		{
			if (7 == iMsb)
			{
				fwrite(&buffer, sizeof(byte), 1, pFileHFB);
				buffer = 0;
				iMsb = -1;
				count++;
			}

			buffer = buffer << 1;
			if (str[i] == '1')
			{
				buffer |= 1;
			}
			++iMsb;
		}

		if (0 == tCheck)
			break;
	}

	int iLastBit = iMsb;
	while (7 != iLastBit)
	{
		buffer = buffer << 1;
		iLastBit++;
	}

	fwrite(&buffer, sizeof(byte), 1, pFileHFB);
	//fseek(pFileHFB, 0, SEEK_SET);
	//fwrite(&iMsb, sizeof(char), 1, pFileHFB);

	fclose(pFileOrigin);
	fclose(pFileHFB);
}

void CHuffmanCompressorDlg::CreateTXT(const wchar_t* _wcharFilePath, const wchar_t* _wcharFileName)
{
	wchar_t pTXT[1024] = {};
	wcscpy_s(pTXT, _wcharFileName);
	wcscat_s(pTXT, L".hfd");

	FILE* pFileOrigin = nullptr;
	FILE* pFileTXT = nullptr;

	_wfopen_s(&pFileOrigin, _wcharFilePath, L"rb");
	_wfopen_s(&pFileTXT, pTXT, L"wt");

	if (nullptr == pFileOrigin || nullptr == pFileTXT)
		return;

	vector<HuffmanBin> vecBin;

	int iPadd = 0;
	fread(&iPadd, sizeof(int), 1, pFileOrigin);

	// 헤더 읽어오기
	// 호프만 코드 원소 개수
	size_t tSize = 0;
	fread(&tSize, sizeof(size_t), 1, pFileOrigin);

	for (int i = 0; i < tSize; i++)
	{
		// 문자 불러오기
		char cBuff = (char)0;
		fread(&cBuff, sizeof(char), 1, pFileOrigin);

		// 호프만 코드의 유효 비트수 불러오기
		size_t tBits = 0;
		fread(&tBits, sizeof(size_t), 1, pFileOrigin);

		// 실제 호프만 코드 불러오기
		byte buffer = 0;
		int iMfb = -1;
		
		string str;
		while (tBits > 0)
		{
			fread(&buffer, sizeof(byte), 1, pFileOrigin);
			for (int j = 7; j >= 0; j--)
			{
				if (tBits <= 0)
					break;

				if ((buffer >> j) & 1)
				{
					str += "1";
				}
				else
				{
					str += "0";
				}
				tBits--;
			}
		}
		HuffmanBin tmp = { cBuff, str };
		vecBin.push_back(tmp);
	}

	sort(vecBin.begin(), vecBin.end(), HuffmanVecCmp);

	// 문자 개수 불러오기
	unsigned int iTotalCount = 0;

	fread(&iTotalCount, sizeof(unsigned int), 1, pFileOrigin);

	// 본문 불러오기
	byte buffer = 0;
	unsigned short sBuffer = 0;
	int iMsb = 0;
	int iLen = 0;

	byte arrBuffer[2] = {};
	size_t tCheck = 1;
	fread(&arrBuffer, sizeof(byte), 2, pFileOrigin);

	unsigned int iCount = 0;

	for (size_t i = 0; i < 8; i++)
	{
		sBuffer = sBuffer << 1;

		if (1 & (arrBuffer[0] >> (7 - i)))
		{
			sBuffer = sBuffer | 1;
		}
	}

	for (size_t i = 0; i < 8; i++)
	{
		sBuffer = sBuffer << 1;

		if (1 & (arrBuffer[1] >> (7 - i)))
		{
			sBuffer = sBuffer | 1;
		}
	}
	
	fread(&buffer, sizeof(byte), 1, pFileOrigin);

	while (true)
	{
		if (iCount == iTotalCount/*0 == tCheck*/)
			break;

		char cOrign = '\0';
		bool bResult = false;

		if (0 == iLen)
		{
			bResult = SearchChar(vecBin, sBuffer, &cOrign, &iLen);
		}
		iLen--;

		if (bResult)
		{
			fwrite(&cOrign, sizeof(char), 1, pFileTXT);
			iCount++;
		}

		short tmp = buffer >> (7 - iMsb);
		iMsb++;

		sBuffer = sBuffer << 1;

		if (1 & tmp)
		{
			sBuffer = sBuffer | 1;
		}

		if (7 < iMsb)
		{
			tCheck = fread(&buffer, sizeof(byte), 1, pFileOrigin);
			iMsb = 0;
		}
	}

	fclose(pFileOrigin);
	fclose(pFileTXT);
}

bool CHuffmanCompressorDlg::SearchChar(const vector<HuffmanBin>& _vec, unsigned short _sBuff, char* _pChar, int* _pLen)
{
	size_t tvecSize = _vec.size();
	char cResult = '\0';

	for (size_t i = 0; i < tvecSize; i++)
	{
		bool bCheck = true;
		size_t tStrLen = _vec[i].tCode.length();

		for (size_t j = 0; j < tStrLen; j++)
		{
			unsigned short buff = _sBuff >> (15 - j);

			if (_vec[i].tCode[j] == '0')
			{
				// 마지막 비트가 1이라면 거짓
				if (buff & (short)1)
				{
					bCheck = false;
					break;
				}
			}
			else
			{
				// 마지막 비트가 1이 아니라면 거짓
				if (!(buff & (short)1))
				{
					bCheck = false;
					break;
				}
			}
		}
		
		if (bCheck)
		{
			*_pChar = _vec[i].tChar;
			*_pLen = (int)tStrLen;
			break;
		}
	}
	return true;
}

bool HuffmanVecCmp(HuffmanBin _left, HuffmanBin _right)
{
	return _left.tCode.length() > _right.tCode.length();
}


void CHuffmanCompressorDlg::OnBnClickedCompare()
{
	// open a file name
	OPENFILENAME ofn = {};

	wchar_t szFilePath1[256] = {};
	wchar_t szFilePath2[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath1;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"txt\0*.txt\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = nullptr;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	ofn.lpstrFile = szFilePath2;
	ofn.lpstrFilter = L"hfd\0*.hfd\0ALL\0*.*";

	if (false == GetOpenFileName(&ofn))
		return;

	FILE* pTxt = nullptr;
	_wfopen_s(&pTxt, szFilePath1, L"rt");
	FILE* pHfd = nullptr;
	_wfopen_s(&pHfd, szFilePath2, L"rt");


	if (pTxt == NULL || pHfd == NULL) 
		return;

	char txtBuff[1024] = {};
	char hfdBuff[1024] = {};
	int count = 0;

	bool bCheck = true;
	while (true) 
	{
		count++;
		if (feof(pTxt) == 0 && feof(pHfd) == 0) 
		{
			fgets(txtBuff, 1024, pTxt);
			fgets(hfdBuff, 1024, pHfd);

			if (strcmp(txtBuff, hfdBuff) != 0)
			{
				bCheck = false;
				break;
			}
		}
		else if (feof(pTxt) != 0 && feof(pHfd) == 0)
		{
			bCheck = false;
			break;
		}
		else if (feof(pTxt) == 0 && feof(pHfd) != 0)
		{
			bCheck = false;
			break;
		}
		else
		{
			bCheck = true;
			break;
		}
	}

	fclose(pTxt);
	fclose(pHfd);

	if (bCheck)
	{
		MessageBoxA(NULL, "두 파일 내용은 일치합니다", "내용 확인", MB_OK);
	}
	else
	{
		MessageBoxA(NULL, "두 파일 내용은 불일치합니다", "내용 확인", MB_OK);
	}
}
