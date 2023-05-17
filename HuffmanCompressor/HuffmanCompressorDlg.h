
// HuffmanCompressorDlg.h: 헤더 파일
//

#pragma once

#include "Huffman.h"

// CHuffmanCompressorDlg 대화 상자
class CHuffmanCompressorDlg : public CDialogEx
{
private:
	HuffmanTree* m_pTree;
// 생성입니다.
public:
	CHuffmanCompressorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CHuffmanCompressorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUFFMANCOMPRESSOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadfile();

private:
	void CreateHFT(const wchar_t* _wcharFilePath, const wchar_t* _wcharFileName);
	void CreateHFB(const wchar_t* _wcharFilePath, const wchar_t* _wcharFileName);
	void CreateTXT(const wchar_t* _wcharFilePath, const wchar_t* _wcharFileName);
	bool SearchChar(const vector<HuffmanBin>& _vec, short _sBuff, char* _pChar);
public:
	afx_msg void OnBnClickedDecompress();
};
