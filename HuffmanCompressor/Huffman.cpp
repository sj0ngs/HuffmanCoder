#include "pch.h"
#include "Huffman.h"

HuffmanTree::HuffmanTree()	:
	m_pRoot(nullptr)
{
}

HuffmanTree::~HuffmanTree()
{
	Clear();
}

void HuffmanTree::Create(const wchar_t* _wcharPath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _wcharPath, L"rt");

	assert(pFile);

	char chBuff = (char)0;

	while (true)
	{
		size_t tCheck = fread(&chBuff, sizeof(char), 1, pFile);
		if (0 == tCheck)
			break;

		m_umapFreq[chBuff]++;
	}

	fclose(pFile);

	for (const auto& pair : m_umapFreq)
	{
		HuffmanNode* pNewNode = new HuffmanNode();
		pNewNode->m_char = pair.first;
		pNewNode->m_ifrequency = pair.second;
		pNewNode->m_pLeft = nullptr;
		pNewNode->m_pRight = nullptr;
		m_pq.push(pNewNode);
	}

	MakeTree();
	string tmp = "";
	FindTree(m_pRoot, tmp);
}

void HuffmanTree::Clear()
{
	ReleaseTree(m_pRoot);
	m_pRoot = nullptr;
	m_umapCode.clear();
	m_umapFreq.clear();
	while (!m_pq.empty()) m_pq.pop();
}

void HuffmanTree::MakeTree()
{
	size_t tSize = m_pq.size() - 1;
	for (size_t i = 0; i < tSize; i++)
	{
		HuffmanNode* pNewNode = new HuffmanNode;
		pNewNode->m_char = NULL;
		pNewNode->m_pLeft = m_pq.top();
		m_pq.pop();
		pNewNode->m_pRight = m_pq.top();
		m_pq.pop();
		pNewNode->m_ifrequency = pNewNode->m_pLeft->GetFrequency() + pNewNode->m_pRight->GetFrequency();
		m_pq.push(pNewNode);
	}
	m_pRoot = m_pq.top();
}

void HuffmanTree::FindTree(HuffmanNode* _pNode, string _strCode)
{
	if (nullptr == _pNode)
		return;

	FindTree(_pNode->m_pLeft, _strCode + '0');
	FindTree(_pNode->m_pRight, _strCode + '1');

	if ((char)0 != _pNode->m_char)
	{
		m_umapCode[_pNode->m_char] = _strCode;
	}
}

void HuffmanTree::ReleaseTree(HuffmanNode* _pNode)
{
	if (nullptr == _pNode)
		return;

	ReleaseTree(_pNode->m_pLeft);
	ReleaseTree(_pNode->m_pRight);
	delete _pNode;
	_pNode = nullptr;
}
