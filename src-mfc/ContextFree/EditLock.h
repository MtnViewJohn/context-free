#pragma once

class EditLock
{
public:
	EditLock()
		: m_iLock(MasterLock++)
	{
	}

	~EditLock()
	{
		MasterLock--;
	}

	EditLock(const EditLock&) = delete;
	EditLock(EditLock&&) = delete;
	EditLock& operator=(const EditLock&) = delete;
	EditLock& operator=(EditLock&&) = delete;

	explicit operator bool() const
	{
		return m_iLock == 0;
	}

protected:
	inline static int MasterLock = 0;
	int m_iLock;
};
