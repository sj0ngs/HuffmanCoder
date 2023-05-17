#pragma once

struct HuffmanBin
{
	char tChar;
	string tCode;
};

class HuffmanNode
{
private:
	char m_char;
	int m_ifrequency;
	HuffmanNode* m_pLeft;
	HuffmanNode* m_pRight;

public:
	int GetFrequency()
	{
		return m_ifrequency;
	}

	friend class HuffmanTree;
};

struct HuffmanCmp
{
	bool operator()(HuffmanNode* _pleft, HuffmanNode* _pRight)
	{
		return _pleft->GetFrequency() > _pRight->GetFrequency();
	}
};

class HuffmanTree
{
private:
	HuffmanNode* m_pRoot;
	unordered_map<char, int> m_umapFreq;
	unordered_map<char, string> m_umapCode;
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, HuffmanCmp> m_pq;

public:
	HuffmanTree();
	~HuffmanTree();

public:
	const unordered_map<char, int>& GetFreq() const { return m_umapFreq; }
	const unordered_map<char, string>& GetCode() const { return m_umapCode; }

public:
	void Create(const wchar_t* _wcharPath);
	void Clear();
	string GetString(char _char) { return m_umapCode[_char]; }

private:
	void MakeTree();
	void FindTree(HuffmanNode* _pNode, string _strCode);
	void ReleaseTree(HuffmanNode* _pNode);
};

